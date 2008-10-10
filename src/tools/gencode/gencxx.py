from generator import *
import string
import sys
import os.path
import re

TYPES = {}
STRUCTLETS = {}

EMPTYLINES = re.compile('\n\s+\n\s+\n')

def indent(s):
    if (not s):
        return ""
    if (s [0] != "\n"): s = "\t" + s;
    s = s.replace ("\n", "\n\t").replace ("\n\t\n", "\n\n")
    s = EMPTYLINES.sub("", s)
    if (s [-1:] == "\t"): s = s [:-1]
    return s

class CXXFunc:
    def __init__(self, name, generator, rules):
        pass

    def get(self):
        return ""

    def code(self):
        return ""

class Processor:
    def _process_rules(self, rules):
        for i in rules:
            # most items are lists, but not all
            try: (name,i) = i.items()[0]
            except: name = i
            if name[0:3].lower() == "if ":
                nif = CXXIf(name[3:],i,packet=self)
                self.static_size = False
                self.vars.append(nif)
                continue
            elif name[0:10] == "structlet ":
                sname = name[10:].strip()
                if not STRUCTLETS.has_key(sname):
                    print "Structlet %s not found" %sname
                else:
                    self.vars.append(CXXComment("STRUCTLET %s" %sname))
                    # if the structlet generates a struct, we inheritance from it
                    if STRUCTLETS[sname].struct:
                        self.parents.append(STRUCTLETS[sname].struct.name)
                    self._process_rules(STRUCTLETS[sname].structure)
                    self.vars.append(CXXComment("END STRUCTLET %s" %sname))
                continue
            elif name == "spacer":
                var = TYPES ["spacer"] (None, self, i, init=None)
                if not var.static_size:
                    self.static_size = False
                self.vars.append (var)
                continue
            elif not isinstance(i,DictType) or not i.has_key("type"):
                print "Illegal structure entry `%s' in item: #%i" % (name, self.generator.count)
                continue
            typ = i["type"]
            vinit = None
            if i.has_key("init"):
                vinit = i["init"]
            if TYPES.has_key(typ):
                var = TYPES [typ] (name, self, i, init=vinit)
                if not var.static_size:
                    self.static_size = False
                self.vars.append (var)
            else:
                print "Unknown value type (%s) in item %s (#%i)" %(typ,name,self.generator.count)

class CXXOpParseFunc(CXXFunc):
    def __init__(self, struct):
        self.struct = struct

    def get(self):
        if (not len (self.struct.vars)):
            return "";

        pktlendef = ""
        if self.struct.packet.varlen:
            pktlendef = ", uint pktlen"

        return \
"""static %(name)s_t *Create (Socket *socket%(pktlendef)s);
bool Parse (Socket *socket%(pktlendef)s);
""" %{"name":self.struct.name, "pktlendef":pktlendef}

    def code(self):
        if (not len (self.struct.vars)):
            return "";

        out = []
        tvars = []
        tvars2 = {}
        for i in self.struct.vars:
            ii = i.get_parse()
            if ii:
                out.append(ii)
        map(lambda x: tvars2.__setitem__(x[1],x[0]), tvars)
        tvars = []
        for (name,type) in tvars2.items(): tvars.append("%s %s;" %(type, name))

        if self.struct.packet.varlen:
            pktlendef = ", uint pktlen"
            pktlen = ", pktlen"
        else:
            pktlendef = ""
            pktlen = ""

        return \
"""%(name)s_t *%(name)s_t::Create (Socket *socket%(pktlendef)s)
{
    %(name)s_t *This = new %(name)s_t;
    if (This->Parse (socket%(pktlen)s))
        return This;
    This->DecRef (); return NULL;
}

bool %(name)s_t::Parse (Socket *socket%(pktlendef)s)
{
%(code)s
    return true;
}
""" %{"name":self.struct.name, "code": indent ("\n".join(tvars + out)),
      "pktlendef": pktlendef, "pktlen": pktlen}

class CXXOpInitFunc(CXXFunc):
    def __init__(self, struct):
        self.struct = struct

    def get(self):
        need_init = 0
        for i in self.struct.vars:
            ii = i.get_init()
            if ii:
                need_init = 1
                break

        if need_init:
            return \
