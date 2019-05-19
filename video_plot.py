import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as pat
import matplotlib.cm as cm

domain = np.genfromtxt("20x20rand30.dat", skip_header=2)

dom_x, dom_y = domain.shape

plt.figure()
plt.imshow(domain,cmap=cm.jet,interpolation='nearest')
plt.show()

