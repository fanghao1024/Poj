#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
using namespace std;

const int max_n=1e5+10;
const int max_m=2e5+10;

int N,M;
int par[max_n],dep[max_n];

struct Edge{
    int from,to;
}edge[max_m];
set<int> si;
map<int,int> mii;
bool vis[max_n];
void init(){
    for(int i=1;i<=N;i++){
        par[i]=i;
        dep[i]=1;
    }
}
int find(int x){
    if(x!=par[x]){
        par[x]=find(par[x]);
    }
    return par[x];
}
void unite(int x,int y){
    int a=find(x);
    int b=find(y);
    if(a!=b){
        if(dep[a]>dep[b]){
            par[b]=a;
        }else{
            par[a]=b;
            if(dep[a]==dep[b]) dep[b]++;
        }
    }

}
inline int read() // 读入优化
{
    int n = 0;
    char ch = getchar();
    while (ch > '9' || ch < '0')
        ch = getchar();
    while (ch >= '0' && ch <= '9')
    {
        n = n * 10 + ch - '0';
        ch = getchar();
    }
    return n;
}
inline void print(int n) // 输出优化
{
    if (n > 9)
        print(n / 10);
    putchar(n % 10 + '0');
    return;
}
int main(){
    //scanf("%d %d",&N,&M);
    N=read();
    M=read();
    int p,q;
    for(int i=0;i<M;i++){
        //scanf("%d %d",&p,&q);
        p=read();q=read();
        edge[i].from=p;
        edge[i].to=q;
        si.insert(p);
        si.insert(q);
    }
    int pos=1;
    for(set<int>::iterator it=si.begin();it!=si.end();it++){
        mii[*it]=pos++;
    }
    init();
    for(int i=0;i<M;i++){
        unite(mii[edge[i].from],mii[edge[i].to]);
    }
    memset(vis,0,sizeof(vis));
    int ans=0;
    for(int i=1;i<=N;i++){
        if(vis[find(i)]) continue;
        ans++;
        vis[find(i)]=1;
    }
    //printf("%d\n",ans);
    print(ans);
    return 0;
}
