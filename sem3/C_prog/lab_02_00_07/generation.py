from random import randint

n = int(input("input size of array "))

file = open("data.txt", "w")

file.write(str(n) + '\n')

for i in range(n):
    s = str(randint(1, 100000))
    file.write(s + '\n')

file.close()
    