def gcd(m,n):

    i = min(n, m)
    while i > 0:
            if (m%i) == 0 and (n%i) == 0:
                return(i)
            else:
                i = i - 1

i = gcd(14,63)
print(i)
