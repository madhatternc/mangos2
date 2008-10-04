__version__ = "0.25"
from load import loadFile
from load import load
from load import Parser
from dump import dump
from dump import dumpToFile
from dump import Dumper
from stream import YamlLoaderException, StringStream, FileStream
from timestamp import timestamp

try:
    from ypath import ypath
except NameError:
    def ypath(expr,target='',cntx=''):
        raise NotImplementedError("ypath requires Python 2.2")


import sys
if sys.hexversion < 0x02010300:
    raise 'YAML is not tested for pre-2.1.3 versions of Python'