"""static %(name)s_t *Create ();
void Init ();
""" %{"name":self.struct.name}
        else:
            return \
"""static %(name)s_t *Create ();
""" %{"name":self.struct.name}

    def code(self):
        out = []
        for i in self.struct.vars:
            ii = i.get_init()
            if ii:
                out.append(ii)

        if out:
            return \
"""%(name)s_t *%(name)s_t::Create ()
{
    %(name)s_t *This = new %(name)s_t;
    This->Init ();
    return This;
}

void %(name)s_t::Init ()
{
%(code)s
}
""" %{"name":self.struct.name, "code":indent ("\n".join(out))}
        else:
            return \
"""%(name)s_t *%(name)s_t::Create ()
{
    %(name)s_t *This = new %(name)s_t;
    return This;
}
""" %{"name":self.struct.name}



class CXXOpDestructFunc(CXXFunc):
    def __init__(self, struct):
        self.struct = struct

    def get(self):
        for i in self.struct.vars:
            ii = i.get_destructor()
            if ii:
                return \
"""protected:
virtual ~%(name)s_t ();
public:
""" %{"name":self.struct.name}
        return None

    def code(self):
        out = []
        for i in self.struct.vars:
            ii = i.get_destructor()
            if ii:
                out.append(ii)

        if (not len (out)):
            return None

        return \
"""%(name)s_t::~%(name)s_t ()
{
%(code)s
}
""" %{"name":self.struct.name, "code":indent ("\n".join(out))}

class CXXOpAssembleFunc(CXXFunc):
    def __init__(self, struct):
        self.struct = struct

    def get(self):
        return \
"""virtual void Assemble ();
""" %{"name":self.struct.name}

    def code(self):
        tvars = []
        tvars2 = {}
        try:
            asize = [self.struct.packet.generator.codesnippets ["pkthdr_size"]]
            out = [self.struct.packet.generator.codesnippets ["pkthdr_assemble"].strip () %{"name":self.struct.name}]
        except:
            print "ERROR: No pkthdr_size/pkthdr_assemble code snippets!"
            os.abort ()
        for i in self.struct.vars:
            ii = i.get_size()
            if ii: asize.append(ii)
            ii = i.get_assemble()
            if ii: out.append(ii)
        map(lambda x: tvars2.__setitem__(x[1],x[0]), tvars)
        tvars = []
        for (name,type) in tvars2.items():
            tvars.append ("%s %s;\n" %(type, name))
        return "void %s_t::Assemble ()\n{\n" %self.struct.name + \
            indent ("".join(tvars) + "length = " + " + ".join(asize) + ";\n" + \
            "\ndata = new uint8 [length]; uint8 *cur = data;\n" + "\n".join(out))+"\n}\n"

class CXXValue(Value):
    parse = True
    cname = None
    array = None
    const = False
    static_size = True

    def __init__(self, name, packet, rules, init=None):
        Value.__init__(self, name, packet, rules)
        self.init = init
        if isinstance(rules, DictType):
            if rules.has_key("init"):
                self.init = rules["init"]
            if rules.has_key("array"):
                if packet: self.iterator = packet.get_iterator();
                else: self.iterator = "i"
                self.array = rules["array"]
                if self.array == "?":
                    if self.packet.varlen:
                        raise ValueError, "Only one variable-length array per packet is allowed"
                    self.packet.varlen = True;
            if rules.has_key("const"):
                self.const = True
                self.init = rules["const"]

    def get_decl(self):
        if self.const:
            return None
        if self.array is not None:
            if self.packet.varlen:
                return "uint %(name)s_Size;\n%(cname)s *%(name)s;" %{"cname":self.cname, "name":self.name}
            else:
                return "%s %s[%i];" %(self.cname, self.name, self.array)
        return "%s %s;" %(self.cname, self.name)

    def get_init(self):
        if not self.const and self.init is not None:
            return "%s = %s;" %(self.name, self.init)
        return None

    def get_parse(self):
        if self.const:
            return None
        if self.array is not None:
            if self.packet.varlen:
                raise ValueError, "Varlen arrays of this type not supported yet"
            return \
