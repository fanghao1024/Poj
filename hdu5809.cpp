#include<cstdio>
#include<algorithm>
using namespace std;

typedef long long ll;
const int max_n = 100010; 
const int max_k=2;
const ll Inf=1e18;
const int inf=0x3fffffff;
int T, N, Q,idx;
struct Node{
    int dim[max_k];
    int id;
}node[max_n];
int rec[max_n];
ll ans;
int ansx,ansy;
int ansid;
bool cmp(const Node& a,const Node& b){
    return a.dim[idx]<b.dim[idx];
}
int par[max_n],hei[max_n];
void init(){
    for(int i=0;i<N;i++) par[i]=i,hei[i]=1;
}
int find(int x){
    if(x!=par[x]){
        par[x]=find(par[x]);
    }
    return par[x];
}
void unite(int x,int y){
    int a=find(x),b=find(y);
    if(a!=b){
        if(hei[a]<hei[b]){
            par[b]=a;
        }else{
            par[a]=b;
            if(hei[a]==hei[b]){
                hei[b]++;
            }
        }
    }
}
bool same(int x,int y){
    return find(x)==find(y);
}

struct KD_Tree{
    void build(int l,int r,int dep){
        if(l>r) return ;
        int mid=(l+r)>>1;
        idx=dep%max_k;
        nth_element(node+l,node+mid,node+r+1,cmp);
        rec[node[mid].id]=mid;
        build(l,mid-1,dep+1);
        build(mid+1,r,dep+1);
    }
    inline ll dist(Node a,Node b){
        ll res=0;
        for(int i=0;i<max_k;i++){
            res+=((ll)a.dim[i]-b.dim[i])*((ll)a.dim[i]-b.dim[i]);
        }
        return res?res:Inf;
    }
    void query(int l,int r,int dep,Node p){
        if(l>r) return ;
        int mid=(l+r)>>1;
        int d=dep%max_k;
        ll dis=dist(node[mid],p);
        if(dis<ans||(dis==ans&&node[mid].dim[0]<ansx)||(dis==ans&&node[mid].dim[0]==ansx&&node[mid].dim[1]<ansy)){
            ans=dis;
            ansx=node[mid].dim[0];
            ansy=node[mid].dim[1];
            ansid=node[mid].id;
        }
        ll rd = ((ll)node[mid].dim[d] - p.dim[d]) * ((ll)node[mid].dim[d] - p.dim[d]);
        if(p.dim[d]<node[mid].dim[d]){
            query(l,mid-1,dep+1,p);
            if(rd<=ans) query(mid+1,r,dep+1,p);
        }else{
            query(mid+1,r,dep+1,p);
            if(rd<=ans) query(l,mid-1,dep+1,p);
        }
    }
}KDT;
int main(){
    scanf("%d",&T);
    for(int caseNo=1;caseNo<=T;caseNo++){
        scanf("%d %d",&N,&Q);
        for(int i=0;i<N;i++){
            for(int j=0;j<max_k;j++) scanf("%d",&node[i].dim[j]);
            node[i].id=i;
        }
        KDT.build(0,N-1,0);
        init();
        for(int i=0;i<N;i++){
            ans = Inf;
            ansx = ansy = inf;
            ansid = -1;
            KDT.query(0, N - 1, 0, node[rec[i]]);
            if(!same(i,ansid)) unite(i,ansid);
        }
        printf("Case #%d:\n",caseNo);
        int x,y;
        while(Q--){
            scanf("%d %d",&x,&y);
            x--;y--;
            if(same(x,y)) printf("YES\n");
            else printf("NO\n");
        }
    }
    return 0;
}