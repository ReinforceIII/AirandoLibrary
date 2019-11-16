#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <limits.h>

using namespace std;
typedef pair<int,int> coco;
vector<coco> adjlist[20001];
vector<int> dist(20001,INT_MAX);
int main() {
	int V,E;
	cin>>V>>E;
	int src;
	cin>>src;
	for(int i=0; i<E; i++) {
		int from,to,cost;
		cin>>from>>to>>cost;
		adjlist[from].emplace_back(to,cost);
	}
	priority_queue<coco,vector<coco>,greater<coco>> pq;
	int start = src;
	dist[start] = 0;
	pq.emplace(0,start);
	while(!pq.empty()) {
		int now_cost = pq.top().first;
		int now_node = pq.top().second;
		pq.pop();
		if(dist[now_node] < now_cost) continue;

		for(int i=0; i<adjlist[now_node].size(); i++) {
			int next_node = adjlist[now_node][i].first;
			int next_cost = now_cost + adjlist[now_node][i].second;
			if(dist[next_node] > next_cost) {
				dist[next_node] = next_cost;
				pq.emplace(next_cost,next_node);
			}
		}
	}
	for(int i=1; i<=V; i++) {
		dist[i] == INT_MAX ? cout<<"INF\n" : cout<<dist[i]<<'\n';
	}
}