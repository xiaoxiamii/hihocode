#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<cmath>
using namespace std;
const int MAX_N=100010;//�������
map<string,int> name_index;//����ת��Ϊ����
vector<string> index_name(MAX_N);//����ת��Ϊ����
int n,m,k;//kȫ����¼����ת��������tree[]�ǵ��±꣬ת������ʱk��Ϊtree[]�ĳ���
vector<vector<int> > f_s(MAX_N);//f_s[i]��ʾ��i�����׵����к���
int tree[2*MAX_N];//DFS����ת��Ϊ������
int depth[MAX_N];//ÿ���������е����
int rmq[MAX_N][30];//����������ֵ
int last_show[MAX_N];//ĳ��Ԫ����������tree�е�λ�ã��±꣩
//����ĳ���˵���Ϣ�����������±�
int store_name(string name)
{
     map<string,int>::iterator it=name_index.find(name);
     if(it==name_index.end())//��������
     {
          int curr_index=name_index.size();//�õ�ǰ����������Ϊ���±꣬�����ǵ����ġ�
          name_index.insert(make_pair(name,curr_index));
          index_name[curr_index]=name;//��¼
          return curr_index;//�����±�
     }
     else
          return it->second;//�Ѿ����ڣ�ֱ�ӷ���
}
//��ȱ�����
void DFS(int root,int deep)
{
     tree[k++]=root;//���뼴��¼
     depth[root]=deep;//��¼���
     int sons=f_s[root].size();
     for(int i=0;i<sons;i++)
     {
          DFS(f_s[root][i],deep+1);
          tree[k++]=root;//ÿ����һ�ζ�Ҫ��¼һ�θ��ڵ�
     }
     last_show[root]=k-1;//root�ڵ������ֵ�λ��
}
//��a,b��Сֵ
inline int get_min(int a,int b)
{
     return a<b?a:b;
}
void init_rmq()
{
     for(int j=0;j<k;j++)
          //rmq[j][0]=depth[tree[j]];
          rmq[j][0]=tree[j];//�����������ڵ㣬������������ȣ�����������
     int q=floor(log((double)k)/log(2.0));
     for(int i=1;i<=q;i++)
     {
          for(int j=k-1;j>=0;j--)
          {
               rmq[j][i]=rmq[j][i-1];
               if(j+(1<<(i-1))<k)
               {
                    if(depth[rmq[j+(1<<(i-1))][i-1]]<depth[rmq[j][i]])//+���ȼ�����<<�����Ը�j+1<<(i-1)Ϊj+(1<<(i-1))
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
     k=0;//��ʼʱ�����±�Ϊ0��DFS��֮��������tree[]����ĳ��ȣ�������Ϊrmq-st��n
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
          if(l>r)//��֤l<=r
          {
               int tmp=r;
               r=l;
               l=tmp;
          }
          t=floor(log(double(r-l+1))/log(2.0));//�ҵ���ʹ[l,r]��Ϊ�����ָ��
          cout<<index_name[get_min(rmq[l][t],rmq[r-(1<<t)+1][t])]<<endl;//r-(1<<t)+1���ǵ�+1
     }
     return 0;
}