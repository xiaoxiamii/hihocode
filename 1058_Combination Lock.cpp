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
const int MAX= 128 ;
const int MAX_N= 5e3 + 200;
const int MAX_M = 1e5 + 10;
const int MAX_K = 1e4+10;

static int N, M, K, T;

int SP;
string str;
int f[ MAX_N];


//same: 表示当前区间的字符是否相同，若相同则same等于该字符，否则same=-1
//add: 表示当前区间的增量，对应CMD2操作所增加的K
//delta和 inc : 这两个变量是一组，其表示CMD4的操作。
//其含义为，该区间最左起第1个元素值增量为delta，此后每一个元素的增量比前一个多inc。
//即第2个元素的增量为delta+inc，第3个元素的增量为delta+inc+inc，...，第i个元素的增量为delta+inc*(i-1)。
struct segTreeNode {
	int left, right;
	int same, add;
	int delta, inc;
	int lch, rch;
} tree[MAX_N << 2];


void createTree(int rt, int left, int right) {
	tree[rt].left = left;
	tree[rt].right = right;
	tree[rt].delta = tree[rt].inc = 0;
	tree[rt].add = 0;

	//leafs node
	if(left == right) {
		tree[rt].same = str[left] - 'A';
		tree[rt].lch = tree[rt].rch =0;
		return ;
	}

	//no-leaf node;

	tree[rt].same = -1;
	tree[rt].lch = rt*2;
	tree[rt].rch = rt *2 +1;

	int mid = (tree[rt].left + tree[rt].right) >>1 ;
	createTree(tree[rt].lch, left, mid);
	createTree(tree[rt].rch, mid +1, right);
	return;
}


void update (int rt, int left, int right, int key, int type) {
	if(!rt) return;
	if(tree[rt].right < left || tree[rt].left > right) return;
	if(left <= tree[rt].left && tree[rt].right <= right) {
		//包含当前所有区间
		switch (type)
		{
		case 1:
			tree[rt].same = key;
			tree[rt].delta =0, tree[rt].inc =0;
			tree[rt].add =0;
			break;
		case 2:
			tree[rt].add +=key;
			break;
		case 3:
			break;

		case 4:
			tree[rt].delta += key + (tree[rt].left - left);
			tree[rt].inc ++;
			break;

		default:
			break;
		}
		if(type == 1) {

		}
	}
	else {
		// 当前节点区间不完全包含于[left,right]，则需要让子区间来处理
        // 传递当前区间的信息
		int mid = (tree[rt].left + tree[rt].right) /2;
		
		if(tree[rt].same == -1) {
			//lch
			tree[ tree[rt].lch ].delta += tree[rt].delta;
			tree[ tree[rt].lch ].inc += tree[rt].inc;
			tree[ tree[rt].lch ].add += tree[rt].add;
			//rch
			tree[ tree[rt].rch ].delta += tree[rt].delta + (mid - tree[rt].left +1) * tree[rt].inc;
			tree[ tree[rt].rch ].inc += tree[rt].inc;
			tree[ tree[rt].rch ].add += tree[rt].add;
		}
		else {
			//lch
			tree[ tree[rt].lch ].same = tree[ tree[rt].rch ].same = tree[rt].same;
			tree[ tree[rt].lch ].delta = tree[rt].delta;
			tree[ tree[rt].rch ].delta = tree[rt].delta + (mid - tree[rt].left +1) * tree[rt].inc;
			tree[ tree[rt].lch ].inc = tree[ tree[rt].rch ].inc = tree[rt].inc;
			tree[ tree[rt].lch ].add = tree[ tree[rt].rch ].add = tree[rt].add;
			
		}

        // 更新当前区间信息
		tree[rt].same = -1;
		tree[rt].delta = tree[rt].inc = 0;
		tree[rt].add = 0;

        // 迭代处理
		update(tree[rt].lch, left, right, key, type);
		update(tree[rt].rch, left, right, key, type);

	}
}


void getResult(int rt) {
	if (!rt) return;
	if( tree[rt].same != -1) {
		int delta = tree[rt].delta;
		for(int i = tree[rt].left ; i<= tree[rt].right; ++i) {
			f[i] = tree[rt].same + tree[rt].add + delta; 
			delta += tree[rt].inc;
		}
	}
	else {
		//
		int mid = (tree[rt].left + tree[rt].right) / 2;
		//lch
		tree[ tree[rt].lch ].delta += tree[rt].delta;
		tree[ tree[rt].lch ].inc += tree[rt].inc;
		tree[ tree[rt].lch ].add += tree[rt].add;
		//rch
		tree[ tree[rt].rch ].delta += tree[rt].delta + (mid - tree[rt].left +1) * tree[rt].inc;
		tree[ tree[rt].rch ].inc += tree[rt].inc;
		tree[ tree[rt].rch ].add += tree[rt].add;

		getResult(tree[rt].lch);
		getResult(tree[rt].lch);
	}
	return;
}

void typeAns() {
	for(int i =0; i<N;  ++i) {
		printf("%c", (char (f[(SP + i) %N] + 'A') ));
	}
	printf("\n");
	return;
}

int main() {
	int N,M;
	cin>> N >> M;
	cin >> str;
	while (M--)
	{
		string tmp;
		int type =0;
		int begin =0, end =0, key =0;
		char c = '\0';


		cin >> tmp >> type;
		switch (type)
		{
		case 1:
			cin >> begin >> end >> c;
			update (1, begin, end, c - 'A', type);
			break;
		case 2:
			cin >> begin >> end >> key;
			update (1, begin, end, key, type);
			break;
		case 3:
			cin >> begin;
			SP +=SP;
			break;
		case 4:
			cin >> begin >> end;
			update (1, begin, end, 0, type);
			break;
		default:
			break;
		}
	}	
	getResult(1);
	typeAns();


	system("pause");
	return 0;

}

