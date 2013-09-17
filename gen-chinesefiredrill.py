#!/bin/python

import random

LIGHTS=24
MAX_LIGHTS=10
MIN_LIGHTS=5
N_COLORS=4

REPS=3

arrs = []

# panel on assignment

print "#define N_PANELS %d" % (LIGHTS)
print "#define REPS %d" % (REPS)

for i in range(REPS):
    nLights = random.randint(MIN_LIGHTS, MAX_LIGHTS)
    on = ["{0}".format(nLights)] + ["{0}".format(n) for n in random.sample(range(LIGHTS), nLights)]
    on = on + ["-1" for n in range(MAX_LIGHTS+1-len(on))]
    arrs.append("{%s}" % (",".join(on)))

print "int lights[%d][N_PANELS] = {%s};" % (REPS, ",".join(arrs))

# light color assignment

colors = range(N_COLORS) * (((LIGHTS-1) / N_COLORS) + 1)
random.shuffle(colors)

lightColor = ["{0}".format(n) for n in colors]

print "int lightColor[N_PANELS] = {%s};" % (",".join(random.sample(lightColor, LIGHTS)))

# color assignment

print "int colors[4][3] = {{ 131, 201, 183 }, { 253, 252, 229 }, { 252, 176, 60 }, { 237, 28, 36 }};"

