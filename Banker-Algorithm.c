#include <stdio.h>

/*
 * need
 * allocated
 * max
 * available
 * sequence
 */

int main() {
    int m = 5, n = 3;
    int max[5][3]= {
        {7,5,3},
        {3,2,2},
        {9,0,2},
        {2,2,2},
        {4,3,3}
    };
    int allocated[5][3] = {
        {0,1,0},
        {2,0,0},
        {3,0,2},
        {2,1,1},
        {0,0,2}
    };
    int need[5][3];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            need[i][j] = max[i][j] - allocated[i][j];
        }
    }
    int available[3] = {3, 3, 2};
    int sequence[5];
    int finish[5] = {0, 0, 0, 0, 0};
    int sequence_index = 0;

    
    for (int k = 0; k < m; k++) {
        for (int i = 0; i < m; i++) {
            if (finish[i] == 0) {
                int can_run = 1;

                // Check if ALL needed resources for this process are <= available
                for (int j = 0; j < n; j++) {
                    if (need[i][j] > available[j]) {
                        can_run = 0; // It needs more than we have
                        break;
                    }
                }

                // If it can run, execute it
                if (can_run == 1) {
                    sequence[sequence_index++] = i; // Add to safe sequence
                    finish[i] = 1;                  // Mark as finished

                    // Return allocated resources back to the available pool
                    for (int y = 0; y < n; y++) {
                        available[y] += allocated[i][y];
                    }
                }
            }
        }
    }

    // 3. Verify if the system is safe
    // If sequence_index equals the total number of processes, it's safe.
    if (sequence_index == m) {
        printf("System is SAFE.\nSafe Sequence: ");
        for (int i = 0; i < m; i++) {
            printf("P%d ", sequence[i]);
        }
        printf("\n");
    } else {
        printf("System is NOT SAFE. Deadlock detected.\n");
    }

    return 0;
}
