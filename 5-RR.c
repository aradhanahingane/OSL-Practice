#include <stdio.h>

int main() {
    int n, time_quantum, bt[20], wt[20], tat[20], rem_bt[20], at[20];
    int total_wt = 0, total_tat = 0, time = 0;
    float avg_wt, avg_tat;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Arrival Time and Burst Time for each process:\n");
    for(int i = 0; i < n; i++) {
        printf("P[%d] Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("P[%d] Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
        rem_bt[i] = bt[i];
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &time_quantum);

    // Process until all processes are completed
    int done;
    while(1) {
        done = 1;
        // Traverse all processes
        for(int i = 0; i < n; i++) {
            // Process only if it has arrived and has remaining burst time
            if(at[i] <= time && rem_bt[i] > 0) {
                done = 0;
                
                if(rem_bt[i] > time_quantum) {
                    time += time_quantum;
                    rem_bt[i] -= time_quantum;
                }
                else {
                    time += rem_bt[i];
                    wt[i] = time - bt[i] - at[i];  // Subtract arrival time
                    rem_bt[i] = 0;
                }
            }
        }
        
        // If no process is ready to execute, increment time
        if(done == 1) {
            int all_completed = 1;
            for(int i = 0; i < n; i++) {
                if(rem_bt[i] > 0) {
                    all_completed = 0;
                    if(at[i] > time) {
                        time = at[i];
                    }
                }
            }
            if(all_completed) break;
            done = 0;
        }
    }

    // Calculate turnaround time
    for(int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        total_wt += wt[i];
        total_tat += tat[i];
    }

    avg_wt = (float)total_wt / n;
    avg_tat = (float)total_tat / n;

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(int i = 0; i < n; i++) {
        printf("P[%d]\t%d\t\t%d\t\t%d\t\t%d\n", i+1, at[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f", avg_wt);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);

    return 0;
}