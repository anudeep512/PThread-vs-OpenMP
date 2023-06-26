import matplotlib.pyplot as plt
import numpy as np
import sys

x=np.array([2,4,8,16,32,64])
y_pthread = np.loadtxt("bash_output_final_pthread.txt",delimiter=" ",dtype="double")
y_openmp = np.loadtxt("bash_output_final_openmp.txt",delimiter=" ",dtype="double")
plt.plot(x,y_pthread,marker=".",label="Pthread")
plt.plot(x,y_openmp,marker=".",label="OpenMP") 
plt.xlabel("No of threads")
plt.ylabel("Time Taken")
plt.title("Time Taken(\u03BC s) vs No of threads")
plt.legend() 
plt.grid()
plt.savefig(sys.argv[1])







