#include<queue>
#include<cstdio>
#include<cstring>
using namespace std;

const int max_m=310;
const int max_n=1e5+10;
int N,M,T,x;
int pri[max_n];
char ch[20];
bool vis[max_m];
queue<int> q[max_m];
queue<int> Q;
int main(){
    memset(vis,0,sizeof(vis));
    scanf("%d %d",&N,&M);
    for(int i=0;i<N;i++) scanf("%d",pri+i);
    scanf("%d",&T);
    while(T--){
        scanf("%s",ch);
        if(ch[1]=='u'){
            scanf("%d",&x);
            q[pri[x]].push(x);
            if(!vis[pri[x]]){
                Q.push(pri[x]);
                vis[pri[x]] = 1;
            }
            
        }else{
            int v=q[Q.front()].front();
            printf("%d\n",v);
            q[Q.front()].pop();
            if (q[Q.front()].empty()){
                vis[Q.front()]=0; 
                Q.pop();
            }
        }
    }
    return 0;
}
