#include <iostream>
#include <queue>
#include <vector>
#include <omp.h>
using namespace std;

#define MAX 100000

vector<int> adj[MAX];

void bfs_parallel(int source)
{

    bool visited[MAX] = {false};
    visited[source] = true;

    queue<int> q;
    q.push(source);

    while (!q.empty())
    {
        int curr = q.front();
        q.pop();

        cout << curr << " ";

#pragma omp parallel for
        for (int i = 0; i < adj[curr].size(); i++)
        {
            int next = adj[curr][i];

#pragma omp critical
            if (!visited[next])
            {
                visited[next] = true;
                q.push(next);
            }
        }
    }

    cout << endl;
}

void bfs_serial(int source)
{

    bool visited[MAX] = {false};
    visited[source] = true;

    queue<int> q;
    q.push(source);

    while (!q.empty())
    {

        int curr = q.front();
        q.pop();

        cout << curr << " ";

        for (int i = 0; i < adj[curr].size(); i++)
        {
            int next = adj[curr][i];

            if (!visited[next])
            {
                visited[next] = true;
                q.push(next);
            }
        }
    }

    cout << endl;
}

int main()
{
    int n, m; // number of nodes and edges
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int source;
    cin >> source;

    double starttime = omp_get_wtime();
    bfs_serial(source);
    double endtime = omp_get_wtime();

    cout << "Time taken: " << endtime - starttime << endl;

    bfs_parallel(source);
    double finalendtime = omp_get_wtime();

    cout << "Time taken: " << finalendtime - endtime << endl;

    return 0;
}