#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#define GRAPH_MAX 5
using namespace std;
typedef pair<int,int> cost_dst;

vector<int> dist(GRAPH_MAX,INT_MAX);

void solution(vector<vector<int>> costs, int src) {
	dist[src] = 0;
	for(int t = 1; t<=GRAPH_MAX-1; t++) {
		for(int i=0; i<costs.size(); i++) {
			int from = costs[i][0];
			int to = costs[i][1];
			int cost = costs[i][2];
			
			if(dist[from] != INT_MAX && dist[to] > dist[from] + cost) dist[to] = dist[from] + cost;
		}
	}
}

int main() {
	int src = 0;
	vector<vector<int>> costs = {{0,2,1},{0,3,5},{1,2,-2},{2,1,4},{2,3,4},{3,0,-1},{3,1,3},{4,0,1},{4,2,-1}};
	solution(costs,src);

	for(int i=0; i<dist.size(); i++) {
		if(i == src) continue;
		if(dist[i] == INT_MAX) cout<<src<<" to " <<i<<" = "<<"INF"<<'\n';
		else cout<<src<<" to " <<i<<" = "<<dist[i]<<'\n';
	}
	return 0;
}