"""for (uint %(i)s = 0; %(i)s < %(array)s; %(i)s++)
    if (!socket->%(trans)s (%(name)s [%(i)s]))
        return false;
""" %{"i":self.iterator, "name":self.name, "trans":self.ctrans_parse, "cname":self.cname, "array":self.array}
        return "if (!socket->%s (%s)) return false;" %(self.ctrans_parse, self.name)

    def get_destructor(self):
        return None

    def get_size(self):
        if self.array is not None:
            if self.packet.varlen:
                return "%s_Size" %self.name
            return "sizeof (%s)*%i" %(self.cname, self.array)
        return "sizeof (%s)" %self.cname

    def get_assemble(self):
        if self.const:
            if self.array is not None:
                if self.packet.varlen:
                    raise ValueError, "Varlen arrays of this type not supported yet"
                return """
for (uint %(i)s = 0; %(i)s < %(array)s; %(i)s++)
{
    %(trans)s (cur, %(init)s);
    cur += sizeof (%(cname)s);
}
""" %{"i": self.iterator, "init":self.init, "trans":self.ctrans_put, "cname":self.cname, "array":self.array}
            return "%(trans)s (cur, %(init)s); cur += sizeof (%(cname)s);" %{"trans":self.ctrans_put, "init":self.init, "cname":self.cname}

        if self.array is not None:
            if self.packet.varlen:
                raise ValueError, "Varlen arrays of this type not supported yet"
            return """
for (uint %(i)s = 0; %(i)s < %(array)s; %(i)s++)
{
    %(trans)s (cur, %(name)s [%(i)s]);
    cur += sizeof (%(cname)s);
}
""" %{"i": self.iterator, "name":self.name, "trans":self.ctrans_put, "cname":self.cname,"array":self.array}
        return "%(trans)s (cur, %(name)s); cur += sizeof (%(cname)s);" %{"trans":self.ctrans_put,"name":self.name, "cname":self.cname}


class CXXComment(CXXValue):
    def __init__(self, text):
        if text.find("\n") != -1:
            self.text = "/* %s */" %text
        else:
            self.text = "// %s " %text
        CXXValue.__init__(self, None, None, None, None)

    def get_decl(self):
        return self.text

    def get_assemble(self):
        return self.text

    def get_init(self):
        return self.text

    def get_size(self):
        return None

    def get_parse(self):
        return self.text


class CXXCompound(CXXValue, Processor):
    def __init__(self, rules, packet=None):
        self.rules = rules
        self.packet = packet
        self.varlen = False
        self.vars = []
        self.generator = packet.generator
        if packet: self.iterator = packet.get_iterator()
        else: self.iterator = "i"
        self._process_rules(rules)

    def get_decl(self):
        out = []
        for i in self.vars:
            ii = i.get_decl()
            if ii:
                out.append(ii)
        return "\n".join(out)

    def get_init(self):
        out = []
        for i in self.vars:
            ii = i.get_init()
            if ii:
                out.append(ii)
        return "\n".join(out)

    def get_parse(self):
        out = []
        for i in self.vars:
            ii = i.get_parse()
            if ii: out.append(ii)
        return self.header+indent ("\n".join(out))+"\n"+self.footer

    def get_destructor(self):
        out = []
        for i in self.vars:
            ii = i.get_destructor()
            if ii: out.append(ii)
        if (not len (out)):
            return None
        return indent ("\n".join(out)) + "\n"

    def get_size(self):
        out = []
        for i in self.vars:
            ii = i.get_size()
            if ii: out.append(ii)
        return " + ".join(out)

    def get_assemble(self):
        out = []
        for i in self.vars:
            ii = i.get_assemble()
            if ii: out.append(ii)
        return self.header+indent ("\n".join(out))+"\n"+self.footer

    def change_varnames(self, func):
        for i in self.vars:
            try:    i.change_varnames(func)
            except: func(i)

    def get_iterator(self):
            if self.packet:
                return self.packet.get_iterator()
            else:
                return "i"


class CXXIf(CXXCompound):
    def __init__(self, condition, rules, packet=None):
        if not isinstance(rules, ListType):
            raise ValueError, "If condition malfromed"
        self.condition = condition
        self.header = "if (%s)\n{\n" %condition
        self.footer = "}\n"
        self.static_size = False
        CXXCompound.__init__(self, rules, packet)

    def change_varnames(self, func):
        # change if condition
        for i in self.vars:
            if i.__dict__.has_key("name"):
                oldname = i.name
            try:    i.change_varnames(func)
            except: func(i)
            if i.name != oldname:
                self.condition = self.condition.replace(oldname, i.name)
        for i in self.packet.vars:
            if i.__dict__.has_key("orgname"):
                self.condition = self.condition.replace(i.orgname, i.name)
        self.header = "if (%s)\n{\n" %self.condition

    def get_size(self):
        size = CXXCompound.get_size (self);
        return "((%s) ? (%s) : 0)" %(self.condition, size)

