import matplotlib.pyplot as plt
import numpy as np

file = open("D://Visual_code//Cpp//BisectionMethod.txt")
Bisection = np.asfarray((file.read()).split('\n'))

file = open("D://Visual_code//Cpp//NewtonsMethod.txt")
Newtons = np.asfarray((file.read()).split('\n'))

iteration = np.array(range(1, len(Bisection)+1))
iteration_ = np.array(range(1, len(Newtons)+1))

plt.plot(iteration, Bisection, color="red", label='Bisection')
plt.plot(iteration_, Newtons, color='blue', label='Newtons')
plt.legend()
plt.show()
