#ifndef CPU_MONITOR_H
#define CPU_MONITOR_H

struct CPUStats {
    float usage_percent;
    float user_percent;
    float system_percent;
    float idle_percent;
};

class CPUMonitor {
public:
    CPUMonitor();
    CPUStats getStats();

private:
    unsigned long prev_idle;
    unsigned long prev_total;
    void readStats(unsigned long &idle, unsigned long &total);
};

#endif /* CPU_MONITOR_H */
