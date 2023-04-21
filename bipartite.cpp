#include <iostream>
#define M 5
#define N 6
using namespace std;

bool bipartiteGraph[M][N] = { 
    {0, 1, 1, 0, 0, 0},
    {1, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0},
    {0, 0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0}};

bool bipartiteMatch(int u, bool visited[], int assign[])
{
    for (int v = 0; v < N; v++)
    { 
        if (bipartiteGraph[u][v] && !visited[v])
        {                      
            visited[v] = true; 
            
            if (assign[v] < 0 || bipartiteMatch(assign[v], visited, assign))
            {
                assign[v] = u; 
                return true;
            }
        }
    }
    return false;
}

int maxMatch()
{
    int assign[N]; 
    for (int i = 0; i < N; i++)
        assign[i] = -1; 
    int jobCount = 0;

    for (int u = 0; u < M; u++)
    { 
        bool visited[N];
        for (int i = 0; i < N; i++)
            visited[i] = false;                 
        if (bipartiteMatch(u, visited, assign)) 
            jobCount++;
    }
    return jobCount;
}

int main()
{
    cout << "Maximum number of applicants matching for job: " << maxMatch();
}