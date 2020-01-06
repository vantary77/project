import matplotlib.pyplot as plt
img = plt.imread("pic1.jpg")
x = range(300)
plt.imshow(img, extent=[0, 2, 0, 2])
#ax.plot(x, x, '--', linewidth=5, color='firebrick')
#fig, ax = plt.subplots()
plt.show()
