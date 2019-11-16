#pragma once
#include <list>
#include <vector>

using namespace std;
class CostGraphListNode {
private:
	int destination_;
	int edge_cost_;
public:
	CostGraphListNode(int d, int e) {
		destination_ = d;
		edge_cost_ = e;
	}
	friend class CostGraph;
};
class CostGraph {
private:
	int num_vertex_;
	vector<list<CostGraphListNode>> adjlist_;
	bool is_undirected_graph_ = false;

	void AddEdge(int from, int to, int cost);
	void SearchDfsRecursion(int v, vector<bool>& visited);

	bool CheckUndirectedGraphCyclicRecursion(int v, vector<bool>& visited, int parent);
	bool CheckUndirectedGraphCyclic();
	bool CheckDirectedGraphCyclicRecursion(int now, vector<bool>& visited, vector<bool>& reclist);
	bool CheckDirectedGraphCyclic();

	int GetUndirectedGraphLongestPath();
	int GetDirectedGraphLongestPath();
public:
	CostGraph(int v);
	~CostGraph();
	void MakeUndirectedGraph(vector<vector<int>> input);
	void MakeDirectedGraph(vector<vector<int>> input);
	void SearchDfs(int v);
	void SearchBfs(int v);
	vector<int> TopologicalSort();
	bool CheckCyclic();
//	void PrintList();

	void GetLongestPathDfs(int start, int length, int& maxi, vector<bool> visited);
	int GetLongestPath();
};