class CXXVector(CXXCompound):
    def __init__(self, name, packet, rules, init=None):
        CXXValue.__init__(self, name, packet, rules, init=init)
        if not rules.has_key("vtype"):
            err = "No vector type defined, vector: "+name
            raise ValueError, err
        if not rules.has_key ("structure"):
            err = "No vector structure defined, vector: "+name
            raise ValueError, err
        self.dir = packet.dir
        if (packet.dir & 1) and (not rules.has_key ("counter")):
            err = "No vector counter defined, vector: "+name
            raise ValueError, err

        self.cname = rules ["vtype"]
        CXXCompound.__init__(self, rules["structure"], packet)
        # Prepend vname to every variable name
        if rules.has_key ("counter"):
            self.counter = rules["counter"]
        else:
            self.counter = None

        self.footer = "}\n"
        self.set_headers()
        def app(i):
            if i.__dict__.has_key ("name"):
                i.orgname = i.name
                i.name = "%(name)s [%(i)s]->" %{"name":self.name,"i":self.iterator} + i.name
        self.change_varnames(app, None)
        self.srules = rules

    def set_headers(self):
        if self.counter:
            self.pheader = "%(name)s.SetLength((int)%(counter)s);\nfor (int i = 0; i < %(name)s.Length(); i++)\n{\n" %{"name":self.name,"counter":self.counter}
        self.header = "for (int %(i)s = 0; %(i)s < %(name)s.Length(); %(i)s++)\n{\n" %{"i":self.iterator, "name":self.name}


    def get_parse(self):
        out = []
        for i in self.vars:
            ii = i.get_parse()
            if ii: out.append(ii)
        return self.pheader+indent ("\n".join(out))+"\n"+self.footer

    def get_destructor(self):
        return None

    def get_decl(self):
        if self.array is not None:
            return "%s %s[%i];" %(self.cname, self.name, self.array)
        return "%s %s;" %(self.cname, self.name)

    def get_size(self):
        if self.static_size:
            return "%(name)s.Length () * (" %{"name":self.name} + CXXCompound.get_size(self) + ")"
        else:
            # we have a dynamic size per item
            return "0;\nfor (int %(i)s = 0; %(i)s < %(name)s.Length (); %(i)s++)\n\tlength += " %{"i":self.iterator, "name":self.name} + CXXCompound.get_size(self) + ";\nlength += 0"

    def change_varnames(self, func, metoo=1):
        CXXCompound.change_varnames(self, func)
        if(metoo):
            func(self)
        self.set_headers()

TYPES["vector"] = CXXVector

class Uint8(CXXValue):
    cname = "uint8"

    def get_parse(self):
        if self.const:
            return None
        if self.array is not None:
            if self.packet.varlen:
                return """%(name)s = new uint8 [%(name)s_Size = pktlen - socket->Chewed ()];
if (!socket->Get (%(name)s, %(name)s_Size)) return false;""" %{"name":self.name}
            return "if (!socket->Get (%(name)s, sizeof (%(name)s))) return false;" %{"name":self.name}
        return "if (!socket->Get (%s)) return false;" %(self.name)

    def get_assemble(self):
        if self.const:
            if self.array is not None:
                if self.packet.varlen:
                    return "memset (cur, %(init)s, %(name)s_Size); cur += %(name)s_Size;" %{"name":self.name, "init":self.init}
                return "memset (cur, %(init)s, sizeof (%(cname)s)*%(array)s); cur += sizeof (%(cname)s)*%(array)s;" %{"cname":self.cname, "init":self.init, "array":self.array}
            return "*cur = %s; cur += sizeof (%s);" %(self.init, self.cname)
        if self.array is not None:
            if self.packet.varlen:
                return "memcpy (cur, %(name)s, %(name)s_Size); cur += %(name)s_Size;" %{"name":self.name}
            return "memcpy (cur, %(name)s, sizeof (%(name)s)); cur += sizeof (%(name)s);" %{"name":self.name}
        return "*cur = %s; cur += sizeof (%s);" %(self.name, self.cname)

