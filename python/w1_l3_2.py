def gcd(m,n):

	if n > m:
		(n, m) = (m, n)

	while (m%n) != 0:
		(m, n) = (n, m%n)
		#print(m, n)
	return(n)

i = gcd(3*11*34*1223345,3*34* 123)
print(i)
