#include <iostream>
#include <set>
#include <queue>

using namespace std;

#define BOARD_SIDE_SIZE 8

void addEdge(set<pair<int, int> > graph[], int u, int v, int weight);
void printGraph(set<pair<int, int> > graph[], int size);
int getMinDistance(set<pair<int, int>> graph[], int size);

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

        int totalDistance = 0;
        cout << totalDistance << "\n";
        cin >> m >> n;
    }

    return 0;
}

int getMinDistance(set<pair<int, int>> graph[], int size)
{
    int distances[size];
    return 0;
}

void addEdge(set<pair<int, int> > graph[], int u, int v, int weight)
{
    pair<int, int> uPair;
    uPair.first = v;
    uPair.second = weight;
    graph[u].insert(uPair);
    pair<int, int> vPair;
    uPair.first = u;
    uPair.second = weight;
    graph[v].insert(vPair);
}

void printGraph(set<pair<int, int> > graph[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << "CITY " << i << " -> ";
        std::set<pair<int, int> >::iterator it;
        for (it = graph[i].begin(); it != graph[i].end(); ++it)
        {
            cout << "(" << (*it).first << ", " << (*it).second << ") ";
        }
        cout << endl;
    }
}