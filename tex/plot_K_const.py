import matplotlib.pyplot as plt
import numpy as np
import sys

x=np.array([9,16,25,36,49,64,81,100])
y_pthread = np.loadtxt("bash_output_final_pthread.txt",delimiter=" ",dtype="double")
y_openmp = np.loadtxt("bash_output_final_openmp.txt",delimiter=" ",dtype="double")
plt.plot(x,y_pthread,marker=".",label="Pthread")
plt.plot(x,y_openmp,marker=".",label="OpenMP") 
plt.xlabel("$N$ value")
plt.ylabel("Time Taken")
plt.title("Time Taken($\u03BC$s) vs Value of $N$")
plt.legend() 
plt.grid()
plt.savefig(sys.argv[1])