TYPES["uint8"] = Uint8

class Uint16(CXXValue):
    cname = "uint16"
    ctrans_parse = "GetLE"
    ctrans_put = "PUT_LE16"

TYPES["uint16"] = Uint16

class Uint32(CXXValue):
    cname = "uint32"
    ctrans_parse = "GetLE"
    ctrans_put = "PUT_LE32"

TYPES["uint32"] = Uint32

class Uint64(CXXValue):
    cname = "uint64"
    ctrans_parse = "GetLE"
    ctrans_put = "PUT_LE64"

TYPES["uint64"] = Uint64

class Int16(CXXValue):
    cname = "int16"
    ctrans_parse = "GetLE"
    ctrans_put = "PUT_LE16"

TYPES["int16"] = Int16

class Int32(CXXValue):
    cname = "int32"
    ctrans_parse = "GetLE"
    ctrans_put = "PUT_LE32"

TYPES["int32"] = Int32

class Int64(CXXValue):
    cname = "int64"
    ctrans_parse = "GetLE"
    ctrans_put = "PUT_LE64"

TYPES["int64"] = Int64

class Spacer(CXXValue):
    length = 1 # length in bytes

    def __init__(self, name, packet, rules, init=None):
        #Value.__init__(self, name, packet, rules)
        self.length = 1
        if isinstance(rules, DictType):
            if rules.has_key("length"):
                self.length = rules["length"]

    def get_parse(self):
        return "if (!socket->Skip (%s)) return false;" %(self.length)

    def get_assemble(self):
        if self.length > 1:
            return "memset (cur, 0, sizeof (uint8)*%(length)s); cur += %(length)s;" %{"length":self.length}
        return "*cur = 0; cur += sizeof (uint8);"

    def get_decl(self):
        return None

    def get_init(self):
        return None

    def get_size(self):
        return str(self.length);

TYPES["spacer"] = Spacer

TYPES["guid"] = Uint64

class String(CXXValue):
    cname = "char *"
    static_size = False

    def get_parse(self):
        if self.parse:
            return "if (!(%(name)s = socket->GetCStr ())) return false;" %{"name":self.name}

    def get_destructor(self):
        return "delete [] %(name)s;" %{"name":self.name}

    def get_assemble(self):
        return """{
    size_t _sl = strlen (%(name)s);
    memcpy (cur, %(name)s, _sl + 1);
    cur += _sl + 1;
}""" %{"name":self.name}

    def get_size(self):
        return "strlen (%s) + 1" %self.name

TYPES["string"] = String

class PString(CXXValue):
    cname = "char *"
    static_size = False

    def __init__(self, name, packet, rules, init=None):
        Value.__init__(self, name, packet, rules)
        self.init = init
        if isinstance(rules, DictType):
            if rules.has_key("ltype"):
                self.ltype = TYPES [rules ["ltype"]] ("_sl", packet, [])
            else:
                self.ltype = TYPES ["uint8"] ("_sl", packet, [])

    def get_parse(self):
        if self.parse:
            return """{
    %(cnt_ctype)s _sl;
    %(ctrans)s
    %(name)s = new char [_sl + 1];
    if (!socket->Get (%(name)s, _sl))
        return false;
    %(name)s [_sl] = 0;
}""" %{"cnt_ctype":self.ltype.cname, "ctrans":self.ltype.get_parse(), "name":self.name}

    def get_destructor(self):
        return "delete [] %(name)s;" %{"name":self.name}

    def get_assemble(self):
        return """{
    %(cnt_ctype)s _sl = strlen (%(name)s);
    %(ctrans)s
    memcpy (cur, %(name)s, _sl);
    cur += _sl;
}""" %{"cnt_ctype":self.ltype.cname, "ctrans":self.ltype.get_assemble(), "name":self.name}

    def get_size(self):
        return "1 + strlen(%s)" %self.name

TYPES["pstring"] = PString

class Float(CXXValue):
    cname = "float"
    ctrans_parse = "GetLE"
    ctrans_put = "PUT_LEF32"

    def get_parse(self):
        if self.const:
            return None
        if self.array is not None:
            return \
