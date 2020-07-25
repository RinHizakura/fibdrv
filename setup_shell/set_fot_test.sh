sudo sh -c "echo 0 > /proc/sys/kernel/randomize_va_space"
sudo sh -c "echo performance >  /sys/devices/system/cpu/cpu5/cpufreq/scaling_governor"
sudo sh -c "echo 1 > /sys/devices/system/cpu/intel_pstate/no_turbo"
