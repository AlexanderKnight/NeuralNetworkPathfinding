import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as pat
import matplotlib.axes as ax
import matplotlib.cm as cm


# Match variables below to run
domain_file = "20x20rand30.dat"
seekers = 50
cores = 2
domain_x = 20
domain_y = 20
iterations = 200

# Should not need to adjust anything below here
domain = np.genfromtxt(domain_file, skip_header=2)
pos_data = np.zeros(14)

dom_x, dom_y = domain.shape


for time in range(0,iterations):
    print(time)
    plt.figure()
    plt.title("Time = {0}".format(time))
    ax = plt.gca()
    ax.set_xticks(np.arange(-.5,20,1))
    ax.set_yticks(np.arange(-.5,20,1))
    ax.set_xticklabels(np.arange(0, 20, 1))
    ax.set_yticklabels(np.arange(0, 20, 1))
    plt.imshow(domain,cmap=cm.jet,interpolation='nearest')
    for i in range(0,cores):
        for j in range(0,int(seekers/cores)):
            
            filename = "PositionalData/pos_procseeker{0}_Iter{1}.dat".format(1000*i+j, time)
            temp_plot=np.genfromtxt(filename)
            plt.plot(temp_plot[:,0],temp_plot[:,1], 'x')
    #plt.show()
    plt.savefig("PositionalData/Positions_{0}.png".format(time), dpi=200)
    plt.close()

