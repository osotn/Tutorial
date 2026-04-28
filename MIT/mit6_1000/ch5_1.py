def intersect(t1, t2):
    """Assumes t1 and t2 are tuples
       Returns a tuple containing elements that are in
       both t1 and t2"""
    result = ()
    for e in t1:
        if e in t2:
            result += (e,)
    return result

t1 = (1,2,3,4)
t2 = (3,4,5,6)
print(t1, " and ", t2, " = ", intersect(t1,t2))

