#include "proc_monitor.h"
#include <fstream>
#include <sstream>
#include <string>
#include <dirent.h>
#include <algorithm>

ProcMonitor::ProcMonitor() {}

std::vector<ProcStats> ProcMonitor::getTopProcesses(int count) {
    std::vector<ProcStats> processes;

    /* Open /proc directory to iterate over all PIDs */
    DIR *dir = opendir("/proc");
    if (!dir) return processes;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        /* Only process numeric directories (PIDs) */
        std::string name = entry->d_name;
        bool is_pid = !name.empty() &&
                      std::all_of(name.begin(), name.end(), ::isdigit);
        if (!is_pid) continue;

        int pid = std::stoi(name);
        std::string stat_path = "/proc/" + name + "/stat";
        std::string comm_path = "/proc/" + name + "/comm";

        /* Read process name */
        std::string proc_name = "unknown";
        std::ifstream comm_file(comm_path);
        if (comm_file.is_open()) {
            std::getline(comm_file, proc_name);
        }

        /* Read process stats */
        std::ifstream stat_file(stat_path);
        if (!stat_file.is_open()) continue;

        std::string stat_line;
        std::getline(stat_file, stat_line);
        std::istringstream ss(stat_line);

        unsigned long utime = 0, stime = 0;
        std::string token;
        int field = 1;

        /* Parse fields from /proc/[pid]/stat */
        while (ss >> token) {
            if (field == 14) utime = std::stoul(token);
            if (field == 15) stime = std::stoul(token);
            if (field > 15)  break;
            field++;
        }

        ProcStats ps;
        ps.pid         = pid;
        ps.name        = proc_name;
        ps.cpu_percent = (float)(utime + stime) / 100.0f;
        ps.mem_percent = 0.0f;

        processes.push_back(ps);
    }

    closedir(dir);

    /* Sort by CPU usage descending */
    std::sort(processes.begin(), processes.end(),
              [](const ProcStats &a, const ProcStats &b) {
                  return a.cpu_percent > b.cpu_percent;
              });

    /* Return top N processes */
    if ((int)processes.size() > count) {
        processes.resize(count);
    }

    return processes;
}
