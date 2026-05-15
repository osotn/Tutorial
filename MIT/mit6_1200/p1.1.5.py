def euler(a,b,c,d):
	return a**4 + b**4 + c**4 == d**4

n=1000000
for a in range(1,n):
	for b in range(1,n):
		for c in range(1,n):
			for d in range(1,n):
				if euler(a,b,c,d):
					print("a = ", a, " b = ", b, " c = ", c, " d = ", d)
 


	
