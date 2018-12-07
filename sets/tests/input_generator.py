#! /usr/bin/env python

import random
import argparse

minrange = -100000
maxrange = 100000

argparser = argparse.ArgumentParser(
    description="input and reference output generator")
argparser.add_argument("-n", "--numops", type=int, default=100,
                       help="number of set operations to generate")
argparser.add_argument("-i", "--inserts", action='store_true',
                       default=False, help="only generate inserts")
argparser.add_argument("-s", "--sorted", action='store_true', default=False,
                       help="sorted numbers instead of random")

args = argparser.parse_args()

f = open("output.ref", 'w')

s = set()
c = 0
num = 0
for i in range(args.numops):
    if not args.inserts:
        c = random.randint(0,2)
    if args.sorted:
        num = num + 1
    else:
        num = random.randint(minrange, maxrange)

    if c == 0:
        print "+", num
        s.add(num)
    if c == 1:
        print "-", num
        s.discard(num)
    if c == 2:
        print "?", num
        if (num in s):
            f.write("found: ")
        else:
            f.write("not found: ")
        f.write(str(num))
        f.write("\n")

print "p"
for e in sorted(s):
    f.write(str(e))
    f.write("\n")

f.close()
