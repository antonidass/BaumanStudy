# # from numpy.polynomial.legendre import leggauss
# # from numpy import arange
# # from math import pi, cos, sin, exp
# # import matplotlib.pyplot as plt

# # def main_function(param):
# #     subfunc = lambda x, y: 2 * cos(x) / (1 - (sin(x) ** 2) * (cos(y) ** 2))
# #     func = lambda x, y: (4 / pi) * (1 - exp(-param * subfunc(x, y))) * cos(x) * sin(x)
# #     return func


# # # a = start, b = end
# # def simpson(func, a, b, num_of_nodes):
# #     if (num_of_nodes < 3 or num_of_nodes & 1 == 0):
# #         raise ValueError

# #     h = (b - a) / (num_of_nodes - 1)
# #     x = a
# #     res = 0

# #     for _ in range((num_of_nodes - 1) // 2):
# #         res += func(x) + 4 * func(x + h) + func(x + 2 * h)
# #         x += 2 * h

# #     return res * (h / 3)


# # #converts to args func to one arg func
# # def func_2_to_1(func2, value):
# #     return lambda y: func2(value, y)


# # def t_to_x(t, a, b):
# #     return (b + a) / 2 + (b - a) * t / 2


# # def gauss(func, a, b, num_of_nodes):
# #     args, coeffs = leggauss(num_of_nodes)
# #     res = 0

# #     for i in range(num_of_nodes):
# #         res += (b - a) / 2 * coeffs[i] * func(t_to_x(args[i], a, b))

# #     return res


# # # func = f(x, y) - function which we integrate
# # # limits = [[a, b], [c, d]] - limits for x and y
# # # num_of_nodes = [N, M] - number of nodes for x and y
# # # integrators = [func1, func2] - functions, which we use to integrate: f(func, a, b, num_of_nodes)
# # def integrate2(func, limits, num_of_nodes, integrators):
# #     inner = lambda x: integrators[1](func_2_to_1(func, x), limits[1][0], limits[1][1], num_of_nodes[1])
# #     return integrators[0](inner, limits[0][0], limits[0][1], num_of_nodes[0])

# # def tao_graph(integrate_func, ar_params, label):
# #     X = list()
# #     Y = list()
# #     for t in arange(ar_params[0], ar_params[1] + ar_params[2], ar_params[2]):
# #         X.append(t)
# #         Y.append(integrate_func(t))
# #     plt.plot(X, Y, c="green", label=label)

# # def generate_label(n, m, func1, func2):
# #     res = "N = " + str(n) + ", M = " + str(m) + ", Methods = "
# #     res += "Simpson" if func1 == simpson else "Gauss"
# #     res += "-Simpson" if func2 == simpson else "-Gauss"
# #     return res


# # end = False
# # while not end:
# #     N = int(input("Enter N: "))
# #     M = int(input("Enter M: "))
# #     param = float(input("Enter param (tao): "))
# #     mode = bool(int(input("Enter external method (0 - Gauss; 1 - Simpson): ")))
# #     func1 = simpson if mode else gauss
# #     mode = bool(int(input("Enter internal method (0 - Gauss; 1 - Simpson): ")))
# #     func2 = simpson if mode else gauss

# #     param_integrate = lambda tao: integrate2(main_function(tao), [[0, pi / 2], [0, pi / 2]], [N, M], [func1, func2])
# #     print("Result with your parameter:", param_integrate(param))
# #     try:
# #         tao_graph(param_integrate, [0.05, 10, 0.05], generate_label(N, M, func1, func2))
# #     except ValueError:
# #         print("Be careful with simpson: argument should be > 2 and not even (3, 5...);")
# #     except ZeroDivisionError:
# #         print("Can't use 2 Simpsons, zero in denominator")
# #     end = bool(int(input("End? (0 - No, 1 - Yes): ")))

# # plt.grid(True)
# # plt.legend()
# # plt.ylabel("Result")
# # plt.xlabel("Tao value")
# # plt.show()




