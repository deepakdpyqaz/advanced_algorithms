#include <bits/stdc++.h>
using namespace std;

set<set<int>> independentSets;

set<set<int>> maximalIndependentSets;

map<pair<int, int>, int> edges;
vector<int> vertices;

void printAllIndependentSets()
{
    for (auto iter : independentSets)
    {
        cout << "{ ";
        for (auto iter2 : iter)
        {
            cout << iter2 << " ";
        }
        cout << "}";
    }
    cout << endl;
}

void printMaximalIndependentSets()
{
    int maxCount = 0;
    int localCount = 0;
    for (auto iter : independentSets)
    {

        localCount = 0;
        for (auto iter2 : iter)
        {
            localCount++;
        }
        if (localCount > maxCount)
            maxCount = localCount;
    }
    for (auto iter : independentSets)
    {

        localCount = 0;
        set<int> tempMaximalSet;

        for (auto iter2 : iter)
        {
            localCount++;
            tempMaximalSet.insert(iter2);
        }
        if (localCount == maxCount)
            maximalIndependentSets
                .insert(tempMaximalSet);
    }
    for (auto iter : maximalIndependentSets)
    {
        cout << "{ ";
        for (auto iter2 : iter)
        {
            cout << iter2 << " ";
        }
        cout << "}";
    }
    cout << endl;
}

bool isSafeForIndependentSet(
    int vertex,
    set<int> tempSolutionSet)
{
    for (auto iter : tempSolutionSet)
    {
        if (edges[make_pair(iter, vertex)])
        {
            return false;
        }
    }
    return true;
}

void findAllIndependentSets(
    int currV,
    int setSize,
    set<int> tempSolutionSet)
{
    for (int i = currV; i <= setSize; i++)
    {
        if (isSafeForIndependentSet(
                vertices[i - 1],
                tempSolutionSet))
        {
            tempSolutionSet
                .insert(vertices[i - 1]);
            findAllIndependentSets(
                i + 1,
                setSize,
                tempSolutionSet);
            tempSolutionSet
                .erase(vertices[i - 1]);
        }
    }
    independentSets
        .insert(tempSolutionSet);
}

int main()
{
    int V, E;
    cout<<"Enter no. of vertices: ";
    cin >> V;
    cout<<"Enter no. of edges: ";
    cin >> E;


    for (int i = 1; i <= V; i++)
        vertices.push_back(i);

    pair<int, int> edge;
    int x, y;
    for (int i = 0; i < E; i++)
    {
        cout<<"Enter edge (U,V): ";
        cin >> x >> y;
        edge.first = x;
        edge.second = y;
        edges[edge] = 1;
        int t = edge.first;
        edge.first = edge.second;
        edge.second = t;
        edges[edge] = 1;
    }

    set<int> tempSolutionSet;

    findAllIndependentSets(1,V,tempSolutionSet);

    printAllIndependentSets();

    printMaximalIndependentSets();

    return 0;
}
