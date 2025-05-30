#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;


// 1. Convert matrix to list (ma trận kề thành danh sách kề)

vector<vector<int>> convertMatrixToList(const string& filename) {
	ifstream fin(filename);
	int n;
	fin >> n;

	vector<vector<int>> adjList(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0, val; j < n; j++) {
			fin >> val;
			if (val) {
				adjList[i].push_back(j);
			}
		}
	}
	return adjList;
}


// 2. Convert list to matrix

vector<vector<int>> convertListToMatrix(const string& filename) {
	ifstream fin(filename);
	int n;
	fin >> n;
	
	vector<vector<int>> adjMatrix(n, vector<int>(n, 0));

	for (int i = 0; i < n; i++) {
		int k, x;
		fin >> k;
		
		for (int j = 0; j < k; j++) {
			fin >> x;
			adjMatrix[i][x] = 1;
		}
	}
	return adjMatrix;
}

// 3. graph information


// directed Graph

bool isDirected(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (adjMatrix[i][j] != adjMatrix[j][i]) {
				return true;
			}
		}
	}
	return false;
}

// The number of vertices

int countVertices(const vector<vector<int>>& adjMatrix) {
	return adjMatrix.size();
}

// The number of Edges

int countEdges(const vector<vector<int>>& adjMatrix) {
	int edges = 0, n = adjMatrix.size();
	bool directed = isDirected(adjMatrix);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (adjMatrix[i][j]) {
				edges++;
			}
		}
	}
	if (directed) {
		return edges;
	}
	else {
		return edges / 2;
	}
}

// List of isolated vertices

vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix) {
	vector<int> isolated;
	int n = adjMatrix.size();
	
	for (int i = 0; i < n; i++) {
		bool iso = true;
		for (int j = 0; j < n; j++) {
			if (adjMatrix[i][j] || adjMatrix[j][i]) {
				iso = false;
				break;
			}
		}
		if (iso) {
			isolated.push_back(i);
		}
	}
	return isolated;
}

//  Undirected Graph

bool isCompleteGraph(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j && adjMatrix[i][j] == 0) {
				return false;
			}
		}
	}
	return true;
}


bool isBipartite(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<int> color(n, -1);
	queue<int> q;

	for (int start = 0; start < n; start++) {
		if (color[start] != -1) continue;
		color[start] = 0;
		q.push(start);

		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int v = 0; v < n; v++) {
				if (adjMatrix[u][v]) {
					if (color[v] == -1) {
						color[v] = 1 - color[u];
						q.push(v);
					}
					else if (color[v] == color[u]) {
						return false;
					}
				}
			}
		}
	}
	return true;
}


bool isCompleteBipartite(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<int> color(n, -1);
	queue<int> q;
	
	for (int start = 0; start < n; start++) {
		if (color[start] != -1) continue;
		color[start] = 0;
		q.push(start);

		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int v = 0; v < n; v++) {
				if (adjMatrix[u][v]) {
					if (color[v] == -1) {
						color[v] = 1 - color[u];
						q.push(v);
					}
					else if (color[v] == color[u]) {
						return false;
					}
				}
			}
		}
	}

	int c0 = count(color.begin(), color.end(), 0);
	int c1 = n - c0;

	return countEdges(adjMatrix) == c0 * c1;
}


// Generate a base undirected graph from a given directed graph

vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<vector<int>> undirected(n, vector<int>{n, 0});

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (adjMatrix[i][j] || adjMatrix[j][i]) {
				undirected[i][j] = undirected[j][j] = 1;
			}
		}
	}
	return undirected;
}

//  Generate a complement graph from a given undirected graph and output its adjacency matrix 

vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<vector<int>> comp(n, vector<int>{n, 0});

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j && adjMatrix[i][j] == 0) {
				comp[i][j] = 1;
			}
		}
	}
	return comp;
}

// Determine the Euler cycle from a given graph

vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<vector<int>> g = adjMatrix;
	vector<int> result;
	stack<int> st;
	st.push(0);

	while (!st.empty()) {
		int u = st.top();
		int v;
		for (v = 0; v < n; v++) {
			if (g[u][v]) {
				break;
			}
		}

		if (v == n) {
			result.push_back(u);
			st.pop();
		}
		else {
			st.push(v);
			g[u][v]--;
			g[v][u]--;
		}
	}
	return result;
}


// Find the spanning tree of a given graph 

void dfsUtil(int u, const vector<vector<int>>& adjMatrix, vector<bool> visited, vector<vector<int>>& tree) {
	int n = adjMatrix.size();
	visited[u] = true;

	for (int v = 0; v < n; v++) {
		if (adjMatrix[u][v] && !visited[v]) {
			tree[u][v] = tree[v][u] = 1;
			dfsUtil(v, adjMatrix, visited, tree);
		}
	}
}


vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
	int n = adjMatrix.size();
	vector<bool> visited(n, false);
	vector<vector<int>> tree(n, vector<int>(n, 0));

	dfsUtil(start, adjMatrix, visited, tree);
	return tree;
}


vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
	int n = adjMatrix.size();
	vector<bool> visited(n, false);
	vector<vector<int>> tree(n, vector<int>(n, 0));
	queue<int> q;

	q.push(start);
	visited[start] = true;

	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int v = 0; v < n; v++) {
			if (adjMatrix[u][v] && !visited[v]) {
				visited[v] = true;
				tree[u][v] = tree[v][u] = 1;
				q.push(v);
			}
		}
	}
	return tree;
}


// Verify the connection between two vertices of a given graph

bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<bool> visited(n, false);
	queue<int> q;

	q.push(u);
	visited[u] = true;

	while (!q.empty()) {
		int cur = q.front(); q.pop();
		if (cur == v) return true;
		for (int i = 0; i < n; i++) {
			if (adjMatrix[cur][i] && !visited[i]) {
				visited[i] = true;
				q.push(i);
			}
		}
	}
	return false;
}


// Find the shortest path between two vertices of a given graph

vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<int> dist(n, INT_MAX), prev(n, -1);
	dist[start] = 0;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
	pq.push({ 0, start });

	while (!pq.empty()) {
		int u = pq.top().second, d = pq.top().first;
		pq.pop();
		if (d > dist[u]) continue;

		for (int v = 0; v < n; ++v) {
			if (adjMatrix[u][v] && dist[u] + adjMatrix[u][v] < dist[v]) {
				dist[v] = dist[u] + adjMatrix[u][v];
				prev[v] = u;
				pq.push({ dist[v], v });
			}
		}
	}

	vector<int> path;
	for (int v = end; v != -1; v = prev[v]) path.push_back(v);
	reverse(path.begin(), path.end());
	return path;
}


vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<int> dist(n, INT_MAX), prev(n, -1);
	dist[start] = 0;

	for (int k = 0; k < n - 1; ++k)
		for (int u = 0; u < n; ++u)
			for (int v = 0; v < n; ++v)
				if (adjMatrix[u][v] && dist[u] != INT_MAX && dist[u] + adjMatrix[u][v] < dist[v]) {
					dist[v] = dist[u] + adjMatrix[u][v];
					prev[v] = u;
				}

	vector<int> path;
	for (int v = end; v != -1; v = prev[v]) path.push_back(v);
	reverse(path.begin(), path.end());
	return path;
}