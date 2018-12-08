import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import matplotlib.animation as manimation
matplotlib.use("Agg")



#text files inlezen, leest 1 punt om de 50 in
# (gewoon om de code wat sneller te laten gaan, veel invloed gaat dit niet hebben op de plot zolang er genoeg punten zijn)
x1 = np.loadtxt("C:\\Users\\Osman\\Downloads\\Burrau_RK4.txt", unpack=True)[0][::50]
y1 = np.loadtxt("C:\\Users\\Osman\\Downloads\\Burrau_RK4.txt", unpack=True)[1][::50]
x2 = np.loadtxt("C:\\Users\\Osman\\Downloads\\Burrau_RK4.txt", unpack=True)[3][::50]
y2 = np.loadtxt("C:\\Users\\Osman\\Downloads\\Burrau_RK4.txt", unpack=True)[4][::50]
x3 = np.loadtxt("C:\\Users\\Osman\\Downloads\\Burrau_RK4.txt", unpack=True)[6][::50]
y3 = np.loadtxt("C:\\Users\\Osman\\Downloads\\Burrau_RK4.txt", unpack=True)[7][::50]


# Geen enkel idee hoe dit werkt, voor de zekerheid niet aangekomen.
# de fps kan je hier wel aanpassen naar keuze
FFMpegWriter = manimation.writers['ffmpeg']
metadata = dict(title='Movie Test', artist='Matplotlib',
                comment='Movie support!')
writer = FFMpegWriter(fps=30, metadata=metadata)


fig = plt.figure()

# de plots voor de trails
l1, = plt.plot([], [], color = 'black')
l2, = plt.plot([], [], color = 'red')
l3, = plt.plot([], [], color = 'yellow')

# de plots voor de sterretjes :D
k1, = plt.plot([], [], color = 'black' , marker = '*')
k2, = plt.plot([], [], color = 'red' , marker = '*')
k3, = plt.plot([], [], color = 'yellow' , marker = '*')


plt.xlim(-5, 5)
plt.ylim(-5, 5)

# definieer de lijsten waar de punten voor de lijnplots in moeten
x1_, y1_ = [], []
x2_, y2_ = [], []
x3_, y3_ = [], []


with writer.saving(fig, "burrau_2d.mp4", dpi = 100):
    for i in range(len(x1)):

        # steekt in de sterretjesplot de huidige posities
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


        # dit is basically voor de trials te krijgen, het nummer kan zonder problemen naar wens aangepast worden
        if i >= 50:
            l1.set_data(x1_[i-50:i], y1_[i-50:i])
            l2.set_data(x2_[i-50:i], y2_[i-50:i])
            l3.set_data(x3_[i-50:i], y3_[i-50:i])
        else:
            l1.set_data(x1_, y1_)
            l2.set_data(x2_, y2_)
            l3.set_data(x3_, y3_)

        # de figuur wordt als frame in de video gestopt
        # hierna wordt de figuur ge-reset
        writer.grab_frame()

