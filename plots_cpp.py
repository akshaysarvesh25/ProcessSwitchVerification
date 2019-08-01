import numpy as np
import matplotlib.pyplot as plt
import subprocess
import time


values = np.loadtxt('simple_execs.txt')
times = np.loadtxt('simple_execs_time.txt')


P1_switch = np.loadtxt('P1_switch.txt')
P1_no_switch = np.loadtxt('P1_no_switch.txt')
P1_switch_time = np.loadtxt('P1_switch_time.txt')
P1_no_switch_time = np.loadtxt('P1_no_switch_time.txt')
P1_start = np.loadtxt('P1_start.txt')
P2_start = np.loadtxt('P2_start.txt')

#times[:] = [(i-times[0])*1e-6 for i in times]
times[:] = [(i-P1_start)*1e-6 for i in times]
P1_switch_time[:] = [(i-P1_start)*1e-6 for i in P1_switch_time]
P1_no_switch_time[:] = [(i-P1_start)*1e-6 for i in P1_no_switch_time]

print(np.gradient(values,times))

plot1, = plt.plot(times,values,'k.',label = 'values')
plot2, = plt.plot(P1_switch_time, P1_switch, 'b.', label = 'P1 with switch')
plot3, = plt.plot(P1_no_switch_time, P1_no_switch, 'g.', label = 'P1 without switch')
#plot4, = plt.plot(times,np.gradient(values,times), 'r.',label = 'Gradient')
plt.grid()
plt.xlabel('Time in seconds')
plt.ylabel('values')
plt.title('values vs time')
plt.legend()
plt.show()


plot2, = plt.plot(P1_switch_time, P1_switch, 'b.', label = 'P1 with switch')
plot3, = plt.plot(P1_no_switch_time, P1_no_switch, 'g.', label = 'P1 without switch')
plt.grid()
plt.xlabel('Time in seconds')
plt.ylabel('values')
plt.title('values vs Time in seconds')
plt.legend()
plt.show()