"""for (uint i = 0; i < %(array)s; i++)
    if (!socket->%(trans)s (%(name)s [i]))
        return false;
""" %{"name":self.name, "trans":self.ctrans_parse, "cname":self.cname, "array":self.array}
        return "if (!socket->%s (%s)) return false;" %(self.ctrans_parse, self.name)

    def get_assemble(self):
        if self.const:
            if self.array is not None:
                return """
for (uint i = 0; i < %(array)s; i++)
{
    %(trans)s(cur,(uint32)%(init)s);
    cur += sizeof (%(cname)s);
}
""" %{"init":self.init, "trans":self.ctrans_put, "cname":self.cname, "array":self.array}
            return "%(trans)s (cur, %(init)s); cur += sizeof (%(cname)s);" %{"trans":self.ctrans_put, "init":self.init, "cname":self.cname}

        if self.array is not None:
            return """
for (uint i = 0; i < %(array)s; i++)
{
    %(trans)s (cur, %(name)s [i]);
    cur += sizeof (%(cname)s);
}
""" %{"name":self.name, "trans":self.ctrans_put, "cname":self.cname,"array":self.array}
        return "%(trans)s (cur, %(name)s); cur += sizeof (%(cname)s);" %{"trans":self.ctrans_put,"name":self.name, "cname":self.cname}

TYPES["float"] = Float

class CXXPacket(Packet, Processor):
    def __init__(self, generator, rules):
        Packet.__init__(self, generator, rules)
        self.init = []
        self.parse = []
        self.ass = []
        self.end = []
        self.vars = []
        self.iterator = 0
        self.parents = []
        self.varlen = False
        if not self.rules.has_key("opcode") or not self.rules.has_key("name"):
            print "Illegal packet description item: #%i" %generator.count
            return

        # Direction is a bitmask: bit 0 set for IN, bit 1 for OUT
        self.dir = 3
        if self.rules.has_key("direction"):
            if self.rules["direction"][:2].lower() == "in":
                self.dir = 1
            elif self.rules["direction"][:3].lower() == "out":
                self.dir = 2
            elif self.rules["direction"].lower() == "both":
                self.dir = 3
            else:
                errtxt = "Unknown packet direction: %s" %self.rules["direction"]
                raise ValueError, errtxt

        if self.rules.has_key("structure"):
            self._process_rules(self.rules["structure"])

        struct = CXXOpStruct(self.rules["name"],self)
        struct.vars += self.vars #add all memeberchars to the op struct
        self.generator.structs.append(struct)
        # add opcode  & struct
        self.generator.consts_opcode.append("%s = 0x%0.4X" %(self.rules["name"], self.rules["opcode"]))

    def get_iterator(self):
            self.iterator += 1;
            return "i%s" %self.iterator;


class CXXStruct:
    def __init__(self, name, generator):
        self.name = name
        self.generator = generator
        self.vars = []
        self.funcs = []
        self.header = """
struct %s
{
""" %self.name

    def code(self):
        if not len (self.funcs):
            return ""

        out = []
        for i in self.funcs:
            ii = i.code()
            if ii: out.append(ii)
        return "\n".join(out) + "\n";

    def pktname(self):
        if self.__dict__.has_key ("packet"):
            return "{ %(name)s, \"%(name)s\" },\n" %{"name":self.name}
        return  ""

    def get(self):
        if (not len (self.vars)) and (not len (self.funcs)):
            return ""

        out = []
        for i in self.vars:
            ii = i.get_decl()
            if ii:
                out.append(ii)
        if (len (out)): out.append ("")
        for i in self.funcs:
            ii = i.get()
            if ii: out.append(ii)
        return self.header + indent ("\n".join(out)) + "};\n"

