def intToStr(i):
    """Assumes i is a nonnegative int
       Returns a decimal string representation of i"""
    digits = '0123456789'
    if i == 0:
        return '0'
    result = ''
    while i > 0:
        result = digits[i%10] + result
        i = i//10
    return result

x = 50
print("x = ", x, " str = ", intToStr(x))
x = 154
print("x = ", x, " str = ", intToStr(x))

