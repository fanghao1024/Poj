#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

const int max_n=1e4+10;
bool vis[max_n];
int scc[max_n];
int N,M,cnt;
vector<int> G[max_n],rG[max_n];
vector<int> S;
void dfs1(int u){
    if(vis[u]) return ;
    vis[u]=1;
    for(int i=0;i<G[u].size();i++){
        dfs1(G[u][i]);
    }
    S.push_back(u);
}
void dfs2(int u){
    if(scc[u]) return ;
    scc[u]=cnt;
    for(int i=0;i<rG[u].size();i++){
        dfs2(rG[u][i]);
    }
}
void ko(){
    for(int i=1;i<=N;i++){
        dfs1(i);
    }
    for(int i=N-1;i>=0;i--){
        if(!scc[S[i]]){
            cnt++;
            dfs2(S[i]);
        }
    }
}
int main(){
    while(scanf("%d %d",&N,&M)!=EOF){
        if(!N&&!M) break;
        int a,b;
        for(int i=0;i<N;i++) G[i].clear(),rG[i].clear();
        while(M--){
            scanf("%d %d",&a,&b);
            G[a].push_back(b);rG[b].push_back(a);
        }
        cnt=0;
        memset(vis,0,sizeof(vis));
        memset(scc,0,sizeof(scc));
        S.clear();
        ko();
        if(cnt==1) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}