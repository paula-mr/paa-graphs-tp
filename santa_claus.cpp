#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

void addEdge(vector<vector<int> >* graph, int u, int v, int weight);
int getMST(vector<vector<int> >* graph, int parents[], int ranks[], int size);
void sortEdges(vector<vector<int> >* graph, int size);
int partition(vector<vector<int> >* graph, int first, int last);
void quickSort(vector<vector<int> >* graph, int first, int last);
int findDSU(int parents[], int i);
void uniteDSU(int parents[], int ranks[], int size, int x, int y);


int main()
{
    int m, n;
    cin >> m >> n;
    while (m > 0)
    {
        vector<vector<int> > graph;
        int* dsuParents = (int*) malloc(n*sizeof(int));
        int* dsuRanks = (int*) malloc(n*sizeof(int));

        for (int i = 0; i < n; i++)
        {
            int city1, city2, distance;
            cin >> city1 >> city2 >> distance;
            addEdge(&graph, city1, city2, distance);
        }

        for (int i = 0; i < n; i++) {
            dsuParents[i] = -1;
            dsuRanks[i] = 1;
        }

        int totalDistance = getMST(&graph, dsuParents, dsuRanks, n);
        cout << totalDistance << "\n";
        
        free(dsuParents);
        free(dsuRanks);
        cin >> m >> n;
    }

    return 0;
}

int getMST(vector<vector<int> >* graph, int parents[], int ranks[], int size)
{
    sortEdges(graph, size);
    int mstDistance = 0;

    for (int i=0; i<size; i++) {
        int city1 = graph->at(i)[0];
        int city2 = graph->at(i)[1];
        int distance = graph->at(i)[2];

        if (findDSU(parents, city1) != findDSU(parents, city2)) {
            uniteDSU(parents, ranks, size, city1, city2);
            mstDistance += distance;
        }
    }

    return mstDistance;
}

void addEdge(vector<vector<int> >* graph, int u, int v, int weight)
{   
    vector<int> city;
    city.push_back(u);
    city.push_back(v);
    city.push_back(weight);
    graph->push_back(city);
}

void sortEdges(vector<vector<int> >* graph, int size)
{   
    quickSort(graph, 0, size-1);
}


int partition(vector<vector<int> >* graph, int first, int last) {
    int pivotIndex = first + floor((last-first)/2);
    int pivotDistance = graph->at(pivotIndex)[2];
    int i = first, j = last;

    while (i < j) {
        while (i <= last && graph->at(i)[2] < pivotDistance) {
            i++;
        }
        while (j >= first && graph->at(j)[2] > pivotDistance) {
            j--;
        }
        if (i < j) {
            if (i == pivotIndex) pivotIndex = j;
            if (j == pivotIndex) pivotIndex = i;
            graph->at(i).swap(graph->at(j));
            i++;
            j--;
        } 
    }
    return pivotIndex;
}

void quickSort(vector<vector<int> >* graph, int first, int last) {
    if (first < last) {
        int partitionIndex = partition(graph, first, last);
        quickSort(graph, first, partitionIndex-1);
        quickSort(graph, partitionIndex+1, last);
    }
}

int findDSU(int parents[], int i) {
    if (parents[i] == -1) return i;
    return findDSU(parents, parents[i]);
}

void uniteDSU(int parents[], int ranks[], int size, int x, int y) {
    int setX = findDSU(parents, x);
    int setY = findDSU(parents, y);

    if (setX != setY) {
        if (ranks[setX] < ranks[setY]) {
            parents[setX] = setY;
            ranks[setY] += ranks[setX];
        } else {
            parents[setY] = setX;
            ranks[setX] += ranks[setY];
        }
    }
}
