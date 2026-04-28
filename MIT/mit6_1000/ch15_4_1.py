import random
import pylab

vals = []
for i in range(1000):
    n1 = random.choice(range(0,101))
    n2 = random.choice(range(0,101))
    vals.append(n1+n2)
pylab.hist(vals, bins = 11)
pylab.ylabel("Number of Occurences")

pylab.show()


