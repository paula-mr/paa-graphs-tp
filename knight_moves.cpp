#include <iostream>
#include <set>

using namespace std;

#define BOARD_SIDE_SIZE 8

void addEdge(set<int> graph[], int u, int v);
void printGraph(set<int> graph[]);
void initializeGraph(set<int> graph[]);
int getNodeIdentifier(int i, int j);
int getNodeIdentifierFromBoard(char v[2]);

int main()
{
    set<int> graph[BOARD_SIDE_SIZE * 10 + BOARD_SIDE_SIZE];
    initializeGraph(graph);

    char v1[3], v2[3];

    cin >> v1 >> v2;
    int i1 = getNodeIdentifierFromBoard(v1);
    int i2 = getNodeIdentifierFromBoard(v2);

    cout << i1 << ' ' << i2 << endl;

    return 0;
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

void printGraph(set<int> graph[])
{
    std::set<int>::iterator it;
    for (int i = 0; i < BOARD_SIDE_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIDE_SIZE; j++)
        {
            int identifier = getNodeIdentifier(i, j);
            cout << "vertex " << identifier;
            for (it = graph[identifier].begin(); it != graph[identifier].end(); ++it)
            {
                cout << " -> " << *it;
            }
            cout << endl;
        }
    }
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
            if (i + 2 < BOARD_SIDE_SIZE && j - 1 > 0)
            {
                int possiblePlace = getNodeIdentifier(i + 2, j - 1);
                addEdge(graph, currentPlace, possiblePlace);
            }
            if (i - 2 > 0 && j + 1 < BOARD_SIDE_SIZE)
            {
                int possiblePlace = getNodeIdentifier(i - 2, j + 1);
                addEdge(graph, currentPlace, possiblePlace);
            }
            if (i - 2 > 0 && j - 1 > 0)
            {
                int possiblePlace = getNodeIdentifier(i - 2, j - 1);
                addEdge(graph, currentPlace, possiblePlace);
            }
            if (j + 2 < BOARD_SIDE_SIZE && i + 1 < BOARD_SIDE_SIZE)
            {
                int possiblePlace = getNodeIdentifier(i + 1, j + 2);
                addEdge(graph, currentPlace, possiblePlace);
            }
            if (j + 2 < BOARD_SIDE_SIZE && i - 1 > 0)
            {
                int possiblePlace = getNodeIdentifier(i - 1, j + 2);
                addEdge(graph, currentPlace, possiblePlace);
            }
            if (j - 2 > 0 && i + 1 < BOARD_SIDE_SIZE)
            {
                int possiblePlace = getNodeIdentifier(i + 1, j - 2);
                addEdge(graph, currentPlace, possiblePlace);
            }
            if (j - 2 > 0 && i - 1 > 0)
            {
                int possiblePlace = getNodeIdentifier(i - 1, j - 2);
                addEdge(graph, currentPlace, possiblePlace);
            }
        }
    }
}
