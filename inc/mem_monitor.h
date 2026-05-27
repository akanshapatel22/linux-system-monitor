#ifndef MEM_MONITOR_H
#define MEM_MONITOR_H

struct MemStats {
    unsigned long total_mb;
    unsigned long used_mb;
    unsigned long free_mb;
    unsigned long cache_mb;
};

class MemMonitor {
public:
    MemMonitor();
    MemStats getStats();
};

#endif /* MEM_MONITOR_H */
