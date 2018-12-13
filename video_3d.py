import numpy as np
import matplotlib.pyplot as plt
import mpl_toolkits.mplot3d.axes3d as p3
import matplotlib.animation as animation


x1 = np.loadtxt("C:\\Users\\Osman\\Downloads\\burrau_FR.txt", unpack=True)[0][::100]
y1 = np.loadtxt("C:\\Users\\Osman\\Downloads\\burrau_FR.txt", unpack=True)[1][::100]
z1 = np.loadtxt("C:\\Users\\Osman\\Downloads\\burrau_FR.txt", unpack=True)[2][::100]

x2 = np.loadtxt("C:\\Users\\Osman\\Downloads\\burrau_FR.txt", unpack=True)[3][::100]
y2 = np.loadtxt("C:\\Users\\Osman\\Downloads\\burrau_FR.txt", unpack=True)[4][::100]
z2 = np.loadtxt("C:\\Users\\Osman\\Downloads\\burrau_FR.txt", unpack=True)[5][::100]

x3 = np.loadtxt("C:\\Users\\Osman\\Downloads\\burrau_FR.txt", unpack=True)[6][::100]
y3 = np.loadtxt("C:\\Users\\Osman\\Downloads\\burrau_FR.txt", unpack=True)[7][::100]
z3 = np.loadtxt("C:\\Users\\Osman\\Downloads\\burrau_FR.txt", unpack=True)[8][::100]


time = np.loadtxt("C:\\Users\\Osman\\Downloads\\burrau_FR_E_err.txt", unpack=True)[2][::100]


fig = plt.figure()
ax1 = plt.subplot2grid((1,21),(0,0), rowspan = 1, colspan = 19,projection="3d")
ax1.set_xlim(-5,5)
ax1.set_ylim(-5,5)
ax1.set_zlim(-5,5)
ax1.set_xlabel("x")
ax1.set_ylabel("y")
ax1.set_zlabel("z")
ax3 = plt.subplot2grid((1,21),(0,20),rowspan = 1, colspan = 1)
ax3.tick_params(axis='x', which='both', bottom=False, top=False, labelbottom=False)
ax3.tick_params(axis='y', which='both', left=False, right=True, labelleft = False, labelright = True)
ax3.set_ylim(0,time[-1])
ax3.set_ylabel('t')
ax3.yaxis.set_label_position("right")



data = np.array([[x1,y1,z1],[x2,y2,z2],[x3,y3,z3]])
lines = [ax1.plot(dat[0, 0:1], dat[1, 0:1], dat[2, 0:1])[0] for dat in data]
bar, = ax3.bar(0,0)

plt.rcParams['animation.html'] = 'html5'

def update_lines(num, dataLines, lines):
    for line, data in zip(lines, dataLines):
        plt.draw()
        if num >50:
            line.set_data(data[0:2, num-50:num])
            line.set_3d_properties(data[2, num-50:num])
            line.set_marker(",")

        else:
            line.set_data(data[0:2, :num])
            line.set_3d_properties(data[2, :num])
            line.set_marker(",")
        ###
        bar.set_height(time[num])
    return lines


line_ani = animation.FuncAnimation(fig, update_lines, len(x1), fargs=(data, lines),
                                   interval=100, blit=True, repeat=True)

line_ani.save('burrau_3d.mp4', writer='ffmpeg',fps=50)
