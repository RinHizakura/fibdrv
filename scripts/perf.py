import os
import matplotlib.pyplot as plt
import numpy as np

os.chdir("/home/rin/Github/linux-internel/fibdrv/")

def stat(data):
    data = np.array(data)
    ret = np.zeros(data.shape[1])

    for i in range(data.shape[1]):
        tmp = data[:,i]
        mean, std = tmp.mean(), tmp.std()
        # identify outliers: 2 std = 95%
        cut_off = std * 2
        lower, upper = mean - cut_off, mean + cut_off
        tmp = tmp[tmp > lower]
        tmp = tmp[tmp < upper]
        ret[i] = tmp.mean()

    return ret

ktime_collect = []
utime_collect = []
ktou_time_collect = []

for i in range(100):
    os.system("make perf > /dev/null")
    out = np.loadtxt("out.txt", dtype = 'int',delimiter=',')
  
    ktime_collect.append(out[:,1])
    utime_collect.append(out[:,2])
    ktou_time_collect.append(out[:,3])

x = out[:,0]

ktime_collect = stat(ktime_collect)
utime_collect = stat(utime_collect)
ktou_time_collect = stat(ktou_time_collect)


plt.plot()
plt.xlabel('fib(n), n= ')
plt.ylabel('time(ns)')

plt.plot(x, ktime_collect, marker = '+', markersize = 7, label = 'kernel')
plt.plot(x, utime_collect, marker = '*', markersize = 3, label = 'user')
plt.plot(x, ktou_time_collect, marker = '^', markersize = 3, label = 'kernel to user')

plt.show()
