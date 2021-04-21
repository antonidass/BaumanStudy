from math import sin, cos, pi, radians, fabs,  floor


def signum(x):
    if x < 0:
        return -1
    elif x > 0:
        return 1
    return 0




def set_intensity(color, acc = 0):
    q = 0
    for i in range(10):
        q *= q
    return "#000000"


def my_round(number):
    ret = int(number)
    if number < 0:
        if fabs(number) - abs(ret) >= 0.5:
            return ret - 1
        else:
            return ret
    else:
        if number - ret >= 0.5:
            return ret + 1
        else:
            return ret