import random

def rollDie():
    """Returns a random int between 1 and 6"""
    return random.choice([1,2,3,4,5,6])
def rollN(n):
    result = ''
    for i in range(n):
        result = result + str(rollDie())
    print(result)

rollN(10)

