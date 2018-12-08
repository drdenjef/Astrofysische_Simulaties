import numpy as np
import matplotlib.pyplot as plt
import mpl_toolkits.mplot3d.axes3d as p3
import matplotlib.animation as animation

#textbestanden inlezen
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
ax = p3.Axes3D(fig)

# stop voor elke punt de coordinaten hiering
data = np.array([[x1,y1,z1],[x2,y2,z2],[x3,y3,z3]])

lines = [ax.plot(dat[0, 0:1], dat[1, 0:1], dat[2, 0:1])[0] for dat in data]


ax.set_xlim(-5,5)
ax.set_ylim(-5,5)
ax.set_zlim(-5,5)
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("z")
plt.rcParams['animation.html'] = 'html5'

#update functies, ik weet eingenlijk niet hoe dit werk.
# de lengte van de trails kan je aanpassen door gewoon het getal 50 door iets anders te veranderen
def update_lines(num, dataLines, lines):
    # deze plot is constant aan het roteren, verwijder gewoon deze 2 lijnen als je een steady plot wilt
    angle = num % 360
    ax.view_init(30, angle)
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
    return lines

#hier wordt de uiteindelijke video gemaakt
line_ani = animation.FuncAnimation(fig, update_lines, len(x1), fargs=(data, lines),
                                   interval=100, blit=True, repeat=True)

#hier kan de fps van de video aanpassen en de video opslaan
line_ani.save('burrau_3d.mp4', writer='ffmpeg',fps=30)
