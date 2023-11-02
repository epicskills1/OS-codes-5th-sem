#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int finish[MAX_PROCESSES];

int num_processes;
int num_resources;

int work[MAX_RESOURCES];
int safe_sequence[MAX_PROCESSES];
int sequence_index = 0;

void initialize() {
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);
   
    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);

    printf("Enter the available resources:\n");
    for (int i = 0; i < num_resources; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter the maximum demand for each process:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("For Process %d: ", i);
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &maximum[i][j]);
            need[i][j] = maximum[i][j];
        }
    }

    printf("Enter the current resource allocation:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("For Process %d: ", i);
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] -= allocation[i][j];
        }
    }
}

int is_safe() {
    for (int i = 0; i < num_resources; i++) {
        work[i] = available[i];
    }

    for (int i = 0; i < num_processes; i++) {
        finish[i] = 0;
    }

    int num_finished = 0;
    while (num_finished < num_processes) {
        int found = 0;

        for (int i = 0; i < num_processes; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < num_resources; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }

                if (j == num_resources) {
                    for (int k = 0; k < num_resources; k++) {
                        work[k] += allocation[i][k];
                    }
                    finish[i] = 1;
                    safe_sequence[sequence_index++] = i;
                    found = 1;
                    num_finished++;
                }
            }
        }

        if (!found) {
            return 0;
        }
    }
    return 1;
}

int main() {
    initialize();

    if (is_safe()) {
        printf("Safe sequence: ");
        for (int i = 0; i < num_processes; i++) {
            printf("%d ", safe_sequence[i]);
        }
        printf("\n");
    } else {
        printf("No safe sequence exists.\n");
    }

    return 0;
