#!/usr/bin/env python

import sys
import os
import os.path
import yaml

from optparse import OptionParser

options = None

def parse_rules():
	print "Load rules"
	fp = open(options.rules, "r")
	txt = fp.read(-1)
	try:
		s = yaml.loadFile(options.rules)
	#	import syck
	#	s = syck.load(txt)
	except TypeError, e:
		print "%s:%d: (column %d) %s" % \
			(options.rules, e [0], e [1], e [2])
		os.abort ()
	except:
		print "Failed to parse YAML file `%s'\n%s: %s" % \
			(options.rules, sys.exc_info()[0], sys.exc_info()[1])
		os.abort ()
	return s

def main():
	global options
	usage = "usage: %prog -t [type] -f [filename] [-v] [-w] [what] [-q] [rules]"
	parser = OptionParser(usage)
	parser.add_option("-f", "--filename", type="string", dest="filename",
					  help="Filename for output")
	parser.add_option("-n", "--pktnames", action="store_true", dest="pktnames",
					  help="Generate an additional array with packet opcode/string names")
	parser.add_option("-t", "--type", type="string", dest="type",
					  help="Chose one of the output targets: CXX or Python")
	parser.add_option("-w", "--what", type="string", dest="what",
					  help="Target specific: what to generate (header/code/parser)")
	parser.add_option("-v", "--verbose", action="store_true", dest="verbose",
					  help="Display information during the parse process")
	parser.add_option("-q", "--quiet", action="store_false", dest="verbose",
					  help="The reverse of the -v option")


	(options, args) = parser.parse_args()
	if len(args) != 1:
		parser.error("incorrect number of arguments")

	options.rules = args[0]
		
	if options.verbose:
		print "writing %s..."  % options.basename

	if not options.type:
		parser.error("No type specified")
		
	if options.type.lower() == "python":
		import genpython as generator
	elif options.type.lower() == "cxx":
		import gencxx as generator
	else:
		parser.error("No type specified")

	rules = parse_rules()
	gen = generator.GENERATOR(rules, options)
	gen.proceed()
	gen.write()
	
		
if __name__ == "__main__":
	main()
