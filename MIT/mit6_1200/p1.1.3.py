
# For every nonnegative integer n, the value p(n) is prime

def p(n):
	"""n is nonnegative integer"""
	return n**2 + n + 41

def is_prime(n):
	"""n is nonnegative integer
	   result is True if n is a prime"""
	if n == 1:
		return True
	for i in range(2,n):
		if (n/i).is_integer():
			return False
	return True

def test1():
	for i in range (1,10):
		print("i = ", i, "is a prime = ", is_prime(i));

def test2(k):
	for i in range (1,k):
		n = p(i)
		print("i = ", i, "p() = ", n, "is a prime = ", is_prime(n));


test1()
test2(100)


