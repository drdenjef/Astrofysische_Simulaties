import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import matplotlib.animation as manimation
matplotlib.use("Agg")



#text files inlezen, leest 1 punt om de 50 in
# (gewoon om de code wat sneller te laten gaan, veel invloed gaat dit niet hebben op de plot zolang er genoeg punten zijn)
x1 = np.loadtxt("C:\\Users\\Osman\\Downloads\\burrau_FR.txt", unpack=True)[0][::100]
y1 = np.loadtxt("C:\\Users\\Osman\\Downloads\\burrau_FR.txt", unpack=True)[1][::100]
x2 = np.loadtxt("C:\\Users\\Osman\\Downloads\\burrau_FR.txt", unpack=True)[3][::100]
y2 = np.loadtxt("C:\\Users\\Osman\\Downloads\\burrau_FR.txt", unpack=True)[4][::100]
x3 = np.loadtxt("C:\\Users\\Osman\\Downloads\\burrau_FR.txt", unpack=True)[6][::100]
y3 = np.loadtxt("C:\\Users\\Osman\\Downloads\\burrau_FR.txt", unpack=True)[7][::100]

time = np.loadtxt("C:\\Users\\Osman\\Downloads\\burrau_FR_E_err.txt", unpack=True)[2][::100]



# Geen enkel idee hoe dit werkt, voor de zekerheid niet aangekomen.
# de fps kan je hier wel aanpassen naar keuze
FFMpegWriter = manimation.writers['ffmpeg']
metadata = dict(title='Movie Test', artist='Matplotlib',
                comment='Movie support!')
writer = FFMpegWriter(fps=40, metadata=metadata)


fig = plt.figure()
ax1 = plt.subplot2grid((1,21),(0,0), rowspan = 1, colspan = 19)
ax1.set_xlim(-5,5)
ax1.set_ylim(-5,5)
ax1.set_xlabel("x")
ax1.set_ylabel("y")

ax2 = plt.subplot2grid((1,21),(0,20),rowspan = 1, colspan = 1)
ax2.tick_params(axis='x', which='both', bottom=False, top=False, labelbottom=False)
ax2.tick_params(axis='y', which='both', left=False, right=True, labelleft = False, labelright = True)
ax2.set_ylim(0,time[-1])
ax2.set_ylabel('t')
ax2.yaxis.set_label_position("right")


# de plots voor de trails
l1, = ax1.plot([], [], color = 'black')
l2, = ax1.plot([], [], color = 'red')
l3, = ax1.plot([], [], color = 'yellow')

# de plots voor de sterretjes :D
k1, = ax1.plot([], [], color = 'black' , marker = '*')
k2, = ax1.plot([], [], color = 'red' , marker = '*')
k3, = ax1.plot([], [], color = 'yellow' , marker = '*')
bar, = ax2.bar(0,0)



# definieer de lijsten waar de punten voor de lijnplots in moeten
x1_, y1_ = [], []
x2_, y2_ = [], []
x3_, y3_ = [], []


with writer.saving(fig, "burrau_2d.mp4", dpi = 100):
    for i in range(len(x1)):
        # steekt in de sterretjesplot de huidege posities
        k1.set_data(x1[i], y1[i])
        k2.set_data(x2[i], y2[i])
        k3.set_data(x3[i], y3[i])

        # steek in de lijnlijsten voor elke loop de huidige posities, eventueel gaan alle posities erin komen
        x1_.append(x1[i])
        y1_.append(y1[i])
        x2_.append(x2[i])
        y2_.append(y2[i])
        x3_.append(x3[i])
        y3_.append(y3[i])

        if i >= 50:
            l1.set_data(x1_[i-50:i], y1_[i-50:i])
            l2.set_data(x2_[i-50:i], y2_[i-50:i])
            l3.set_data(x3_[i-50:i], y3_[i-50:i])
        else:
            l1.set_data(x1_, y1_)
            l2.set_data(x2_, y2_)
            l3.set_data(x3_, y3_)
        ###
        bar.set_height(time[i])
        writer.grab_frame()
