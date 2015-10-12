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
const int MAX_N = 1000010;
static int N, M, Q;
int weight[MAX_N] ;
struct seg_tree_node
{
	int val; // value
	int addMark; // lazy mark;
} seg_tree[MAX_N*4];

/*
function:
*/
int seg_tree_opterator(int val1, int val2) {
	return val1 + val2;
	//return min(val1, val2);
}
/*
function: build segment tree, begin from zero;
root : index of root in current segment tree 
arr: arrary to build segment tree;
istart: the begin of arr;
iend: the end of arr;
*/
void seg_tree_build(int root, int arr[], int istart, int iend) {

	seg_tree[root].addMark = 0;
	if( istart == iend ) { // leaf node
		seg_tree[root].val = arr[istart];
	}
	else {
		int mid = istart + (iend - istart) / 2;
		//build left and right
		seg_tree_build(root*2 +1, arr, istart, mid);
		seg_tree_build(root*2 +2, arr, mid+1, iend);
		//update the val;
		seg_tree[root].val = seg_tree_opterator(seg_tree[root*2+1].val, seg_tree[root*2+2].val);
	}
}

/*
function: spread mark to child node
root: index of current segment tree
*/
void seg_tree_push_down(int root, int nstart, int nend) {
	if(seg_tree[root].addMark !=0 ) {
		//设置左右孩子节点的标志域，因为孩子节点可能被多次延迟标记又没有向下传递
		//标志域可以根据题目的需求修改相关的值。
		seg_tree[root*2 +1].addMark = seg_tree[root].addMark;
		seg_tree[root*2 +2].addMark =seg_tree[root].addMark;

		int mid = nstart + (nend - nstart) /2;
		seg_tree[root*2 +1].val = seg_tree[root].addMark * (mid - nstart +1);
		seg_tree[root*2 +2].val = seg_tree[root].addMark * (nend - mid);

		seg_tree[root].addMark = 0;
	}
}
/*
function: query section in segment tree;
root: index of root in current segment tree;
[nstart, nend]: section of current node;
[qstart, qend]: section of query;
*/

int seg_tree_query(int root, int nstart, int nend, int qstart, int qend) {
	//whether has the intersection
	if(qstart > nend || qend < nstart) {
		return -1;
	}

	//whether the node section was included in query section
	if(qstart <= nstart && qend >= nend) {
		return seg_tree[root].val;
	}
	seg_tree_push_down(root, nstart, nend);

	//query left and query right, return the min num of query result;
	int mid = nstart + (nend - nstart) /2;
	int ret1 = seg_tree_query(root*2+1, nstart, mid, qstart, qend);
	int ret2 = seg_tree_query(root*2+2, mid+1, nend, qstart, qend);

	if(ret1 == -1) 
		return ret2;
	if(ret2 == -1)
		return ret1;
	//return min;
	//return min(ret1, ret2);
	return seg_tree_opterator(ret1, ret2);
}

/*
function:update the leaf node in segment tree;
root:  the index of current segment tree;
[nstart, nend]: the section of current node;
index: the index of update node in arr;
addval: (curVal + addVal)
*/

void seg_tree_update_one(int root, int nstart, int nend, int index, int addval){

	if(index == nstart && nstart == nend){
		//seg_tree[root].val += addval;
		seg_tree[root].val = addval;
		return;
	}

	int mid = nstart + (nend - nstart)/2;
	if(index <=mid)
		seg_tree_update_one(root*2+1, nstart, mid, index ,addval);
	else
		seg_tree_update_one(root*2+2, mid+1, nend, index, addval);

	//seg_tree[root].val = min(seg_tree[root*2+1].val, seg_tree[root*2 +2].val);
	seg_tree[root].val = seg_tree_opterator(seg_tree[root*2+1].val, seg_tree[root*2+2].val);
}
/*
function: update the section of segment tree;
root:index;
[nstart, nend]: the section of current root;
[ustart, uend]: section waiting to update
addVal: update value;
*/
void seg_tree_update_section(int root, int nstart, int nend, int ustart, int uend, int addVal) {

	if(ustart > nend || uend < nstart) {
		return ;
	}

	if(ustart <= nstart && uend >= nend) {
		seg_tree[root].addMark = addVal;
		seg_tree[root].val = addVal *(nend - nstart +1);
		return;
	}

	seg_tree_push_down(root, nstart, nend);

	int mid = nstart + (nend - nstart) / 2;
	seg_tree_update_section(root*2+1, nstart, mid, ustart, uend, addVal);
	seg_tree_update_section(root*2+2, mid+1, nend, ustart, uend, addVal);

	//
	seg_tree[root].val = seg_tree_opterator(seg_tree[root*2+1].val, seg_tree[root*2+2].val);
	//seg_tree[root].val = (seg_tree[root*2 +1].val + seg_tree[root*2+2].val);
}


int main (){
	scanf("%d", &N);
	for(int i =0; i<N; ++i) 
	{
		scanf("%d", &weight[i]);
	}
	seg_tree_build(0, weight, 0, N);

	scanf("%d", &Q);
	for(int i =0; i<Q; ++i) 
	{
		int act, left, right;
		scanf("%d", &act);
		if(act == 1) 
		{
			int newp;
			scanf("%d %d %d", &left, &right, &newp);
			seg_tree_update_section(0, 0, N, left -1, right -1, newp);
		}
		else
		{
			scanf("%d %d", &left, &right);
			int ret = seg_tree_query(0, 0, N, left -1, right -1);
			printf("%d\n", ret);
		}
	}
	
	//system("pause");
	return 0;
	
}