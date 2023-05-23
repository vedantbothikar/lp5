#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

#define MAXN 100000

vector<int> adj[MAXN]; // Adjacency list representation of graph

void dfs_parallel(int source) {

    bool visited[MAXN] = {false}; // Array to keep track of visited nodes
    stack<int> st; // Stack to store nodes to visit

    visited[source] = true;
    st.push(source);

    cout<<"Visited nodes: ";

    while (!st.empty()) {
        int u = st.top();
        st.pop();

        cout<<u<<" ";

        #pragma omp parallel for
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];

            #pragma omp critical
            {
                if (!visited[v]) {
                    visited[v] = true;
                    st.push(v);
                }
            }
        }
    }

    cout<<endl;
}

void dfs_serial(int source) {

    bool visited[MAXN] = {false}; // Array to keep track of visited nodes
    stack<int> st; // Stack to store nodes to visit

    visited[source] = true;
    st.push(source);

    cout<<"Visited nodes: ";

    while (!st.empty()) {
        int u = st.top();
        st.pop();

        cout<<u<<" ";

        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];

            if (!visited[v]) {
                visited[v] = true;
                st.push(v);
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
    dfs_serial(source);
    double mid_time = omp_get_wtime();

    cout << "Time taken for serial DFS: " << (mid_time - start_time) << " seconds" << endl;

    dfs_parallel(source);
    double end_time  = omp_get_wtime();

    cout << "Time taken for parallel DFS: " << (end_time - mid_time) << " seconds" << endl;


    return 0;
}
