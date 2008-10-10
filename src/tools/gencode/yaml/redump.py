from yaml.ordered_dict import OrderedDict
from yaml import Parser, Dumper, StringStream

def redump(stream):
    parser = Parser(StringStream(stream))
    parser.dictionary = OrderedDict
    docs = list(iter(parser))
    dumper = Dumper()
    dumper.alphaSort = 0
    return dumper.dump(*docs)
