import numpy as np
import matplotlib.pyplot as plt
# print(np.shape([ [ [ [1],[2] ],[ [3],[4] ],[ [5],[6] ] ], [ [ [7],[8] ],[ [9],[10] ],[ [11],[12] ] ] ]))
# print(np.array([ [ [ [1],[2] ],[ [3],[4] ],[ [5],[6] ] ], [ [ [7],[8] ],[ [9],[10] ],[ [11],[12] ] ] ]))

# print(np.shape([1,2,3,4]))

x = np.ones((2,2))
x[0,0]=4
x[0,1]=6
x[1,0]=7
x[1,1]=8
y = np.ones((2,2))
y[0,0]=1
y[0,1]=2
y[1,0]=3
y[1,1]=4
print(np.sum(x - y,0))

# make data
x = np.linspace(-20, 10, 100)
y = 4 + 2 * np.sin(2 * x)

plt.plot(x, y, linewidth=2.0)
plt.plot(x**2-x+1)
plt.show()