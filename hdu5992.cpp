#include<cstdio>
#include<algorithm>
using namespace std;

typedef long long ll;
#define sq(x) (x)*(x)
const int max_n=200010;
const int K=2;
const ll inf=1e18;
int T,N,M,idx;
struct Node{
    int pos[K];
    int price;
    int id;
}a[max_n],temp;
bool cmp(const Node& a,const Node& b){
    return a.pos[idx]<b.pos[idx];
}
int rec[max_n];
ll ans;
int ansid;

struct KD_Tree{
    void build(int l,int r,int dep){
        if(l>r) return ;
        int mid=(l+r)>>1;
        idx=dep%K;
        nth_element(a+l,a+mid,a+r+1,cmp);
        rec[a[mid].id]=mid;
        build(l,mid-1,dep+1);
        build(mid+1,r,dep+1);
    }
    ll dist(Node p,Node q){
        ll res=0;
        for(int i=0;i<K;i++){
            res+=sq((ll)p.pos[i]-q.pos[i]);
        }
        return res;
    }
    void query(int l,int r,int dep,Node p){
        if(l>r) return ;
        int mid=(l+r)>>1;
        ll dis=dist(a[mid],p);
        int d=dep%K;
        if((dis<ans&&a[mid].price<=p.price)||(dis==ans&&a[mid].price<=p.price&&ansid>a[mid].id)){
            //printf("~~~dis:%lld==x:%d y:%d price:%d\n",dis,a[mid].pos[0],a[mid].pos[1],a[mid].price);
            ans=dis;
            ansid=a[mid].id;
        }
        ll rd=sq((ll)a[mid].pos[d]-p.pos[d]);
        if(p.pos[d]<a[mid].pos[d]){
            query(l,mid-1,dep+1,p);
            if(rd<ans) query(mid+1,r,dep+1,p);
        }else{
            query(mid+1,r,dep+1,p);
            if(rd<ans) query(l,mid-1,dep+1,p);
        }
    }
}KDT;

int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d %d",&N,&M);
        for(int i=0;i<N;i++){
            scanf("%d %d %d",&a[i].pos[0],&a[i].pos[1],&a[i].price);
            a[i].id=i;
        }
        KDT.build(0,N-1,0);
        int x,y,c;
        for(int i=0;i<M;i++){
            scanf("%d %d %d",&x,&y,&c);
            temp.pos[0]=x;
            temp.pos[1]=y;
            temp.price=c;
            ans=inf;
            ansid=N;
            KDT.query(0,N-1,0,temp);
            int position=rec[ansid];
            printf("%d %d %d\n",a[position].pos[0],a[position].pos[1],a[position].price);
        }
    }
    return 0;
}