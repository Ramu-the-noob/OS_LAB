#include "stdio.h"

struct Process{
    int pid;
    int at;
    int bt;
    int ct;
    int wt;
    int tat;
    int rt;
};

int main(){

    int totalTime = 0;
    int done = 0;

    printf("enter number of processes : ");
    int numProcess;
    scanf("%d", &numProcess);

    struct Process process[numProcess];

    for(int i = 0; i < numProcess; i ++){
        printf("enter AT of process %d : ", i);
        scanf("%d", &process[i].at);

        printf("enter BT of process %d : ", i);
        scanf("%d", &process[i].bt);

        struct Process[i].pid = i;
        struct Process[i].rt = struct Process[i].bt;
    }



    while(done != numProcess){
        int minTime = 100000;
        int smallIndex = -1;

        for(int i = 0; i < numProcess; i ++){
            if(process[i].at <= totalTime && process[i].rt > 0 && process[i].rt < minTime){
                minTime = process[i].rt;
                smallIndex = i;
            }
        }
        if(smallIndex == -1){
            totalTime++;
            continue;
        }

        process[smallIndex].rt--;
        totalTime++;

        if(process[smallIndex].rt == 0){
            process[smallIndex].ct = totalTime;
            process[smallIndex].tat = process[smallIndex].ct - process[smallIndex].at;
            process[smallIndex].wt = process[smallIndex].tat - process[smallIndex].bt;

            done++;
        }

    }

    printf("results : \n");
    for(int i = 0; i < numProcess; i++){
        printf("process %d \n burst time : %d \n arrival time : %d : \n Completion time : %d \n turn around time : %d \n waiting time : %d ",i, process[i].bt, process[i]. at, process[i]. ct, process[i].tat, process[i]. wt);
        printf("\n");
    }

}

//learnt




















