#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LOCATIONS 1000  

typedef struct {
    int *connections[MAX_LOCATIONS];  
    int connection_count[MAX_LOCATIONS];
    bool explored[MAX_LOCATIONS];
} Network;

void insertConnection(Network *network, int pointA, int pointB) {
    network->connections[pointA] = realloc(network->connections[pointA], (network->connection_count[pointA] + 1) * sizeof(int));
    network->connections[pointA][network->connection_count[pointA]++] = pointB;
}

int breadthFirstSearch(Network *network, int start, int capacity) {
    int queue[MAX_LOCATIONS], front = 0, rear = 0;
    int reachable = 0;

    queue[rear++] = start;
    network->explored[start] = true;
    reachable++;

    while (front < rear && capacity > 0) {
        int levelSize = rear - front;

        for (int i = 0; i < levelSize; i++) {
            int current = queue[front++];

            for (int j = 0; j < network->connection_count[current]; j++) {
                int next = network->connections[current][j];

                if (!network->explored[next]) {
                    network->explored[next] = true;
                    queue[rear++] = next;
                    reachable++;
                }
            }
        }
        capacity--;  
    }
    return reachable;
}

int main() {
    int locations, paths, waterUnits, startPoint;

    printf("Enter number of locations: ");
    scanf("%d", &locations);
    printf("Enter number of paths: ");
    scanf("%d", &paths);
    printf("Enter available water units: ");
    scanf("%d", &waterUnits);
    printf("Enter starting location: ");
    scanf("%d", &startPoint);

    Network network = {0};  

    printf("Enter %d paths (pointA pointB):\n", paths);
    for (int i = 0; i < paths; i++) {
        int pointA, pointB;
        scanf("%d %d", &pointA, &pointB);
        insertConnection(&network, pointA, pointB);
        insertConnection(&network, pointB, pointA);
    }

    int result = breadthFirstSearch(&network, startPoint, waterUnits);
    printf("Total number of reachable locations with %d water units: %d\n", waterUnits, result);

    for (int i = 0; i < locations; i++) {
        free(network.connections[i]);
    }

    return 0;
}