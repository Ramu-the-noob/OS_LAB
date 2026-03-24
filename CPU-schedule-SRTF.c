#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;
    int at;
    int bt;
    int rt;
    int ct;
    int tat; // ct - at
    int wt; //tat - bt
};

int main() {
    int n, Completed = 0 , TotalWt = 0, CurrentTime = 0;

    printf("enter number of processes: ");
    scanf("%d", &n);

    struct Process process[n];

    for (int i = 0; i < n; i++) {
        printf("enter PID: ");
        scanf("%d", &process[i].pid);
        printf("enter AT: ");
        scanf("%d", &process[i].at);
        printf("enter BT: ");
        scanf("%d", &process[i].bt);
        process[i].rt = process[i].bt;
    }
    while (Completed != n) {
        int MinRT = INT_MAX;
        int Shortest_index = -1;

        for (int i = 0; i < n; i++) {
            if (process[i].at <= CurrentTime && process[i].rt > 0 && process[i].rt <= MinRT ) {
                MinRT = process[i].rt;
                Shortest_index = i;
            }
        }
        if (Shortest_index == -1) {
            CurrentTime++;
            continue;
        }

        process[Shortest_index].rt--;
        CurrentTime++;

        if (process[Shortest_index].rt == 0) {
            Completed++;
            process[Shortest_index].ct = CurrentTime;
            process[Shortest_index].tat =  process[Shortest_index].ct - process[Shortest_index].at;
            process[Shortest_index].wt = process[Shortest_index].tat - process[Shortest_index].bt;
            TotalWt += process[Shortest_index].wt;
        }
    }

    // Print the result table
    printf("\nSRTF Scheduling Results:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
            process[i].pid, process[i].at, process[i].bt, process[i].ct, process[i].tat, process[i].wt);
    }

    printf("\nAverage Waiting Time = %d\n", TotalWt / n);


    return 0;
}
