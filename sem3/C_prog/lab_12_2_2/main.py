from ctypes import *
from tkinter import *


lib = cdll.LoadLibrary("/home/akrik/lab_12/iu7-cprog-labs-2020-krikovanton/lab_12_2_2/mylib.so")


def fill_fibonacci(n, choice):
    _fill_fibonacci = lib.fill_fibonacci
    _fill_fibonacci.argtypes = (POINTER(c_int), c_int)
    _fill_fibonacci.restype = None

    arr = (c_int * n)()

    _fill_fibonacci(arr, n)

    return list(arr)



def fill_myarray(array, size, choice):
    _fill_myarray = lib.fill_myarray 
    _fill_myarray.argtypes = (POINTER(c_int), c_int, POINTER(c_int), POINTER(c_int))
    _fill_myarray.restype = None

    if choice == 1:
        dst = (c_int * size)()
        ndst = c_int()

        src = (c_int * size)(*array)

        _fill_myarray(src, size, dst, ndst)
        
        return list(dst), ndst.value

    elif choice == 2:
        temp_dst = (c_int * size)()
        temp_ndst = c_int()
        src = (c_int * size)(*array)

        _fill_myarray(src, size, temp_dst, temp_ndst)

        dst = (c_int * temp_ndst.value)()        
        ndst = c_int()

        _fill_myarray(src, size, dst, ndst)

        return list(dst), ndst.value;


def get_choice():
    global choice_mem

    choice_mem = int(entry.get())




def create_fib_label(fib_arr):

    input_l4 = Label(root, text="Числа фибоначи\n", font=("ComisSansMS", 15), bg='#FFEFD5')
    input_l4.place(relx=0.01, rely=0.8, relwidth=0.5, relheight=0.1)

    input_l5 = Label(root, text=str(fib_arr), font=("ComisSansMS", 15), bg='#FFEFD5')
    input_l5.place(relx=0.01, rely=0.9, relwidth=0.5, relheight=0.1)



def get_array():
    global array, entry4, size

    array = list(map(int, entry4.get().split()))
    

    ans, ansn = fill_myarray(array, size, choice_mem)
    
    input_l4 = Label(root, text="Массив без повторений\n", font=("ComisSansMS", 15), bg='#FFEFD5')
    input_l4.place(relx=0.01, rely=0.8, relwidth=0.5, relheight=0.1)

    input_l5 = Label(root, text=str(ans), font=("ComisSansMS", 15), bg='#FFEFD5')
    input_l5.place(relx=0.01, rely=0.9, relwidth=0.5, relheight=0.1)


def create_array_label(n, choice):
    global array, entry4
    input_l4 = Label(root, text="Введите исходный массив\n", font=("ComisSansMS", 15), bg='#FFEFD5')
    input_l4.place(relx=0.01, rely=0.8, relwidth=0.5, relheight=0.1)


    entry4 = Entry(root, font=("ComisSansMS", 18), selectborderwidth=5)
    entry4.place(relx=0.15, rely=0.92, relwidth=0.5, relheight=0.08)

    b_point = Button(root, text="Ввести", font=("ComisSansMS", 18), fg="#00CED1", bg="#F8F8FF",
                    activebackground="#FDF5E6", activeforeground="#1E90FF", command=lambda: get_array(), width=8, bd=4)
    b_point.place(relx=0.55, rely=0.92, relwidth=0.15, relheight=0.08, anchor='nw')



def get_command():
    global choice_command

    choice_command = int(entry2.get())



def get_size():
    global size, choice_command, choice_mem

    size = int(entry3.get())

    if (choice_command == 1):
        fib_arr = fill_fibonacci(int(size), int(choice_mem))
        create_fib_label(fib_arr)
    elif (choice_command == 2):
        create_array_label(int(size), int(choice_mem))
        

def create_entry():
    global choice_mem, choice_command, size, arr, entry, entry2, entry3

    input_l = Label(root, text="Выберите способ выделения памяти\n 1 - выделить память с запасом \n" "2 - вызвать функцию, узнать размер, затем повторно вызвать функцию\n", font=("ComisSansMS", 15), bg='#FFEFD5')
    input_l.place(relx=0.01, rely=0.01, relwidth=0.8, relheight=0.13)

    entry = Entry(root, font=("ComisSansMS", 18), selectborderwidth=5)
    entry.place(relx=0.15, rely=0.18, relwidth=0.1, relheight=0.08)

    b_point = Button(root, text="Выбрать", font=("ComisSansMS", 18), fg="#00CED1", bg="#F8F8FF",
                    activebackground="#FDF5E6", activeforeground="#1E90FF", command=lambda: get_choice(), width=8, bd=4)
    b_point.place(relx=0.55, rely=0.18, relwidth=0.15, relheight=0.08, anchor='nw')



    input_l2 = Label(root, text="1 - Заполнить массив числами фибоначчи\n2 - Поместить во второй массив первое вхождение каждого элемента первого массива  \n", font=("ComisSansMS", 15), bg='#FFEFD5')
    input_l2.place(relx=0.01, rely=0.3, relwidth=0.8, relheight=0.11)

    entry2 = Entry(root, font=("ComisSansMS", 18), selectborderwidth=5)
    entry2.place(relx=0.15, rely=0.45, relwidth=0.1, relheight=0.08)

    b_point2 = Button(root, text="Выбрать", font=("ComisSansMS", 18), fg="#00CED1", bg="#F8F8FF",
                    activebackground="#FDF5E6", activeforeground="#1E90FF", command=lambda: get_command(), width=8, bd=4)
    b_point2.place(relx=0.55, rely=0.45, relwidth=0.15, relheight=0.08, anchor='nw')


    input_l3 = Label(root, text="Введите размер\n", font=("ComisSansMS", 15), bg='#FFEFD5')
    input_l3.place(relx=0.01, rely=0.55, relwidth=0.8, relheight=0.11)
    
    entry3 = Entry(root, font=("ComisSansMS", 18), selectborderwidth=5)
    entry3.place(relx=0.15, rely=0.7, relwidth=0.1, relheight=0.08)

    b_point3 = Button(root, text="Выбрать", font=("ComisSansMS", 18), fg="#00CED1", bg="#F8F8FF",
                    activebackground="#FDF5E6", activeforeground="#1E90FF", command=lambda: get_size(), width=8, bd=4)
    b_point3.place(relx=0.55, rely=0.7, relwidth=0.15, relheight=0.08, anchor='nw')



root = Tk()

root.geometry("1200x700+300+200")
root.title('Лабораторная работа 12')
root.config(bg="#FFFAF0")

create_entry()

root.mainloop()
