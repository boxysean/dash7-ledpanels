#!/bin/python

import sys
import random

N_PANELS = 24
REPS = 100
LIGHTS_ON = 10
N_COLORS = 4

print "#define LIGHTS_ON %d" % (LIGHTS_ON)
print "#define N_PANELS %d" % (N_PANELS)
print "#define REPS %d" % (REPS)

# lights on sequence

seq = range(N_PANELS) * (((REPS-1) / N_PANELS) + 1 + 1) # one extra
random.shuffle(seq)

for idx, x in enumerate(seq[0:REPS]):
    while x in seq[max(0, idx-LIGHTS_ON):idx]:
        swapIdx = random.randint(idx+1, len(seq)-1)
        seq[idx] = seq[swapIdx]
        seq[swapIdx] = x
        x = seq[idx]

seq = seq[0:100]

print "int seq[REPS] = {%s};" % (",".join(["{0}".format(n) for n in seq]))

# light color assignment

colors = range(N_COLORS) * (((N_PANELS-1) / N_COLORS) + 1)
random.shuffle(colors)

lightColor = ["{0}".format(n) for n in colors]

print "int lightColor[N_PANELS] = {%s};" % (",".join(random.sample(lightColor, N_PANELS)))

# color assignment

print "int colors[4][3] = {{ 131, 201, 183 }, { 253, 252, 229 }, { 252, 176, 60 }, { 237, 28, 36 }};"

# print freq count

buckets = {}

for x in seq:
    if x in buckets:
        buckets[x] = buckets[x] + 1
    else:
        buckets[x] = 1

counts = {}

for k, v in buckets.items():
    if v in counts:
        counts[v] = counts[v] + 1
    else:
        counts[v] = 1

print >> sys.stderr, "=== histogram of number of lights on over REPS ==="

for i in range(15):
    if i in counts:
        print >> sys.stderr, "%3d %s" % (i, "".join(['*' for j in range(counts[i])]))
    else:
        print >> sys.stderr, "%3d" % (i)
