#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int n, bt[20], wt[20], tat[20], p[20], total_wt = 0, total_tat = 0;
    float avg_wt, avg_tat;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Burst Time for each process:\n");
    for(int i = 0; i < n; i++) {
        printf("P[%d]: ", i + 1);
        scanf("%d", &bt[i]);
        p[i] = i + 1;
    }

    // Sort burst time in ascending order using selection sort
    for(int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for(int j = i + 1; j < n; j++) {
            if(bt[j] < bt[min_idx])
                min_idx = j;
        }
        // Swap burst time
        swap(&bt[min_idx], &bt[i]);
        // Swap process id
        swap(&p[min_idx], &p[i]);
    }

    wt[0] = 0;
    // Calculate waiting time
    for(int i = 1; i < n; i++) {
        wt[i] = wt[i-1] + bt[i-1];
        total_wt += wt[i];
    }

    // Calculate turnaround time
    for(int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        total_tat += tat[i];
    }

    avg_wt = (float)total_wt / n;
    avg_tat = (float)total_tat / n;

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(int i = 0; i < n; i++) {
        printf("P[%d]\t%d\t\t%d\t\t%d\n", p[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f", avg_wt);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);

    return 0;
}