class CXXOpStruct(CXXStruct):
    def __init__(self, name, packet):
        CXXStruct.__init__(self, name, packet.generator)
        self.header = """
class %s_t : public %s
{
public:
""" %(self.name, ", ".join(["NetworkPacket"] + packet.parents))
        self.packet = packet
        self.vars = []
        self.funcs = []
        self.empty = not self.packet.rules.has_key("structure")
        # Do not emit code if packet description is empty
        if self.empty:
            return
        # test which function is required
        if (packet.dir & 2):
            self.funcs.append (CXXOpInitFunc (self))
            self.funcs.append (CXXOpAssembleFunc (self))
        if (packet.dir & 1):
            self.funcs.append(CXXOpParseFunc(self))
            if len(self.funcs):
                self.funcs.insert(0,CXXOpDestructFunc(self))
        #

    def get_switch(self):
        # really lowlevel override
        key = "parser_%s" %self.name
        if self.generator.codesnippets.has_key (key):
            code = self.generator.codesnippets [key];
        elif self.packet.rules.has_key("c++code"):
            code = self.packet.rules["c++code"]
        elif self.packet.rules.has_key("c++handler"):
            # Do not emit code if packet description is empty
            if self.empty:
                code = "%s ();" %self.packet.rules["c++handler"]
            else:
                pktlen = ""
                if self.packet.varlen:
                    pktlen = ", pktlen"
                code = \
"""packet = %(name)s_t::Create (socket%(pktlen)s);
if (packet)
    %(func)s (*(%(name)s_t *)packet);
""" %{"name":self.name, "func":self.packet.rules["c++handler"], "pktlen":pktlen}
        elif self.packet.rules.has_key("luahandler"):
            code = \
"""packet = %(name)s_t::Create (socket);
lua_getglobal(Lua, "%(func)s");
tolua_pushusertype(Lua,(void*)packet,"%(name)s_t");
tolua_pushusertype(Lua,(void*)this,"GameClient");
if(lua_pcall(Lua, 2, LUA_MULTRET, 0))
            CONSOLE.Out (
                         "\\axeWARNING: \\ax2Lua handler \\axa%(name)s\\ax2 failed:\\n%%s\\n", lua_tostring(Lua, -1));
""" %{"name":self.name, "func":self.packet.rules["luahandler"]}
        else:
            # Generate default handler only for incoming packets
            if ((self.packet.dir & 1) == 0):
                return ""
            return "// Unhandled packet %s\n" %self.name
        return "case %s:\n{\n\t" %self.name +\
            code.strip ().replace ("\n", "\n\t") + "\n\tbreak;\n}\n"

class CXXEnum:
    def __init__(self, name, generator):
        self.generator = generator
        self.name = name
        self.consts = []

    def get(self):
        out = []
        for i in self.consts:
            out.append(i.get())
        return """
enum %s
{
%s
};
""" %(self.name, indent (",\n".join(out)))

class CXXConst:
    def __init__(self, generator, packet):
        if not packet.has_key("value") or not packet.has_key("name") :
            print "Wrong Const packet"
            return
        self.name = packet["name"]
        try: self.value = eval(packet["value"])
        except: self.value = packet["value"]
        self.enum = None
        self.generator = generator
        if packet.has_key("format"):
            self.format = packet["format"]
        else:
            # default output for numeric numbers is hex
            if isinstance(self.value, IntType) or isinstance(self.value, LongType):
                self.format = "0x%X"
            else:
                self.format = "%s"

        if packet.has_key("enum"):
            if generator.enums.has_key(packet["enum"]):
                self.enum = generator.enums[packet["enum"]]
            else:
                self.enum = CXXEnum(packet["enum"], generator)
                generator.enums[packet["enum"]] = self.enum
            self.enum.consts.append(self)
        else:
            generator.consts.append(self)

    def get(self):
        if isinstance(self.value, StringType):
            value = eval(self.value)
        else:
            value = self.value
        if self.enum:
            format = "%%s = %s" %self.format
            return format %(self.name, value)
        format = "#define %%s %s\n" %self.format;
        return format %(self.name, value)

class Structlet(Processor, CXXCompound):
    """A structlet is a structure snipplet which can be embedded with
    - structlet [STRUCTLETNAME]
    into other structure definitions.
    Every structlet can generate a struct class with is member chars, when struct-name is set
    """
    def __init__(self, generator, rules):
        self.generator = generator
        self.rules = rules
        self.vars = []
        self.struct = None
        self.iterator = 0
        if not rules.has_key("structure"):
            raise ValueError, "structlet without structure"
        if not rules.has_key("name"):
            raise ValueError, "structlet without name"
        if rules.has_key("struct-name"):
            self.struct_name = rules["struct-name"]
        else:
            self.struct_name = None
        self.name = rules["name"]
        self.structure = rules["structure"]
        if self.struct_name:
            # this structlet will have a own struct, so generate it and add it to the generator
            self._process_rules(self.structure)
            self.struct = CXXStruct(self.struct_name, generator)
            self.struct.vars = self.vars
            generator.structs.append(self.struct)

    def get_iterator(self):
        """structlets have global unique iterators"""
        return self.generator.get_iterator()

