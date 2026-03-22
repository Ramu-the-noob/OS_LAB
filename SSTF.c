#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, total = 0;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    int req[n], visited[n];

    printf("Enter the requests:\n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &req[i]);
        visited[i] = 0;
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("\nStep\tFrom\tTo\tMovement\n");
    printf("--------------------------------\n");

    for(int step = 0; step < n; step++) {

        int min = 100000, index = -1;

        for(int i = 0; i < n; i++) {
            if(!visited[i]) {
                int dist = abs(head - req[i]);
                if(dist < min) {
                    min = dist;
                    index = i;
                }
            }
        }

        printf("%d\t%d\t%d\t%d\n", step+1, head, req[index], min);

        total += min;
        head = req[index];
        visited[index] = 1;
    }

    printf("--------------------------------\n");
    printf("Total head movement = %d\n", total);

    return 0;
}
