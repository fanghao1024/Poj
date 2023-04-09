#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int g[50][2000];
int degree[50];
int st[2000];
bool vis[2000];
int npoints,nroads,start,top;
void eular(int u){

    for(int i=1;i<=nroads;i++){
        if(!vis[i]&&g[u][i]){
            vis[i]=1;
            eular(g[u][i]);
            st[++top] = i;
        }
    }
}
int main(){
    int x,y,z;
    while(scanf("%d %d",&x,&y)!=EOF){
        if(!x&&!y) break;
        scanf("%d",&z);
        npoints=nroads=top=0;
        memset(degree,0,sizeof(degree));
        memset(vis,0,sizeof(vis));
        memset(g,0,sizeof(g));
        start=x<y?x:y;
        npoints = max(npoints, max(x, y));
        nroads=max(nroads,z);
        g[x][z]=y;
        g[y][z]=x;
        degree[x]++;
        degree[y]++;
        while(scanf("%d %d",&x,&y)!=EOF){
            if(!x&&!y) break;
            scanf("%d",&z);
            npoints = max(npoints,max(x, y));
            nroads = max(nroads, z);
            g[x][z] = y;
            g[y][z] = x;
            degree[x]++;
            degree[y]++;
        }
        bool flag=true;
        for(int i=1;i<=npoints;i++){
            if(degree[i]%2){
                flag=false;
                break;
            }
        }
        if(!flag) printf("Round trip does not exist.\n");
        else{
            eular(start);
            printf("%d",st[top--]);
            for(int i=top;i>0;i--){
                printf(" %d",st[i]);
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}