# from numpy.polynomial.legendre import leggauss
# from numpy import arange
# from math import pi, cos, sin, exp
# import matplotlib.pyplot as plt
# import numpy as np
# from numpy.polynomial.legendre import *
# from numpy.linalg import eigvalsh
# from numpy.linalg import solve

# EPS = 1e-6



# def polynom_legendre(n, x):
#    if (n == 0):
#        return 1
#    elif (n == 1):
#        return x
 
#    k1 = polynom_legendre(n - 1, x)
#    k2 = polynom_legendre(n - 2, x)
 
#    return ((2 * n - 1) * x * k1 - (n - 1) * k2) / n


# def half_division(dot1, dot2, n):
 
#    mid_dot = (dot1 + dot2) / 2
 
#    if (abs(dot1 - dot2) < EPS):
#        return mid_dot
 
#    tmp_value = polynom_legendre(n, mid_dot)
 
#    if (tmp_value > 0):
#        return half_division(dot1, mid_dot, n)
#    elif (tmp_value < 0):
#        return half_division(mid_dot, dot2, n)
 
#    return mid_dot


# def legendre(deg):
#     leg_values = np.linspace(-1, 1, deg + 1)
#     x = []

#     for i in range(deg):
#         x1 = leg_values[i]
#         x2 = leg_values[i + 1]

#         if (polynom_legendre(deg, x1) > 0 and (polynom_legendre(deg, x2) < 0)):
#             x1, x2 = x2, x1
#             x.append(half_division(x1, x2, deg))

#     left = np.array([[num ** i for num in x] for i in range(deg)])
#     right = np.array([2 / (i + 1) if i % 2 == 0 else 0 for i in range(deg)])


#     print("left = ", left, "\n\n\n", "rigth =  ", right)
#     w = solve(left, right)

#     return x, w




# def general_function(param):
#     subfunc = lambda x, y: 2 * cos(x) / (1 - (sin(x) * sin(x)) * (cos(y) * cos(y)))
#     func = lambda x, y: (4 / pi) * (1 - exp(-param * subfunc(x, y))) * cos(x) * sin(x)
#     return func


# def Gauss(f, a, b, num):
#     args, coeffs = legendre(num)

#     res = 0

#     sub_f = lambda tao : f((b + a) / 2 + ((b - a) / 2) * tao)

#     for i in range(num):
#         res += (b - a) / 2 * coeffs[i] * sub_f(args[i])

#     return res


# def Simpson(f, a, b, num):
#     h = (b - a) / (num - 1)
#     x = a
#     res = 0

#     for i in range((num - 1) // 2):
#         res += f(x) + 4 * f(x + h) + f(x + 2 * h)
#         x += 2 * h

#     res *= h / 3
#     return res


# def to_single(func2, value):
#     return lambda x: func2(value, x)


# def integrate2(f, limits, num, integrators):
#     inner = lambda x: integrators[1](to_single(f, x), limits[1][0], limits[1][1], num[1])
#     return integrators[0](inner, limits[0][0], limits[0][1], num[0])










# def main():
#     parameter = int(input("Input parameter: "))
#     NSimpson = int(input("Input N (Simpson): "))
#     MGauss = int(input("Input M (Gauss): "))
#     output = integrate2(general_function(parameter), ((0, pi / 2), (0, pi / 2)), (NSimpson, MGauss), (Simpson, Gauss))
#     print("Result = ", output)



# main()






from math import sin, cos, pi, exp
from numpy.linalg import solve
from numpy.polynomial.legendre import leggauss
 
from numpy import array, linspace, arange
 
import matplotlib.pyplot as plt
 
 
EPS = 1e-9
 
 
def func(tao):
   koef = lambda theta, phi: 2 * cos(theta) / (1 - sin(theta) ** 2 * cos(phi) ** 2)
 
   f = lambda theta, phi: (1 - exp(-tao * koef(theta, phi))) * cos(theta) * sin(theta)
 
   return f
 
 
def polynom_legendre(n, x):
   if (n == 0):
       return 1
   elif (n == 1):
       return x
 
   k1 = polynom_legendre(n - 1, x)
   k2 = polynom_legendre(n - 2, x)
 
   return ((2 * n - 1) * x * k1 - (n - 1) * k2) / n
 
 
