from tkinter import *
import random



# Построение элементов
def create_entry():
    global entry, input_l, canvas

    input_l = Label(root, text="Введите координаты X и Y через пробел", font=("ComisSansMS", 15), bg='#FFEFD5')
    input_l.place(relx=0.005, rely=0.005, relwidth=0.4, relheight=0.1)

    entry = Entry(root, font=("ComisSansMS", 18), selectborderwidth=5)
    entry.place(relx=0.005, rely=0.1, relwidth=0.4, relheight=0.1)

    b_point = Button(root, text="Ввести координаты", font=("ComisSansMS", 18), fg="#00CED1", bg="#F8F8FF",
                    activebackground="#FDF5E6", activeforeground="#1E90FF", command=lambda: enter('<Return>'), width=8, bd=4)
    b_point.place(relx=0.02, rely=0.2, relwidth=0.35, relheight=0.1, anchor='nw')

    b_find = Button(root, text="Поиск", font=("ComisSansMS", 18), fg="#00CED1", bg="#F8F8FF",
                    activebackground="#FDF5E6", activeforeground="#1E90FF", command=find_answer, width=5, bd=4)
    b_find.place(relx=0.02, rely=0.31, relwidth=0.35, relheight=0.12, anchor='nw')

    b_clear = Button(root, text="Стереть построения", font=("ComisSansMS", 18), fg="#00CED1", bg="#F8F8FF",
                    activebackground="#FDF5E6", activeforeground="#1E90FF", command=clear, width=5, bd=4)
    b_clear.place(relx=0.02, rely=0.44, relwidth=0.35, relheight=0.12, anchor='nw')

    canvas = Canvas(root, bg="white")
    canvas.place(relx=0.41, rely=0.1, relwidth=0.58, relheight=0.88, anchor='nw')


    y = Label(root, text="Y(600)", bg="#FFFAF0", font=("ComisSansMS", 20))
    y.place(relx=0.33, rely=0.91, anchor='nw')

    x = Label(root, text="X(700)", bg="#FFFAF0", font=("ComisSansMS", 20))
    x.place(relx=0.9, rely=0.04,  anchor='nw')




def find_triangle_sides(x1, y1, x2, y2, x3, y3):
    AB = ((x2 - x1)**2 + (y2 - y1)**2) ** 0.5
    BC = ((x2 - x3)**2 + (y2 - y3)**2) ** 0.5
    AC = ((x3 - x1)**2 + (y3 - y1)**2) ** 0.5

    return AB, BC, AC


# Условие существования треугольника
def tringle_condition(AB, BC, AC):
    if (AB + BC <= AC) or (AB + AC <= BC) or (BC + AC <= AB):
        return False
    return True



# Поиск суммы биссектрис
def find_sum_bisectors(a, b, c):
    bs_c = (a * b * (a + b + c) * (a + b - c)) ** 0.5 / (a + b)
    bs_a = (b * c * (a + b + c) * (b + c - a)) ** 0.5 / (b + c)
    bs_b = (c * a * (a + b + c) * (c + a - b)) ** 0.5 / (a + c)

    return bs_c + bs_a + bs_b


