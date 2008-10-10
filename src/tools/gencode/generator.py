from types import *

class Value:
    def __init__(self, name, packet, rules):
        self.packet = packet
        self.rules = rules
        self.name = name

class Packet:
    def __init__(self, generator, rules):
        self.generator = generator
        self.rules = rules

class Generator:
    def __init__(self, rules, options):
        self.options = options
        self.rules = rules
        self.output = []
        self.count = 0

    def proceed(self):
        """Proceed all rules"""
        i = self.rules.next()
        for item in i:
            self.proceed_item(item)
            self.count += 1

    def proceed_item(self, item):
        pass

    def write(self):
        pass
