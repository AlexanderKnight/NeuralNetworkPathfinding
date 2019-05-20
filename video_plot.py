import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as pat
import matplotlib.axes as ax
import matplotlib.cm as cm

domain = np.genfromtxt("20x20rand30.dat", skip_header=2)
pos_data = np.zeros(20)

dom_x, dom_y = domain.shape

plt.figure()
ax.Axes.set_xticks(np.arange(0,20,1))
ax.Axes.set_yticks(np.arange(0,20,1))
plt.imshow(domain,cmap=cm.jet,interpolation='nearest')
for i in range(0,2):
    for j in range(0,10):
        try:
            print(i,j)
            filename = "PositionalData_Bck/pos_procseeker{0}_Iter{1}.dat".format(1000*i+j, 0)
            print(filename)
            temp_plot=np.genfromtxt(filename)
            plt.plot(temp_plot[:,0],temp_plot[:,1], 'x')
        except:
            break
plt.show()

