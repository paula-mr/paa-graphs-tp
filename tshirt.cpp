#include <iostream>
#include <string>
#include <queue>

using namespace std;

void initializeGraph(int** graph, int graphSize, int nVolunteers, int nTshirts);
int getSizeIdentifier(string size, int nVolunteers);
int fordFulkerson(int** graph, int s, int t, int graphSize);
bool bfs(int** graph, int s, int t, int graphSize, int* parents);

int main()
{
    int t;
    cin >> t;

    for (int i=0; i<t; i++) {
        int nTshirts, nVolunteers;
        cin >> nTshirts >> nVolunteers;
        int graphSize = nVolunteers+6+2;

        int** graph = (int**) malloc(graphSize*sizeof(int*));
        initializeGraph(graph, graphSize, nVolunteers, nTshirts);

        for (int j=0; j<nVolunteers; j++) {
            string size1, size2;
            cin >> size1 >> size2;
            int size1Id = getSizeIdentifier(size1, nVolunteers);
            graph[j+1][size1Id] = 1;
            int size2Id = getSizeIdentifier(size2, nVolunteers);
            graph[j+1][size2Id] = 1;
        }

        int maxFlow = fordFulkerson(graph, 0, graphSize-1, graphSize);
        if (maxFlow == nVolunteers) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}

int fordFulkerson(int** graph, int s, int t, int graphSize) {
    int** residualGraph = (int**) malloc(graphSize*sizeof(int*));
    for (int i=0; i<graphSize; i++) {
        residualGraph[i] = (int*) malloc(graphSize*sizeof(int));
        for (int j=0; j<graphSize; j++) {
            residualGraph[i][j] = graph[i][j];
        }
    }

    int* parents = (int*) malloc(graphSize*sizeof(int));
    int maxFlow = 0;

    while (bfs(residualGraph, s, t, graphSize, parents)) {
        int path = INT16_MAX;
        for (int i=t; i != s; i = parents[i]) {
            int parent = parents[i];
            if (residualGraph[parent][i] < path) {
                path = residualGraph[parent][i];
            }
        }

        // update residuals
        for (int i=t; i != s; i = parents[i]) {
            int parent = parents[i];
            residualGraph[parent][i] -= path;
            residualGraph[i][parent] += path;
        }
        maxFlow += path;
    }

    return maxFlow;
}

bool bfs(int** graph, int s, int t, int graphSize, int* parents) {
    bool* visitedNodes = (bool*) malloc(graphSize * sizeof(bool));
    queue<int> priorityQueue;

    for (int i = 0; i < graphSize; i++) {
        visitedNodes[i] = false;
    }

    visitedNodes[s] = true;
    priorityQueue.push(s);
    parents[s] = -1;

    while(!priorityQueue.empty()) {
        int current = priorityQueue.front();
        priorityQueue.pop();

        for (int i=0; i<graphSize; i++) {   
            if (!visitedNodes[i] && graph[current][i] > 0) {
                parents[i] = current;
                if (i == t) { // if we reach the sink node we can interrupt
                    return true;
                }
                priorityQueue.push(i);
                visitedNodes[i] = true;
            }
        }
    }

    return false;
}

void initializeGraph(int** graph, int graphSize, int nVolunteers, int nTshirts) {
    int amountEachShirt = nTshirts/6;

    for (int i=0; i<graphSize; i++) {
        graph[i] = (int*) malloc(graphSize*sizeof(int));
        for (int j=0; j<graphSize; j++) {
            graph[i][j] = 0;
        }
    }

    // initialize source node to volunteers
    for (int i=0; i<nVolunteers; i++) {
        graph[0][i+1] = 1;
    }

    // initialize shirt nodes to sink
    for (int i=0; i<6; i++) {
        graph[i+1+nVolunteers][graphSize-1] = amountEachShirt;
    }

}

int getSizeIdentifier(string size, int nVolunteers) {
    int sizeValue = 0;

    if (size == "XS") sizeValue = 0;
    else if (size == "S") sizeValue = 1;
    else if (size == "M") sizeValue = 2;
    else if (size == "L") sizeValue = 3;
    else if (size == "XL") sizeValue = 4;
    else if (size == "XXL") sizeValue = 5;

    return sizeValue + 1 + nVolunteers;
}
