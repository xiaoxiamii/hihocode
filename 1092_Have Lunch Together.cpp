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
#include<set>

using namespace std;
#define eps 1e-8
#define LL long long
const LL mod=12357;
const int MIN= -1e3;
const int MAX= 14 ;
const int MAX_N= 1e2 + 10;
const int MAX_M = 1e2 + 10;
const int MAX_K = 1e4+10;

static int N, M, K, T;

int step[MAX_N][MAX_M] ;

const int dir[4][2] = {{0, -1}, {1,0 }, {0,1}, {-1, 0}};
vector< pair<int, int> > seq;


bool inMap(int x, int y, vector<string> map){
	return (1<=x && x <= N && 1<=y && y<=M) && (map[x][y] == '.' || map[x][y] == 'S');
}

void BFS(int x, int y, vector<string> map){
	step[x][y] = 0;
	seq.push_back( make_pair(x,y) );

	int i =0;
	while ( i < (int)seq.size())
	{
		for(int dr = 0; dr< 4; ++dr) {
			int tempX =seq[i].first + dir[dr][0];
			int tempY = seq[i].second + dir[dr][1];
			if(inMap(tempX, tempY,map) && step[tempX][tempY] == 20000){
				step[tempX][tempY] = step[seq[i].first][seq[i].second] +1;

				//not seat
				if(map[tempX][tempY] != 'S') seq.push_back( make_pair(tempX, tempY));
			}
		}
		i++;
	}
	return ;
}


int main() {
	for(int i =0;i<MAX_N; ++i) {
		for(int j =0; j<MAX_M;++j){
			step[i][j] = 20000;
		}
	}

	cin >> N >> M;
	vector<string> map(N,"");
	for(int i = 0;i<N;++i) {
		cin >> map[i];
	}

	//ÕÒÆðµã
	int startX=0; 
	int startY = 0;
	for(int i= 0; i<N;++i) {
		for(int j =0; j < N; ++j) {
			if(map[i][j] == 'H'){
				startX = i; startY =j;
				break;
			}
		}
	}
	BFS(startX, startY, map);

	int ret = 20000;
	for(int i = 0; i< N; ++i) {
		for(int j =0; j< M ;++j) {
			if(map[i][j] == 'S' && step[i][j] != 0 && step[i][j] != 20000){
				if(map[i-1][j] == 'S' && step[i-1][j] !=0 && step[i-1][j] != 20000 && (ret > step[i][j] + step[i-1][j])){
					//cout <<"1:" << step[i][j] <<"2:"<< step[i-1][j] << endl;
					ret = step[i][j] + step[i-1][j];
				}

				if(map[i][j-1] == 'S' && step[i][j-1] !=0 && step[i][j-1] != 20000 && (ret > step[i][j] + step[i][j-1])){
					//cout <<"3:" << step[i][j] <<"4:"<< step[i][j-1] << endl;
					ret = step[i][j] + step[i][j-1];
				}
			}
		}
	}
	if(ret == 20000) {
		printf("Hi and Ho will not have lunch.\n");
	}
	else {
		printf("%d\n",ret);
	}


	system("pause");
	return 0;

}
