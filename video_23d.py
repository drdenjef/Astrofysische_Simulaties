import numpy as np
import matplotlib.pyplot as plt
import mpl_toolkits.mplot3d.axes3d as p3
import matplotlib.animation as animation

# voor deze functie geld algemeen  bijna dezeflde commentaar als de 3d plot functie

x1 = np.loadtxt("C:\\Users\\Osman\\Downloads\\Burrau_RK4.txt", unpack=True)[0][::50]
y1 = np.loadtxt("C:\\Users\\Osman\\Downloads\\Burrau_RK4.txt", unpack=True)[1][::50]
z1 = np.loadtxt("C:\\Users\\Osman\\Downloads\\Burrau_RK4.txt", unpack=True)[2][::50]

x2 = np.loadtxt("C:\\Users\\Osman\\Downloads\\Burrau_RK4.txt", unpack=True)[3][::50]
y2 = np.loadtxt("C:\\Users\\Osman\\Downloads\\Burrau_RK4.txt", unpack=True)[4][::50]
z2 = np.loadtxt("C:\\Users\\Osman\\Downloads\\Burrau_RK4.txt", unpack=True)[5][::50]

x3 = np.loadtxt("C:\\Users\\Osman\\Downloads\\Burrau_RK4.txt", unpack=True)[6][::50]
y3 = np.loadtxt("C:\\Users\\Osman\\Downloads\\Burrau_RK4.txt", unpack=True)[7][::50]
z3 = np.loadtxt("C:\\Users\\Osman\\Downloads\\Burrau_RK4.txt", unpack=True)[8][::50]



fig = plt.figure()
ax = fig.add_subplot(2, 1, 1, projection="3d")
ax2 = fig.add_subplot(2, 1, 2)

data = np.array([[x1,y1,z1],[x2,y2,z2],[x3,y3,z3]])

#data voor de 3d plot
lines = [ax.plot(dat[0, 0:1], dat[1, 0:1], dat[2, 0:1])[0] for dat in data]

#data voor de 2d-projectie op x-y vlak
lines2 = [ax2.plot(dat[0, 0:1], dat[1, 0:1])[0] for dat in data]


ax.set_xlim(-5,5)
ax.set_ylim(-5,5)
ax.set_zlim(-5,5)
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("z")

ax2.set_xlim(-5,5)
ax2.set_ylim(-5,5)
ax2.set_xlabel("x")
ax2.set_ylabel("y")
plt.rcParams['animation.html'] = 'html5'


def update_lines(num, dataLines, lines, lines2):
    #constant roteren van 3d plot
    angle = num % 360
    ax.view_init(50, angle)
    for line, line2, data in zip(lines, lines2, dataLines):
        plt.draw()
        if num >50:
            line.set_data(data[0:2, num-50:num])
            line.set_3d_properties(data[2, num-50:num])
            line.set_marker(",")
            line2.set_data(data[0:2, num - 50:num])
        else:
            line.set_data(data[0:2, :num])
            line.set_3d_properties(data[2, :num])
            line.set_marker(",")
            line2.set_data(data[0:2, :num])
    return lines


line_ani = animation.FuncAnimation(fig, update_lines, len(x1), fargs=(data, lines, lines2),
                                   interval=100, blit=True, repeat=True)

line_ani.save('burrau_23d.mp4', writer='ffmpeg',fps=30)
