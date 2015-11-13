#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>
#include<vector>
#include<string>
#include<sstream>
#include<algorithm>
#include<stack>
#include<queue>
#include<limits.h>
#include<numeric>
#include<cstring>
#include<map>

using namespace std;
const int MAX_N = 1e3 + 10;
const int MAX_M = 1e4 + 10;

static int N, M, S, T;
int graph[MAX_N][MAX_N];
int dist[MAX_N], vis[MAX_N];

int prime() {
	for(int i =1; i<=N;++i){
		dist[i] = graph[1][i];
	}
	
	int sum_dist = 0;
	vis[1] = 1;
	for(int k =2; k<=N;++k){
		int node = 0;
		int min_dist = INT_MAX;
		for(int i=1; i<=N; ++i){
			if(vis[i] == 0 && dist[i] < min_dist){
				node = i;
				min_dist = dist[i];
			}
		}
		vis[node] =1;
		//cout << node << " " <<min_dist << endl;
		sum_dist += min_dist;

		//¸üÐÂ¾àÀë
		for(int i=1; i<=N;++i){
			if(dist[i] > ( graph[node][i])) {
				dist[i] = graph[node][i];
			}
		}
	}
	return sum_dist;

}

int main (){
	cin >> N;
	for(int i = 1; i<=N; ++i){
		for(int j =1; j<=N; ++j){
			cin>> graph[i][j];
		}
	}
	cout << prime() << endl;
	
	system("pause");
	return 0;
	
}