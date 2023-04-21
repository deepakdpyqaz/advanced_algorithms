#include <bits/stdc++.h>
using namespace std;

class Graph
{
    int V;
    list<int> *adj;

public:
    Graph(int V);
    void addEdge(int v, int w);
    void printVertexCover();
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);
}

void Graph::printVertexCover()
{
    bool visited[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    list<int>::iterator i;

    for (int u = 0; u < V; u++)
    {
        if (visited[u] == false)
        {
            for (i = adj[u].begin(); i != adj[u].end(); ++i)
            {
                int v = *i;
                if (visited[v] == false)
                {
                    visited[v] = true;
                    visited[u] = true;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < V; i++)
        if (visited[i])
            cout << i << " ";
}

int main()
{
    int n;
    cout << "Enter no. of vertices : ";
    cin >> n;
    Graph g(n);

    int e;
    cout << "Enter no. of edges : ";
    cin >> e;

    for (int i = 0; i < e; i++)
    {
        int u, v;
        cout << "Enter start and end vertex of a edge : ";
        cin >> u >> v;
        g.addEdge(u, v);
    }

    cout << "Vertex Cover set in given graph : ";
    g.printVertexCover();

    return 0;
}