#include <iostream>
#include <set>
#include <queue>

using namespace std;

#define BOARD_SIDE_SIZE 8

void addEdge(set<pair<int, int> > graph[], int u, int v, int weight);
int* getMST(set<pair<int, int> > graph[], int size);
int getMinKeyNotInMST(int keys[], int includedInMst[], int size);
int getDistance(set<pair<int, int> > graph[], int parents[], int size);
int getEdgeDistance(set<pair<int, int> > graph[], int u, int v);

int main()
{
    int m, n;
    cin >> m >> n;
    while (m > 0)
    {
        set<pair<int, int> > graph[m];
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
        cin >> m >> n;
    }

    return 0;
}

int getDistance(set<pair<int, int> > graph[], int parents[], int size){
    int totalDistance = 0;
    for (int i=0; i<size; i++) {
        if (parents[i] != -1) {
            totalDistance += getEdgeDistance(graph, i, parents[i]);
        }
    }
    return totalDistance;
}

int* getMST(set<pair<int, int> > graph[], int size)
{
    int* parents = (int*)malloc(size * sizeof(int));
    int includedInMst[size];
    int keys[size];

    for (int i=0; i<size; i++) {
        keys[i] = INT32_MAX;
        includedInMst[i] = false;
    }

    keys[0] = 0;
    parents[0] = -1;

    for (int i=0; i<size-1; i++) {
        int minKey = getMinKeyNotInMST(keys, includedInMst, size);
        includedInMst[minKey] = true;

        std::set<pair<int, int> >::iterator it;
        for (it = graph[minKey].begin(); it != graph[minKey].end(); ++it)
        {
            int neighborIndex = (*it).first;
            int neighborWeight = (*it).second;

            if (!includedInMst[neighborIndex] && neighborWeight < keys[neighborIndex]) {
                parents[neighborIndex] = minKey;
                keys[neighborIndex] = neighborWeight;
            }
        }
    }

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

void addEdge(set<pair<int, int> > graph[], int u, int v, int weight)
{
    pair<int, int> vPair = make_pair(v, weight);
    graph[u].insert(vPair);
    pair<int, int> uPair = make_pair(u, weight);
    graph[v].insert(uPair);
}

int getEdgeDistance(set<pair<int, int> > graph[], int u, int v)
{   
    std::set<pair<int, int> >::iterator it;
    for (it = graph[u].begin(); it != graph[v].end(); ++it)
    {
        int neighborIndex = (*it).first;
        int neighborWeight = (*it).second;
        if (neighborIndex == v) {
            return neighborWeight;
        }
    }
    return INT32_MAX;
}
