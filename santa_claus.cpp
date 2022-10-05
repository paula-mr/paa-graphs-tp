#include <iostream>

using namespace std;

#define BOARD_SIDE_SIZE 8

void addEdge(short int** graph, int u, int v, int weight);
int* getMST(short int** graph, int size);
int getMinKeyNotInMST(int keys[], int includedInMst[], int size);
int getDistance(short int** graph, int parents[], int size);
int getEdgeDistance(short int** graph, int u, int v);

int main()
{
    int m, n;
    cin >> m >> n;
    while (m > 0)
    {
        short int** graph = (short int**) malloc(m*sizeof(int *));
        for (int i=0; i<m; i++) {
            graph[i] = (short int*) malloc(m*sizeof(int *));
            for (int j=0; j<m; j++) {
                graph[i][j] = INT16_MAX;
            }
        }

        for (int i = 0; i < n; i++)
        {
            int city1, city2, distance;
            cin >> city1 >> city2 >> distance;
            addEdge(graph, city1, city2, distance);
            addEdge(graph, city2, city1, distance);
        }

        int* parents = getMST(graph, m);
        int totalDistance = getDistance(graph, parents, m);
        cout << totalDistance << "\n";

        for (int i=0; i<m; i++) {
            free(graph[i]);
        }
        free(graph);
        free(parents);
        
        cin >> m >> n;
    }

    return 0;
}

int getDistance(short int** graph, int parents[], int size){
    int totalDistance = 0;
    for (int i=1; i<size; i++) {
        totalDistance += graph[i][parents[i]];
    }
    return totalDistance;
}

int* getMST(short int** graph, int size)
{
    int* parents = (int*)malloc(size * sizeof(int));
    int* includedInMst = (int*)malloc(size * sizeof(int));
    int* keys = (int*)malloc(size * sizeof(int));

    for (int i=0; i<size; i++) {
        keys[i] = INT16_MAX;
        includedInMst[i] = false;
    }

    keys[0] = 0;
    parents[0] = -1;

    for (int i=0; i<size-1; i++) {
        int minKey = getMinKeyNotInMST(keys, includedInMst, size);
        includedInMst[minKey] = true;

        for (int j=0; j<size; j++) {
            if (!includedInMst[j] && graph[minKey][j] < keys[j]) {
                parents[j] = minKey;
                keys[j] = graph[minKey][j];
            }
        }
    }

    free(includedInMst);
    free(keys);
    return parents;
}

int getMinKeyNotInMST(int keys[], int includedInMst[], int size) {
    int minValue = INT32_MAX, minIndex;

    for (int i=0; i<size; i++) {
        if (!includedInMst[i] && keys[i] < minValue) {
            minValue = keys[i];
            minIndex = i;
        }
    }

    return minIndex;
}

void addEdge(short int** graph, int u, int v, int weight)
{
    graph[u][v] = weight;
    graph[v][u] = weight;
}
