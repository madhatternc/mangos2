-- register uint8 as char* alternative
--_basic['uint8*'] = 'string'

vector_template = [[
class VType : public Vector 
{ 
public: 
	VType (int limit = 16, int threshold = 16) : Vector (limit, threshold) {} 
	virtual ~VType (); 
	virtual void FreeItem (Some Item) const; 
	CType &Get (int iIndex) const;
	inline CType &operator [] (int iIndex) const;
}
]]


-- we need a special desctructor on classes which inherate from base
function is_basetype(ob)
   if ob == "NetworkPacket" then
     return 1
   end

   while(ob ~= "Base" and ob ~= nil and _global_classes[ob]) do
     ob = _global_classes[ob].base
     --else
     --   ob = nil
     --end
   end
   if ob == "Base" then
   	return 1
   end
   return nil
end


function build_collect_hook(cls, i, v)
   output('\nstatic int '..v..' (lua_State* tolua_S)')
   output('{')
   output(' '..i..'* self = ('..i..'*) tolua_tousertype(tolua_S,1,0);')
   if is_basetype(i) then
      output('	self->DecRef();')
   else
      output('	delete self;')
   end
   output('	return 0;')
   output('}')
end

function build_destructor_class(obj)
   if is_basetype(obj.parent.base) then
     output('   self->DecRef();')
   else
     output('  delete self;')
   end
end

function remove_text(s, q, r)
  while string.find(s, q) do
    s = string.gsub(s, q, r);
  end
  return s

end

-- called for every $ifile directive
-- takes a table with a string called 'code' inside, the filename, and any extra arguments
-- passed to $ifile. no return value
function include_file_hook(t, filename, ...)
  -- We filter out the structlet parents from the classes in Opcodes.h because they are not 
  -- necessary, blow up the wrapper and generate compiler problems
  flush()
  if type(t.code) == nil then
    return
  end
  t.code = remove_text(t.code, "\n[^\n]*[Tt][Oo][Ll][Uu][Aa]_[hH][iI][Dd][eE][^\n]*\n", "\n")
  t.code = remove_text(t.code, "#if 0.-#endif", "")
  t.code = remove_text(t.code, 'extern%s*"C"%s*%b{}%s*', "")
  t.code = remove_text(t.code, "[Tt][Oo][Ll][Uu][Aa]_[Bb][Ee][Gg][Ii][Nn]_[hH][iI][Dd][eE].-[Tt][Oo][Ll][Uu][Aa]_[Ee][Nn][Dd]_[hH][iI][Dd][eE]", "")
  t.code = remove_text(t.code, ",%s*\.\.\.%s*%)", ")") -- we remove varargs because this is done on lua level
  
  if filename == "Opcodes.h" then
    t.code = string.gsub(t.code, "class%s([^%s]+)%s*:%s*public NetworkPacket([, %w_]*)","class %1 : public NetworkPacket")
  elseif t.code ~= nil then
    local _,e,c = strfind(t.code, "\n([^\n]-)[Tt][Oo][Ll][Uu][Aa]_[Bb][Ee][Gg][Ii][Nn][^\n]*\n")
    if e then
      t.code = extract_code("", t.code)
    end

    --local s = extract_code("", t.code)
    --t.code = s
  end

end

function mkvector(m, n, c)
    local ne = string.gsub(vector_template, "VType", n)
    ne = string.gsub(ne, "CType", c)
    return ne

end

-- We catch here macros like the vector definitions and adjust the 
-- Vector template. This allows us to simply generate all Vector classes
-- at the end of all headers
function hook_custom_parse(obj, s)
  local b, e, m, n, c, v = string.find(s, "%s*s?t?a?t?i?c?%s*DECLARE_VECTOR([%w_]*)%s*%(([^,]*),([^,]*),[^)]*%)([^\n]*)\n")
  if b then
    print(b)
    print("FOUND VECTOR")
    print(string.sub(s, 1, e))
    print(obj.policy)
    if obj.policy ~= "public" then
      print("NOT")
      return strsub(s,e+1)
    end
    local ne = mkvector(m, n, c)
    -- initialize one variable with this type
    if v ~= "" and v ~= ";" then
      ne = "\n"..n.." "..v.."\n"
    end
    return ne..strsub(s,e+1)
  end
  return nil
end