def method_half_division(dot1, dot2, n):
 
   mid_dot = (dot1 + dot2) / 2
 
   if (abs(dot1 - dot2) < EPS):
       return mid_dot
 
   tmp_value = polynom_legendre(n, mid_dot)
 
   if (tmp_value > 0):
       return method_half_division(dot1, mid_dot, n)
   elif (tmp_value < 0):
       return method_half_division(mid_dot, dot2, n)
 
   return mid_dot
 
 
def find_legendre_roots(n):
   legendre_values = linspace(-1, 1, n + 1)
 
   roots = []

   print("deg = N ", n)
 
   for i in range(n):
       dot1 = legendre_values[i]
       dot2 = legendre_values[i + 1]
 
       if ((polynom_legendre(n, dot1) > 0) and (polynom_legendre(n, dot2) < 0)):
           tmp = dot1
           dot1 = dot2
           dot2 = tmp
 
       roots.append(method_half_division(dot1, dot2, n))
 
   return roots
 
 
def gauss_method(f, a, b, n):
   roots = find_legendre_roots(n)
 
   # Find left side of the system
 
   left_side = array([[num ** i for num in roots] for i in range(n)])
 
 
   print("roots = ", roots)   # Find right side of the system
 
   tmp_right_side = []
 
   for i in range(n):
       if (i % 2 == 0):
           tmp_right_side.append(2 / (i + 1))
       else:
           tmp_right_side.append(0)
 
   right_side = array(tmp_right_side)
 
   # Solve linear equation
 
   solution = solve(left_side, right_side)
 
   # Count Gauss integral
 
   sub_func = lambda tao: f((a + b) / 2 + ((b - a) / 2) * tao)
 
   result = sum(i * sub_func(j) for i, j in zip(solution, roots))
 
   return ((b - a) / 2) * result
 
 
 
def simpson_method(f, a, b, n):
   h = (b - a) / n
 
   res = 0
 
   for i in range(0, n, 2):
 
       f1 = f(i * h)
       f2 = f((i + 1) * h)
       f3 = f((i + 2) * h)
 
       res += f1 + 4 * f2 + f3
 
   return h / 3 * res
 
 
def solve_double_integral(tao, n, m, a, b, method_1, method_2):
   f = func(tao)
 
   first_integral = lambda theta: method_1(lambda phi: f(phi, theta), a, b, n)
 
   second_integral = method_2(first_integral, a, b, m)
 
   result = 4 / pi * second_integral
 
   return result
 
 
 
def choose_method():
   try:
       method_num = int(input("Выберите метод: 1 - Гаусса, 2 - Симпсона: "))
 
       if (method_num < 1 or method_num > 2):
           print("\n\nОшибка: неверно выбран метод\n\n")
           return -2, -2
 
       if (method_num == 1):
           method = gauss_method
       else:
           method = simpson_method
 
       n = int(input("Введите количество узлов: "))
 
       if (n < 1):
           print("\n\nОшибка: количество узлов должно быть больше нуля\n\n")
           return -3, -3
 
       return method, n
   except:
       print("\n\nОшибка: неверно введено число. Повторите\n\n")
       return -1, -1
 
 
if __name__ == "__main__":
    # tao = linspace(0.05, 10, 100)
    tao = [1]
    
    option = -1

    print("\n------------------------ \
        \n  Решить двойной инеграл \
        \n------------------------\n")

    while (option != 0):
        option = int(input("\nДобавить график? (1 - да, 0 - нет): "))

        if (option < 0 or option > 1):
            print("\n\nОшибка: неверно выбрана опция\n\n")

        if (option == 0):
            continue
        
        print("\nПервый метод: ")
        method_1, n = choose_method()

        if (n < 0):
            continue

        print("Второй метод: ")
        method_2, m = choose_method()

        if (m < 0):
            continue

        res = [solve_double_integral(t, n, m, 0, pi / 2, method_1, method_2) for t in tao]

        plt.plot(tao, res, label = "Узлы: n = %d, m = %d" %(n, m))

    plt.legend()
    plt.grid()
    plt.show()