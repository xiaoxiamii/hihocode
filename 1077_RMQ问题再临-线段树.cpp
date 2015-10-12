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
		seg_tree[root].val = min(seg_tree[root*2 +1].val, seg_tree[root*2 +2].val);
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
		return INT_MAX;
	}

	//whether the node section was included in query section
	if(qstart <= nstart && qend >= nend) {
		return seg_tree[root].val;
	}

	//query left and query right, return the min num of query result;
	int mid = nstart + (nend - nstart) /2;
	int ret1 = seg_tree_query(root*2+1, nstart, mid, qstart, qend);
	int ret2 = seg_tree_query(root*2+2, mid+1, nend, qstart, qend);

	/*
	if(ret1 == -1) 
		return ret2;
	if(ret2 == -1)
		return ret1;
		*/
	//return min;
	return min(ret1, ret2);
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

	seg_tree[root].val = min(seg_tree[root*2+1].val, seg_tree[root*2 +2].val);
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
		int act, begin, end;
		scanf("%d %d %d", &act, &begin, &end);
		if(act == 1) 
		{
			seg_tree_update_one(0, 0, N, begin -1, end);
		}
		else
		{
			int ret = seg_tree_query(0, 0, N, begin -1, end -1);
			printf("%d\n", ret);
		}
	}
	
	//system("pause");
	return 0;
	
}