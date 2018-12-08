import numpy as np
import matplotlib.pyplot as plt

################################################################################################################



N, RK4, RK4_error = np.loadtxt("C:\\Users\\Joren\\source\\repos\\AS_Project\\AS_Project\\#N\\RK4.txt", unpack=True)
_, RKF45, RKF45_error = np.loadtxt("C:\\Users\\Joren\\source\\repos\\AS_Project\\AS_Project\\#N\\RKF45.txt", unpack=True)
_, Verlet, Verlet_error = np.loadtxt("C:\\Users\\Joren\\source\\repos\\AS_Project\\AS_Project\\#N\\Verlet.txt", unpack=True)
_, LF, LF_error = np.loadtxt("C:\\Users\\Joren\\source\\repos\\AS_Project\\AS_Project\\#N\\LF.txt", unpack=True)
_, FR, FR_error = np.loadtxt("C:\\Users\\Joren\\source\\repos\\AS_Project\\AS_Project\\#N\\F-R.txt", unpack=True)
_, PEFRL, PEFRL_error = np.loadtxt("C:\\Users\\Joren\\source\\repos\\AS_Project\\AS_Project\\#N\\PEFRL.txt", unpack=True)

x = np.linspace(2,7,100)
y_RK4 = 0.0180623*x**2 + 0.216879*x
y_RKF45 = 0.101767*x**2 + 0.443737*x
y_Verlet = 0.00287234*x**2 + 0.0165838*x
y_Leapfrog = 0.00134799*x**2 + 0.0143379*x
y_Forest_Ruth = 0.00429845*x**2 + 0.0276985*x
y_PEFRL = 0.00568412*x**2 + 0.0367843*x


################################################################################################################


# RKF EN RKF45
plt.figure()
plt.suptitle("Integratietijd van simulatie in functie van aantal deeltjes.")

# PLOT VOOR RK4
plt.subplot(121)
plt.title(r'RK4 ($ \ \chi_{d.o.f.}^2 = 2,1 \ . 10^{-3} \ $)')
plt.errorbar(N, RK4, yerr = RK4_error, fmt='.', markersize=8, capsize=2, color = 'sienna', label = "Meetwaarden")
plt.plot(x, y_RK4, label = r'$f(x) = 0,018 x^2 + 0,215 x$', color = 'steelblue')
plt.xlabel("Aantal deeltjes")
plt.ylabel("Integratietijd (ms)")
plt.xscale('log')
plt.yscale('log')
plt.legend()

# PLOT VOOR RKF45
plt.subplot(122)
plt.title(r'RKF45 ($ \ \chi_{d.o.f.}^2 = 0,2 \ $)')
plt.errorbar(N, RKF45, yerr = RKF45_error, fmt='.', markersize=8, capsize=2, color = 'sienna', label = "Meetwaarden")
plt.plot(x, y_RKF45, label = r'$f(x) = 0,102 x^2 + 0,444 x$', color = 'steelblue')
plt.xlabel("Aantal deeltjes")
plt.ylabel("Integratietijd (ms)")
plt.xscale('log')
plt.yscale('log')
plt.legend()
plt.show()

################################################################################################################

# FR EN PEFRL
plt.figure()
plt.suptitle("Integratietijd van simulatie in functie van aantal deeltjes.")

# PLOT VOOR FOREST-RUTH
plt.subplot(121)
plt.title(r'Forest-Ruth ($ \ \chi_{d.o.f.}^2 = 1,4 \ . 10^{-3} \ $)')
plt.errorbar(N, FR, yerr = FR_error, fmt='.', markersize=8, capsize=2, color = 'sienna', label = "Meetwaarden")
plt.plot(x, y_Forest_Ruth, label = r'$f(x) = 0,004 x^2 + 0,028 x$', color = 'steelblue')
plt.xlabel("Aantal deeltjes")
plt.ylabel("Integratietijd (ms)")
plt.xscale('log')
plt.yscale('log')
plt.legend()

# PLOT VOOR PEFRL
plt.subplot(122)
plt.title(r'PEFRL ($ \ \chi_{d.o.f.}^2 = 9,4 \ . 10^{-4} \ $)')
plt.errorbar(N, PEFRL, yerr = PEFRL_error, fmt='.', markersize=8, capsize=2, color = 'sienna', label = "Meetwaarden")
plt.plot(x, y_PEFRL, label = r'$f(x) = 0,006 x^2 + 0,037 x$', color = 'steelblue')
plt.xlabel("Aantal deeltjes")
plt.ylabel("Integratietijd (ms)")
plt.xscale('log')
plt.yscale('log')
plt.legend()
plt.show()

################################################################################################################

# LEAPFROG EN VERLET
plt.figure()
plt.suptitle("Integratietijd van simulatie in functie van aantal deeltjes.")

# PLOT VOOR LEAPFROG
plt.subplot(121)
plt.title(r'Leapfrog ($ \ \chi_{d.o.f.}^2 = 1,5 \ . 10^{-3} \ $)')
plt.errorbar(N, LF, yerr = LF_error, fmt='.', markersize=8, capsize=2, color = 'sienna', label = "Meetwaarden")
plt.plot(x, y_Leapfrog, label = r'$f(x) = 0,001 x^2 + 0,014 x$', color = 'steelblue')
plt.xlabel("Aantal deeltjes")
plt.ylabel("Integratietijd (ms)")
plt.xscale('log')
plt.yscale('log')
plt.legend()

#PLOT VOOR VERLET
plt.subplot(122)
plt.title(r'Verlet ($ \ \chi_{d.o.f.}^2 = 8,1 \ . 10^{-4} \ $)')
plt.errorbar(N, Verlet, yerr = Verlet_error, fmt='.', markersize=8, capsize=2, color = 'sienna', label = "Meetwaarden")
plt.plot(x, y_Verlet, label = r'$f(x) = 0,003 x^2 + 0,017 x$', color = 'steelblue')
plt.xlabel("Aantal deeltjes")
plt.ylabel("Integratietijd (ms)")
plt.xscale('log')
plt.yscale('log')
plt.legend()

plt.show()

################################################################################################################

# ALLEMAAL SAMEN
plt.figure()
plt.title("Vergelijking van de snelheden van de methodes.")
plt.xlabel("Aantal deeltjes")
plt.ylabel("Integratietijd (ms)")

plt.plot(N, RKF45, color = 'sienna', label = 'RKF45')
plt.scatter(N, RKF45, color = 'sienna', marker = 'd')

plt.plot(N, RK4, color = 'grey', label = 'RK4')
plt.scatter(N, RK4, color = 'grey', marker = 'd')

plt.plot(N, PEFRL, color = 'tomato', label = 'PEFRL')
plt.scatter(N, PEFRL, color = 'tomato', marker = 'd')

plt.plot(N, FR, color = 'darkorange', label = 'Forest-Ruth')
plt.scatter(N, FR, color = 'darkorange', marker = 'd')

plt.plot(N, Verlet, color = 'steelblue', label = 'Verlet')
plt.scatter(N, Verlet, color = 'steelblue', marker = 'd')

plt.plot(N, LF, color = 'orchid', label = 'Leapfrog')
plt.scatter(N, LF, color = 'orchid', marker = 'd')
plt.xscale('log')
plt.yscale('log')


plt.legend()
plt.show()

