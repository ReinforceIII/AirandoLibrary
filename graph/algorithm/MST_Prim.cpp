#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
typedef pair<int,int> coco;
vector<coco> adjlist[100];
bool visited[100];
int solution(int n, vector<vector<int>> costs) {
    int answer = 0;
    for(int i=0; i<costs.size(); i++) {
        int from = costs[i][0];
        int to = costs[i][1];
        int cost = costs[i][2];
        adjlist[from].emplace_back(to,cost);
        adjlist[to].emplace_back(from,cost);
    }
    
    //Find MST :: Prim algorithm
    priority_queue<coco,vector<coco>,greater<coco>> pq;
    int start = 0;
    visited[start] = true;
    for(int i=0; i<adjlist[start].size(); i++) {
        int next_node = adjlist[start][i].first;
        int next_cost = adjlist[start][i].second;
        pq.emplace(next_cost,next_node);
    }
    while(!pq.empty()) {
        int now_cost = pq.top().first;
        int now_node = pq.top().second;
        pq.pop();
        if(visited[now_node]) continue;
        visited[now_node] = true;
        answer += now_cost;
        
        for(int i=0; i<adjlist[now_node].size(); i++) {
            int next_node = adjlist[now_node][i].first;
            int next_cost = adjlist[now_node][i].second;
            pq.emplace(next_cost,next_node);
        }
    }
    return answer;
}