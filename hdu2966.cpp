#include<cstdio>
#include<algorithm>
using namespace std;

#define sq(x) (x)*(x)
typedef long long ll;
const int max_n=100010;
const int K=2;
const ll inf=1e18;

int T,N,idx;
ll ans;
struct Node{
    int dim[K];
}a[max_n],p[max_n];
bool cmp(const Node& a,const Node& b){
    return a.dim[idx]<b.dim[idx];
}
struct KD_Tree{
    void build(int l,int r,int dep){
        if(l>r) return ;
        int mid=(l+r)>>1;
        idx=dep%K;
        nth_element(a+l,a+mid,a+r+1,cmp);
        build(l,mid-1,dep+1);
        build(mid+1,r,dep+1);
    }
    ll dis(Node a,Node b){
        ll res=0;
        for(int i=0;i<K;i++){
            res+=sq((ll)a.dim[i]-b.dim[i]);
        }
        return res?res:inf;
    }
    void query(int l,int r,int dep,Node node){
        if(l>r) return ;
        int mid=(l+r)>>1;
        int dim=dep%K;
        ll dist=dis(a[mid],node);
        if(dist<ans) ans=dist;
        ll rd=sq((ll)node.dim[dim]-a[mid].dim[dim]);
        if(node.dim[dim]<a[mid].dim[dim]){
            query(l,mid-1,dep+1,node);
            if(rd<ans) query(mid+1,r,dep+1,node);
        }else{
            query(mid + 1, r, dep + 1, node);
            if(rd<ans) query(l, mid - 1, dep + 1, node);
        }
    }
}KDT;
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&N);
        for(int i=0;i<N;i++){
            for(int j=0;j<K;j++) scanf("%d",&a[i].dim[j]);
            p[i]=a[i];
        }
        KDT.build(0,N-1,0);
        for(int i=0;i<N;i++){
            ans=inf;
            KDT.query(0,N-1,0,p[i]);
            printf("%lld\n",ans);
        }
    }
    return 0;
}