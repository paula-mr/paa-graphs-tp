#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void initializeGraph(vector<int> graph[], int n, int m);
void printMap(char* graphValues, int n, int m);
void addEdge(vector<int> graph[], int u, int v);
int getNodeIdentifier(int m, int i, int j);
void projectContamination(vector<int> graph[], char* graphValues, int n, int m);

int main()
{
    int n, m;

    while (cin >> n >> m)
    {
        if (n == 0)
            break;

        vector<int> graph[2501];
        char graphValues[2501];
        initializeGraph(graph, n, m);
        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                int nodeIdentifier = getNodeIdentifier(m, i, j);
                char node;
                cin >> node;
                graphValues[nodeIdentifier] = node;
            }
        }

        projectContamination(graph, graphValues, n, m);
        printMap(graphValues, n, m);
    }

    return 0;
}

int getNodeIdentifier(int m, int i, int j) {
    return ((m*i)+j) + 1;
}

void addEdge(vector<int> graph[], int u, int v)
{   
    bool isPresent = false;
    std::vector<int>::iterator it;
    for (it = graph[u].begin(); it != graph[u].end(); ++it) {
        int x = (*it);
        if (x == v) {
            isPresent = true;
            break;
        }
    }

    if (!isPresent) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
}

void initializeGraph(vector<int> graph[], int n, int m)
{  
    for (int j = 0; j < m; j++) {
        int neighbor = getNodeIdentifier(m, 0, j);
        addEdge(graph, 0, neighbor);
    }

    for (int i = 0; i < n; i++) // horizontal
    {
        for (int j = 0; j < m; j++) // vertical
        {   
            int currentPlace = getNodeIdentifier(m, i, j);
            if (i+1 < n) {
                int neighbor = getNodeIdentifier(m, i + 1, j);
                addEdge(graph, currentPlace, neighbor);
            }
            if (i-1 >= 0) {
                int neighbor = getNodeIdentifier(m, i - 1, j);
                addEdge(graph, currentPlace, neighbor);
            }
            if (j+1 < m) {
                int neighbor = getNodeIdentifier(m, i, j+1);
                addEdge(graph, currentPlace, neighbor);
            }
            if (j-1 >= 0) {
                int neighbor = getNodeIdentifier(m, i, j-1);
                addEdge(graph, currentPlace, neighbor);
            }
        }
    }
}

void projectContamination(vector<int> graph[], char* graphValues, int n, int m) {
    bool* visitedNodes = (bool*) malloc((n*m) + 1);
    queue<int> priorityQueue;

    for (int i = 0; i < n; i++) // horizontal
    {
        for (int j = 0; j < m; j++) // vertical
        {
            int currentPlace = getNodeIdentifier(m, i, j);
            visitedNodes[currentPlace] = false;
        }
    }

    visitedNodes[0] = true;
    priorityQueue.push(0);

    while(!priorityQueue.empty()) {
        int current = priorityQueue.front();
        priorityQueue.pop();
        char currentNodeValue = graphValues[current];

        std::vector<int>::iterator it;
        for (it = graph[current].begin(); it != graph[current].end(); ++it)
        {   
            int neighbor = (*it);
            char neighborValue = graphValues[neighbor];
            if (currentNodeValue == 'T' && neighborValue == 'A') {
                graphValues[neighbor] = 'T';
                visitedNodes[neighbor] = false;
            }
            if (neighborValue == 'T' && currentNodeValue == 'A') {
                graphValues[current] = 'T';
                visitedNodes[current] = false;
            }

            if  (!visitedNodes[neighbor]) {
                visitedNodes[neighbor] = true;
                priorityQueue.push(neighbor);
            }
        }
    }
}

void printMap(char* graphValues, int n, int m) {
    for (int i = 0; i < n; i++) // horizontal
    {
        for (int j = 0; j < m; j++) // vertical
        {   
            int currentPlace = getNodeIdentifier(m, i, j);
            cout << graphValues[currentPlace];
        }
        cout << "\n";
    }
    cout << "\n";
}
