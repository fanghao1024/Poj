#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int head[30],cnt,color[30];
struct Edge{
    int to,nxt;
}edge[30*30];
int N;
char ch[50];
bool vis[30];
void init(){
    memset(head,-1,sizeof(head));
    cnt=0;
    memset(vis,0,sizeof(vis));
    memset(color,0,sizeof(color));
}
void add_edge(int x,int y){
    edge[cnt].to=y;
    edge[cnt].nxt=head[x];
    head[x]=cnt++;
}
void dfs(int p){
    if(p==N) return;
    int c=1;
    bool flag;
    while(1){
        flag=true;
        for(int i=head[p];i!=-1;i=edge[i].nxt){
            int v=edge[i].to;
            if(color[v]==c){
                c++;
                flag=false;
                break;
            }
        }
        if(flag){
            color[p]=c;
            dfs(p+1);
            break;
        }
    }
}
int main(){
    while(scanf("%d",&N)&&N){
        init();
        for(int i=1;i<=N;i++){
            scanf("%s",ch);
            int x=ch[0]-'A';
            for(int j=2;j<strlen(ch);j++){
                add_edge(x,ch[j]-'A');
                add_edge(ch[j]-'A',x);
            }
        }
        for(int i=0;i<N;i++){
            if(!vis[i]){
                dfs(i);
            }
        }
        int ans=0;
        for(int i=0;i<N;i++) ans=max(ans,color[i]);
        if(ans==1)
            printf("1 channel needed.\n");
        else
            printf("%d channels needed.\n",ans);
    }
    return 0;
}