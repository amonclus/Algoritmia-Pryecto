using namespace std;
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

struct Graph
{
    int numNodes;
    vector< vector<int> > adjList;

 Graph()
    {
        numNodes = 0;
        adjList.resize(0);
    }

    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void printGraph() const
    {
        for(int i = 0; i < numNodes; i++)
        {
            for(int j : adjList[i])
            {
                cout << j << " ";
            }
            cout << endl;
        }
    }

    void readFile()
    {
        string line;
        char c;
        int u, v, n, m;

        while (getline(cin, line))
        {
            istringstream iss(line);
            if (!(iss >> c)) continue; // Skip empty lines

            if (c == 'c')
            {
                continue;
            }
            if (c == 'p')
            {
                string type;
                iss >> type >> n >> m;
                numNodes = n;
                adjList.resize(n);
            }
            else if (c == 'e')
            {
                iss >> u >> v;
                addEdge(u - 1, v - 1);
            }
        }
    }

    void dfs(int node, vector<bool>& visited) {
        visited[node] = true;
        for (int neighbor : adjList[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, visited);
            }
        }
    }

    int connectedComponents() {
        vector<bool> visited(numNodes, false);
        int numComponents = 0;

        for (int i = 0; i < numNodes; ++i) {
            if (!visited[i]) {
                numComponents++;
                dfs(i, visited);  
            }
        }

        return numComponents;
    }
};

int main()
{
    Graph g;

    // Open the DIMACS file
    ifstream inputFile("test.dimacs");

    if (!inputFile.is_open()) {
        cerr << "Error: Could not open file test.dimacs" << endl;
        return 1;
    }

    cin.rdbuf(inputFile.rdbuf());  // Redirect cin to read from the file
    g.readFile();
    inputFile.close();
    cout << "The graph has " << g.connectedComponents() << " connected components" << endl;
}
