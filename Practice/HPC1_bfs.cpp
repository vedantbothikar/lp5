#include <iostream>
#include <queue>
#include <vector>
#include <omp.h>

using namespace std;

#define MAXN 100000

vector<int> adj[MAXN]; // Adjacency list representation of graph

void bfs_parallel(int source) {

    bool visited[MAXN] = {false}; // Array to keep track of visited nodes
    queue<int> q; // Queue to store nodes to visit

    visited[source] = true;
    q.push(source);

    cout<<"Visited nodes: ";

    while (!q.empty()) {
        int u = q.front();

        cout<<u<<" ";

        q.pop();

        #pragma omp parallel for
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];

            #pragma omp critical
            {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }

    cout<<endl;
}

void bfs_serial(int source) {

    bool visited[MAXN] = {false}; // Array to keep track of visited nodes
    queue<int> q; // Queue to store nodes to visit

    visited[source] = true;
    q.push(source);

    cout<<"Visited nodes: ";

    while (!q.empty()) {
        int u = q.front();

        cout<<u<<" ";

        q.pop();

        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];

            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    cout<<endl;
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int source;
    cin >> source;

    double start_time = omp_get_wtime();
    bfs_serial(source);
    double mid_time = omp_get_wtime();

    cout << "Time taken for serial BFS: " << (mid_time - start_time) << " seconds" << endl;

    bfs_parallel(source);
    double end_time  = omp_get_wtime();

    cout << "Time taken for parallel BFS: " << (end_time - mid_time) << " seconds" << endl;


    return 0;
}