# Поиск треугольника
def find_answer():
    global min_coords, bisec_cooords1, bisec_cooords2, bisec_cooords3
    min_sum = 10**20
    flag = 0

    for i in range(0, len(coords)-5, 2):
        for j in range(i + 2, len(coords)-3, 2):
            for k in range(j + 2, len(coords)-1, 2):
                a, b, c = find_triangle_sides(coords[i], coords[i+1], coords[j], coords[j+1], coords[k], coords[k+1])
                cur_sum = find_sum_bisectors(a, b, c)

                if tringle_condition(a, b, c) and cur_sum < min_sum:
                    min_sum = cur_sum

                    #Стираем предыдущие построения
                    if len(min_coords) > 0 and flag == 0:
                        canvas.create_line(min_coords[0], min_coords[1], min_coords[2], min_coords[3], fill='white')
                        canvas.create_line(min_coords[0], min_coords[1], min_coords[4], min_coords[5], fill='white')
                        canvas.create_line(min_coords[2], min_coords[3], min_coords[4], min_coords[5], fill='white')
                        bisec_cooords1 = ((min_coords[0] + min_coords[2]) / 2, (min_coords[1] + min_coords[3]) / 2)
                        canvas.create_line(min_coords[4], min_coords[5], bisec_cooords1[0], bisec_cooords1[1], fill="white")

                        bisec_cooords2 = ((min_coords[0] + min_coords[4]) / 2, (min_coords[1] + min_coords[5]) / 2)
                        canvas.create_line(min_coords[2], min_coords[3], bisec_cooords2[0], bisec_cooords2[1], fill="white")

                        bisec_cooords3 = ((min_coords[2] + min_coords[4]) / 2, (min_coords[3] + min_coords[5]) / 2)
                        canvas.create_line(min_coords[0], min_coords[1], bisec_cooords3[0], bisec_cooords3[1], fill="white")
                        flag = 1

                    min_coords = [coords[i], coords[i+1], coords[j], coords[j+1], coords[k], coords[k+1]]

    if (min_sum == 10**20):
        input_l.config(text="Невозможно построить треугольник!!!", font=("ComisSansMS", 14), fg="Red")
        return



    input_l.config(text="Успех ", font=("ComisSansMS", 14), fg="Green")
    canvas.create_line(min_coords[0], min_coords[1], min_coords[2], min_coords[3])
    canvas.create_line(min_coords[0], min_coords[1], min_coords[4], min_coords[5])
    canvas.create_line(min_coords[2], min_coords[3], min_coords[4], min_coords[5])


    bisec_cooords1 = ((min_coords[0] + min_coords[2]) / 2, (min_coords[1] + min_coords[3]) / 2)
    canvas.create_line(min_coords[4], min_coords[5], bisec_cooords1[0], bisec_cooords1[1], fill="red")

    bisec_cooords2 = ((min_coords[0] + min_coords[4]) / 2, (min_coords[1] + min_coords[5]) / 2)
    canvas.create_line(min_coords[2], min_coords[3], bisec_cooords2[0], bisec_cooords2[1], fill="red")

    bisec_cooords3 = ((min_coords[2] + min_coords[4]) / 2, (min_coords[3] + min_coords[5]) / 2)
    canvas.create_line(min_coords[0], min_coords[1], bisec_cooords3[0], bisec_cooords3[1], fill="red")






def mousec_coords(event):
    point_x_y = (event.x, event.y)
    coords_l = Label(root, text="x = "+str(point_x_y[0]) + "\ny = " + str(point_x_y[1]), bg="#FFFAF0", font=("ComisSansMS", 15))
    coords_l.place(relx=0.33, rely=0.6,  anchor='nw')


# Добавление точек
def update_points(coords_for_update):
    colors = ['red', 'green', 'blue', 'brown', 'orange',
              'grey', 'purple', 'pink', '#FF1493', '#9ACD32', '#4682B4', '#00008B', '#A52A2A',
              '#00FFFF', '#00FF00', '#8A2BE2', '#FFD700', '#FFA07A', '#FA8072', '#00FA9A', '#ADFF2F',
              '#2F4F4F', '#FF00FF', '#BDB76B']
    color = random.choice(colors)

    for i in range(0, len(coords_for_update)-1, 2):
        canvas.create_oval(coords_for_update[i], coords_for_update[i+1], coords_for_update[i], coords_for_update[i+1], outline=color, width=10)


# Ввод данных
def enter(event):
    cur_coords = list(map(float, entry.get().split()))

    if len(cur_coords) & 1 == 1:
        input_l.config(text="Введено нечетное количество координат", font=("ComisSansMS", 12), fg="Red")
        return

    input_l.config(text="Введите координаты X и Y через пробел", font=("ComisSansMS", 15), fg="black")

    for x in cur_coords:
        coords.append(x)

    entry.delete(0, END)
    update_points(cur_coords)


def clear():
    global coords
    coords = list()
    canvas.delete("all")


root = Tk()

root.geometry("1200x700+300+200")
root.title('Лабораторная работа 4. Поиск наименьших длин биссектрис треугольника')
root.config(bg="#FFFAF0")

create_entry()

min_coords = list()
coords = list()

root.bind('<Return>',  enter)
canvas.bind('<Motion>', mousec_coords)


root.mainloop()
