def getRatios(vect1, vect2):
    """Assumes: vect1 and vect2 are equal length lists of numbers
       Returns: a list containing the meaningful values of
       vect1[i]/vect2[i]"""
    ratios = []
    for index in range(len(vect1)):
        try:
            ratios.append(vect1[index]/vect2[index])
        except ZeroDivisionError:
            ratios.append(float('nan')) #nan = Not a Number
        except TypeError:
            ratios.append('error')
        except:
            raise ValueError('getRatios called with bad arguments')
    return ratios

vect1 = [1, 3, 5]
vect2 = [2, 5, 6]
print("vect1 = ", vect1, " vect2 = ", vect2, " getRatios = ", getRatios(vect1, vect2))

vect1 = [1, 3, 5]
vect2 = [2, 0, 6]
print("vect1 = ", vect1, " vect2 = ", vect2, " getRatios = ", getRatios(vect1, vect2))

vect1 = [1, 3, 5]
vect2 = [2, "hell", 6]
print("vect1 = ", vect1, " vect2 = ", vect2, " getRatios = ", getRatios(vect1, vect2))

