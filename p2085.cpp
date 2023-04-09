#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;

priority_queue<int,vector<int>,less<int> > q;

const int max_n=1e4+10;
int N,M;
struct Node{
    int a,b,c;
}node[max_n];
bool vis[max_n],flag;
void Print(){
    if(!q.empty()){
        int x=q.top();
        q.pop();
        Print();
        if(!flag)
            flag = 1, printf("%d", x);
        else printf(" %d",x);
    }
}
int main(){
    scanf("%d %d",&N,&M);
    for(int i=1;i<=N;i++){
        scanf("%d %d %d",&node[i].a,&node[i].b,&node[i].c);
    }
    memset(vis,0,sizeof(vis));
    int count=N;
    for(int i=1;i<=M;i++){
        if(!count) break;
        for(int j=1;j<=N;j++){
            if(!vis[j]){
                int num=node[j].a*i*i+node[j].b*i+node[j].c;
                if(q.size()>M&&num>q.top()){
                    vis[j]=1;
                    count--;
                }
                if(q.size()<M||num<q.top()){
                    q.push(num);
                }
                while(q.size()>M) q.pop();
            }
        }
    }
    flag=0;
    Print();
    printf("\n");
    return 0;
}