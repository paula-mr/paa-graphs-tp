#include <iostream>
#include <set>
#include <queue>

using namespace std;

#define BOARD_SIDE_SIZE 8

void addEdge(set<int> graph[], int u, int v);
void initializeGraph(set<int> graph[]);
int getNodeIdentifier(int i, int j);
int getNodeIdentifierFromBoard(char v[2]);
int getMinDistance(set<int> graph[], int source, int end);

int main()
{
    char v1[3], v2[3];

    set<int> graph[BOARD_SIDE_SIZE * 10 + BOARD_SIDE_SIZE];
    initializeGraph(graph);

    while (cin >> v1)
    {
        cin >> v2;
        int i1 = getNodeIdentifierFromBoard(v1);
        int i2 = getNodeIdentifierFromBoard(v2);

        int minDistance = getMinDistance(graph, i1, i2);
        cout << "To get from " << v1 << " to " << v2 << " takes " << minDistance << " knight moves.\n";
    }

    return 0;
}

int getMinDistance(set<int> graph[], int source, int end)
{
    int distances[BOARD_SIDE_SIZE * 10 + BOARD_SIDE_SIZE];
    queue<int> priorityQueue;

    for (int i = 0; i < BOARD_SIDE_SIZE; i++) // horizontal
    {
        for (int j = 0; j < BOARD_SIDE_SIZE; j++) // vertical
        {
            int currentPlace = getNodeIdentifier(i, j);
            distances[currentPlace] = INT32_MAX;
        }
    }

    distances[source] = 0;
    priorityQueue.push(source);

    while (!priorityQueue.empty())
    {
        int item = priorityQueue.front();
        priorityQueue.pop();
        std::set<int>::iterator it;
        for (it = graph[item].begin(); it != graph[item].end(); ++it)
        {
            if (distances[*it] > distances[item] + 1)
            {
                distances[*it] = distances[item] + 1;
                priorityQueue.push(*it);
            }
        }
    }

    return distances[end];
}

int getNodeIdentifierFromBoard(char v[2])
{
    int horizontal = v[0];
    int vertical = v[1];
    return ((horizontal - 97) * 10) + (vertical - 49);
}

int getNodeIdentifier(int i, int j)
{
    return (i * 10) + j;
}

void addEdge(set<int> graph[], int u, int v)
{
    graph[u].insert(v);
    graph[v].insert(u);
}

void initializeGraph(set<int> graph[])
{
    for (int i = 0; i < BOARD_SIDE_SIZE; i++) // horizontal
    {
        for (int j = 0; j < BOARD_SIDE_SIZE; j++) // vertical
        {
            int currentPlace = getNodeIdentifier(i, j);
            if (i + 2 < BOARD_SIDE_SIZE && j + 1 < BOARD_SIDE_SIZE)
            {
                int possiblePlace = getNodeIdentifier(i + 2, j + 1);
                addEdge(graph, currentPlace, possiblePlace);
            }
            if (i + 2 < BOARD_SIDE_SIZE && j - 1 >= 0)
            {
                int possiblePlace = getNodeIdentifier(i + 2, j - 1);
                addEdge(graph, currentPlace, possiblePlace);
            }
            if (i - 2 >= 0 && j + 1 < BOARD_SIDE_SIZE)
            {
                int possiblePlace = getNodeIdentifier(i - 2, j + 1);
                addEdge(graph, currentPlace, possiblePlace);
            }
            if (i - 2 >= 0 && j - 1 >= 0)
            {
                int possiblePlace = getNodeIdentifier(i - 2, j - 1);
                addEdge(graph, currentPlace, possiblePlace);
            }
            if (j + 2 < BOARD_SIDE_SIZE && i + 1 < BOARD_SIDE_SIZE)
            {
                int possiblePlace = getNodeIdentifier(i + 1, j + 2);
                addEdge(graph, currentPlace, possiblePlace);
            }
            if (j + 2 < BOARD_SIDE_SIZE && i - 1 >= 0)
            {
                int possiblePlace = getNodeIdentifier(i - 1, j + 2);
                addEdge(graph, currentPlace, possiblePlace);
            }
            if (j - 2 >= 0 && i + 1 < BOARD_SIDE_SIZE)
            {
                int possiblePlace = getNodeIdentifier(i + 1, j - 2);
                addEdge(graph, currentPlace, possiblePlace);
            }
            if (j - 2 >= 0 && i - 1 >= 0)
            {
                int possiblePlace = getNodeIdentifier(i - 1, j - 2);
                addEdge(graph, currentPlace, possiblePlace);
            }
        }
    }
}
