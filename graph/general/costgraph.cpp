#include "costgraph.h"
#include <iostream>
#include <queue>
#include <limits.h>
#include <algorithm>

CostGraph::CostGraph(int v) {
	num_vertex_ = v;
	adjlist_ = vector<list<CostGraphListNode>>(v);
}

CostGraph::~CostGraph() {
}

void CostGraph::AddEdge(int from, int to, int cost) {
	CostGraphListNode edge(to, cost);
	adjlist_[from].push_back(edge);
}

void CostGraph::MakeUndirectedGraph(vector<vector<int>> input) {
	for (size_t i = 0; i < input.size(); i++) {
		int from = input[i][0];
		int to = input[i][1];
		int cost = input[i][2];
		AddEdge(from, to,cost);
		AddEdge(to, from,cost);
	}
	cout << "Making undirected graph complete. Vertex count = " << num_vertex_ << '\n';
	is_undirected_graph_ = true;
}

void CostGraph::MakeDirectedGraph(vector<vector<int>> input) {
	for (size_t i = 0; i < input.size(); i++) {
		int from = input[i][0];
		int to = input[i][1];
		int cost = input[i][2];
		AddEdge(from, to, cost);
	}
	cout << "Making directed graph complete. Vertex count = " << num_vertex_ << '\n';
	is_undirected_graph_ = false;
}

void CostGraph::SearchDfsRecursion(int now, vector<bool>& visited) {
	visited[now] = true;
	cout << now << " ";

	for (auto next = adjlist_[now].begin(); next != adjlist_[now].end(); next++) {
		int next_node = next->destination_;
		if (!visited[next_node]) SearchDfsRecursion(next_node, visited);
	}
}

void CostGraph::SearchDfs(int v) {
	vector<bool> visited(num_vertex_, false);
	cout << "Start Depth First Search\n";
	SearchDfsRecursion(v, visited);
	cout << "\nDepth First Search End\n";
}

void CostGraph::SearchBfs(int v) {
	vector<bool> visited(num_vertex_, false);
	cout << "Start Breadth First Search\n";
	queue<int> q;
	q.push(v);
	visited[v] = true;
	while (!q.empty()) {
		int now = q.front(); q.pop();
		cout << now << " ";
		for (auto next = adjlist_[now].begin(); next != adjlist_[now].end(); next++) {
			int next_node = next->destination_;
			if (!visited[next_node]) {
				visited[next_node] = true;
				q.push(next_node);
			}
		}
	}
	cout << "\nBreadth First Search End\n";
}

bool CostGraph::CheckUndirectedGraphCyclicRecursion(int now, vector<bool>& visited, int parent) {
	visited[now] = true;
	for (auto next = adjlist_[now].begin(); next != adjlist_[now].end(); next++) {
		int next_node = next->destination_;
		if (!visited[next_node]) {
			if (CheckUndirectedGraphCyclicRecursion(next_node, visited, now)) return true;
		}
		else if (next_node != parent) return true;
	}
	return false;
}
bool CostGraph::CheckUndirectedGraphCyclic() {
	vector<bool> visited(num_vertex_, false);
	for (int i = 0; i < num_vertex_; i++) {
		if (!visited[i] && CheckUndirectedGraphCyclicRecursion(i, visited, -1)) return true;
	}
	return false;
}

bool CostGraph::CheckDirectedGraphCyclicRecursion(int now, vector<bool>& visited, vector<bool>& reclist) {
	if (!visited[now]) {
		visited[now] = true;
		reclist[now] = true;
		for (auto next = adjlist_[now].begin(); next != adjlist_[now].end(); next++) {
			int next_node = next->destination_;
			if (!visited[next_node] && CheckDirectedGraphCyclicRecursion(next_node, visited, reclist)) return true;
			else if (reclist[next_node]) return true;
		}
	}
	reclist[now] = false;
	return false;
}
bool CostGraph::CheckDirectedGraphCyclic() {
	vector<bool> visited(num_vertex_, false);
	vector<bool> reclist(num_vertex_, false);
	for (int i = 0; i < num_vertex_; i++) {
		if (CheckDirectedGraphCyclicRecursion(i, visited, reclist)) return true;
	}
	return false;
}

bool CostGraph::CheckCyclic() {
	if (is_undirected_graph_) return CheckUndirectedGraphCyclic();
	else return CheckDirectedGraphCyclic();
}

void CostGraph::GetLongestPathDfs(int start, int length, int& maxi, vector<bool> visited) {
	visited[start] = true;
	int curr_len = 0;
	for (auto next = adjlist_[start].begin(); next != adjlist_[start].end(); next++) {
		CostGraphListNode now = *next;
		if (!visited[now.destination_]) {
			curr_len = length + now.edge_cost_;

			GetLongestPathDfs(now.destination_, curr_len, maxi, visited);
		}
		if (maxi < curr_len) maxi = curr_len;
		curr_len = 0;
	}
}

int CostGraph::GetUndirectedGraphLongestPath() {
	if (CheckCyclic()) return -1;
	vector<int> leaf;
	for (int i = 0; i < num_vertex_; i++) {
		if (adjlist_[i].size() == 1) leaf.push_back(i);
	}
	int maxi_length = INT_MIN;
	for (auto start = leaf.begin(); start != leaf.end(); start++) {
		vector<bool> visited(num_vertex_, false);

		GetLongestPathDfs(*start, 0, maxi_length, visited);
	}
	return maxi_length;
}

vector<int> CostGraph::TopologicalSort() {
	vector<int> indegree(num_vertex_, 0);
	vector<int> result;
	for (int i = 0; i < num_vertex_; i++) {
		for (auto next = adjlist_[i].begin(); next != adjlist_[i].end(); next++) {
			int next_node = next->destination_;
			indegree[next_node]++;
		}
	}
	priority_queue<int, vector<int>, greater<int>> pq;
	for (int i = 0; i < num_vertex_; i++) {
		if (indegree[i] == 0) pq.push(i);
	}
	while (!pq.empty()) {
		int now = pq.top(); pq.pop();
		result.push_back(now);
		for (auto next : adjlist_[now]) {
			indegree[next.destination_]--;
			if (indegree[next.destination_] == 0) pq.push(next.destination_);
		}
	}
	return result;
}
int CostGraph::GetDirectedGraphLongestPath() {
	if (CheckCyclic()) return -1;
	vector<int> topological_order = TopologicalSort();
	vector<int> distance(num_vertex_, INT_MIN);
	distance[topological_order[0]] = 0;
	for (int now : topological_order) {
		if (distance[now] != INT_MIN) {
			for (auto next = adjlist_[now].begin(); next != adjlist_[now].end(); next++) {
				distance[next->destination_] = max(distance[next->destination_], distance[now] + next->edge_cost_);
			}
		}
	}
	return *max_element(distance.begin(), distance.end());
}

int CostGraph::GetLongestPath() {
	if (is_undirected_graph_) return GetUndirectedGraphLongestPath();
	else return GetDirectedGraphLongestPath();
}
