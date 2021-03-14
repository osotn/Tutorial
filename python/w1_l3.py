def gcd(m,n):

    if n > m:
        (n, m) = (m, n)

    if (m%n) == 0:
            return(n)
    else:
        diff = m-n
        return(gcd(max(n,diff), min(n,diff)))

i = gcd(14,63)
print(i)
