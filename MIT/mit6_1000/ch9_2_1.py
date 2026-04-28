def f(x):
    """Assume x is an int > 0"""
    ans = 0
    #Loop that takes constant time
    for i in range(1000):
        ans += 1
    print('Number of additions so far', ans)
    #Loop that takes time x
    ans = 0
    for i in range(x):
        ans += 1
    print('Number of additions so far', ans)
    #Nested loops take time x**2
    ans = 0
    for i in range(x):
        for j in range(x):
            ans += 1
    print('Number of additions so far', ans)
    return ans

f(10)
f(100)
f(1000)
f(10000)