class CXXGenerator(Generator):
    def __init__(self, rules, options):
        Generator.__init__(self, rules, options)
        self.header = []
        self.consts = []
        self.consts_opcode = []
        self.switch = []
        self.enums = {}
        self.structs = []
        self.codesnippets = {}
        self.iterator = 0

    def proceed_item(self, item):
        if not isinstance(item, DictType) or not item.has_key("type"):
            print "Wrong formatted entry or no type:"
            print "#"*50
            print item
            print "#"*50
            return
        type = item["type"].lower()
        if type == "packet":
            CXXPacket(self, item)
        elif type == "const":
            CXXConst(self, item)
        elif type == "structlet":
            s = Structlet(self, item)
            STRUCTLETS[s.name] = s
        elif type == "c++code":
            if not item.has_key("code") or not item.has_key("name") :
                print "Wrong code packet:", item
                os.abort ()
            self.codesnippets [item ["name"]] = item ["code"]
        else:
            print "Unknown item type `%s': " % type, item
            os.abort ()

    def write(self):
        if not self.options.what:
            print "--what argument required: [header|code|parser]"
            return
        if self.options.what.lower() == "header":
            print "writing headers"
            data = self.get_header()
        elif self.options.what.lower() == "code":
            print "writing code"
            data = self.get_code()
        elif self.options.what.lower() == "parser":
            print "writing parser"
            data = self.get_parser()
        else:
            print "--what argument unknown"
            return
        fp = open(self.options.filename, "w")
        fp.write(data)
        fp.close()
        print "finished"
        sys.exit(0)

    def get_header(self):
        header = "/* AUTOGENERATED. DO NOT MODIFY !!! */\n"
        header += "/* RULES_MTIME: %s */\n" %os.path.getmtime(self.options.rules)
        if not self.codesnippets.has_key ("header_start") or \
           not self.codesnippets.has_key ("header_end") or \
           not self.codesnippets.has_key ("opcodes_start") or \
           not self.codesnippets.has_key ("opcodes_end"):
            print "Cannot find required c++ code snippets"
            os.abort ()
        header += self.codesnippets["header_start"]
        header += self.codesnippets["opcodes_start"]
        header += indent (",\n".join(self.consts_opcode))
        header += "\n" + self.codesnippets["opcodes_end"]
        for i in self.enums.values():
            header += i.get()
        for i in self.consts:
            header += i.get()
        for i in self.structs:
            header += i.get()

        header += self.codesnippets["header_end"]
        return header

    def get_code(self):
        code = "/* AUTOGENERATED. DO NOT MODIFY !!! */\n"
        code += "/* RULES_MTIME: %s */\n" %os.path.getmtime(self.options.rules)
        if not self.codesnippets.has_key ("code_start") or \
           not self.codesnippets.has_key ("code_end") or \
           (self.options.pktnames and \
            (not self.codesnippets.has_key ("pktnames_start") or \
             not self.codesnippets.has_key ("pktnames_start"))):
            print "Cannot find required c++ code snippets"
            os.abort ()
        code += self.codesnippets["code_start"]
        if self.options.pktnames:
            code += self.codesnippets["pktnames_start"]
            for i in self.structs:
                code += indent (i.pktname())
            code += self.codesnippets["pktnames_end"]
        for i in self.structs:
            code += i.code()
        code += self.codesnippets["code_end"]
        return code

    def get_parser(self):
        parser = "/* AUTOGENERATED. DO NOT MODIFY !!! */\n"
        parser += "/* RULES_MTIME: %s */\n" %os.path.getmtime(self.options.rules)
        for i in self.structs:
            if isinstance(i, CXXOpStruct):
                ii = i.get_switch()
                if ii:
                    parser += ii

        return parser

    def get_iterator(self):
        self.iterator += 1
        return "j%i" %self.iterator

GENERATOR = CXXGenerator
