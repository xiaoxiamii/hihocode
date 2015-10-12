#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<cmath>
using namespace std;
const int MAX_N=100010;//最大人数
map<string,int> name_index;//名字转换为数字
vector<string> index_name(MAX_N);//数字转换为名字
int n,m,k;//k全部记录将树转换成数组tree[]是的下标，转换结束时k即为tree[]的长度
vector<vector<int> > f_s(MAX_N);//f_s[i]表示第i个父亲的所有孩子
int tree[2*MAX_N];//DFS将树转换为的数组
int depth[MAX_N];//每个点在树中的深度
int rmq[MAX_N][30];//区间深度最低值
int last_show[MAX_N];//某个元素最后出现在tree中的位置（下标）
//保存某个人的信息，并返回其下标
int store_name(string name)
{
     map<string,int>::iterator it=name_index.find(name);
     if(it==name_index.end())//还不存在
     {
          int curr_index=name_index.size();//用当前已有人数作为其下标，正好是递增的。
          name_index.insert(make_pair(name,curr_index));
          index_name[curr_index]=name;//记录
          return curr_index;//返回下标
     }
     else
          return it->second;//已经存在，直接返回
}
//深度遍历树
void DFS(int root,int deep)
{
     tree[k++]=root;//进入即记录
     depth[root]=deep;//记录深度
     int sons=f_s[root].size();
     for(int i=0;i<sons;i++)
     {
          DFS(f_s[root][i],deep+1);
          tree[k++]=root;//每返回一次都要记录一次根节点
     }
     last_show[root]=k-1;//root节点最后出现的位置
}
//求a,b最小值
inline int get_min(int a,int b)
{
     return a<b?a:b;
}
void init_rmq()
{
     for(int j=0;j<k;j++)
          //rmq[j][0]=depth[tree[j]];
          rmq[j][0]=tree[j];//保存的是这个节点，而不是它的深度，方便最后输出
     int q=floor(log((double)k)/log(2.0));
     for(int i=1;i<=q;i++)
     {
          for(int j=k-1;j>=0;j--)
          {
               rmq[j][i]=rmq[j][i-1];
               if(j+(1<<(i-1))<k)
               {
                    if(depth[rmq[j+(1<<(i-1))][i-1]]<depth[rmq[j][i]])//+优先级高于<<，所以改j+1<<(i-1)为j+(1<<(i-1))
                         rmq[j][i]=rmq[j+(1<<(i-1))][i-1];
               }
                    //rmq[j][i]=get_min(rmq[j][i],rmq[j+1<<(i-1)][i-1]);
          }
     }
}
int main()
{
     //freopen("input.txt","r",stdin);
     cin>>n;
     string name1,name2;
     int index1,index2;
     while(n--)
     {
          cin>>name1>>name2;
          index1=store_name(name1);
          index2=store_name(name2);
          f_s[index1].push_back(index2);
     }
     k=0;//开始时树的下标为0，DFS完之后正好是tree[]数组的长度，可以作为rmq-st的n
     DFS(0,0);
     init_rmq();
     cin>>m;
     int l,r,t;
     while(m--)
     {
          cin>>name1>>name2;
          if(name1==name2)
          {
               cout<<name1<<endl;
               continue;
          }
          index1=store_name(name1);
          index2=store_name(name2);
          l=last_show[index1];
          r=last_show[index2];
          if(l>r)//保证l<=r
          {
               int tmp=r;
               r=l;
               l=tmp;
          }
          t=floor(log(double(r-l+1))/log(2.0));//找到能使[l,r]分为两半的指数
          cout<<index_name[get_min(rmq[l][t],rmq[r-(1<<t)+1][t])]<<endl;//r-(1<<t)+1，记得+1
     }
     return 0;
}