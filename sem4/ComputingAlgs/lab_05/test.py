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
 
 
   # Find right side of the system
 
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
    tao = linspace(0.05, 10, 100)
    
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