#include <iostream>
using namespace std;

struct Process {
    int pid;            // process ID
    int bt;             // burst time
    int at;             // arrival time
    int pr;             // priority (lower value = higher priority)
    int remaining_bt;   // remaining burst time
    int ct;             // completion time
    int tat;            // turnaround time
    int wt;             // waiting time
    bool done;          // completion flag
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    Process p[20];

    cout << "\nEnter the details of each process:\n";
    cout << "(Format: Arrival_Time Burst_Time Priority)\n";

    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << ": ";
        cin >> p[i].at >> p[i].bt >> p[i].pr;

        p[i].pid = i + 1;
        p[i].remaining_bt = p[i].bt;
        p[i].done = false;
    }

    int completed = 0, current_time = 0;

    while (completed != n) {
        int idx = -1;
        int highest_priority = 999999;

        // Select process with highest priority (smallest number)
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= current_time && p[i].pr < highest_priority) {
                highest_priority = p[i].pr;
                idx = i;
            }
        }

        if (idx != -1) {
            p[idx].remaining_bt--;

            if (p[idx].remaining_bt == 0) {
                p[idx].done = true;
                p[idx].ct = current_time + 1;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                completed++;
            }
        }

        current_time++;
    }

    // Output results
    cout << "\n\n---------- Pre-emptive Priority Scheduling Result ----------\n";
    cout << "PID\tAT\tBT\tPR\tCT\tTAT\tWT\n";

    float avg_tat = 0, avg_wt = 0;

    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].pr << "\t"
             << p[i].ct << "\t"
             << p[i].tat << "\t"
             << p[i].wt << endl;

        avg_tat += p[i].tat;
        avg_wt += p[i].wt;
    }

    cout << "\nAverage Turnaround Time: " << avg_tat / n;
    cout << " ms\nAverage Waiting Time: " << avg_wt / n << " ms\n";

    return 0;
}

