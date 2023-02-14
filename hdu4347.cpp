#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;

const int max_n=50010;
const int max_k=5;
#define sq(x) (x)*(x)
int N,K,idx,T,M;
struct Node{
    int dim[max_k];
}node[max_n];
bool cmp(const Node& a,const Node& b){
    return a.dim[idx]<b.dim[idx];
}
typedef pair<int,int> P;
priority_queue<P> pp;
struct KD_Tree{
    void build(int l,int r,int dep){
        if(l>r) return ;
        int mid=(l+r)>>1;
        idx=dep%K;
        nth_element(node+l,node+mid,node+r+1,cmp);
        build(l,mid-1,dep+1);
        build(mid+1,r,dep+1);
    }
    int dist(Node a,Node b){
        int res=0;
        for(int i=0;i<K;i++){
            res+=sq(a.dim[i]-b.dim[i]);
        }
        return res;
    }
    void query(int l,int r,int dep,Node p){
        if(l>r) return ;
        int mid=(l+r)>>1;
        int dis=dist(node[mid],p);
        int d=dep%K;
        if(pp.size()<M||pp.top().first>dis){
            pp.push(make_pair(dis,mid));
            while(pp.size()>M) pp.pop();
        }
        int rd=sq(node[mid].dim[d]-p.dim[d]);
        if(p.dim[d]<node[mid].dim[d]){
            query(l,mid-1,dep+1,p);
            if(rd<pp.top().first) query(mid+1,r,dep+1,p);
        }else
        {
            query(mid+1,r,dep+1,p);
            if(rd<pp.top().first) query(l,mid-1,dep+1,p);
        }
        
    }
}KDT;
int num[max_k];
Node temp;
int ans[20];
int main(){
    while(scanf("%d %d",&N,&K)!=EOF){
        for(int i=0;i<N;i++){
            for(int j=0;j<K;j++) scanf("%d",&node[i].dim[j]);
        }
        KDT.build(0,N-1,0);
        scanf("%d",&T);
        while(T--){
            for(int i=0;i<K;i++){
                scanf("%d",&temp.dim[i]);
            }
            scanf("%d",&M);
            KDT.query(0,N-1,0,temp);
            printf("the closest %d points are:\n",M);
            int pos=M;
            while(!pp.empty()){
                ans[pos--]=pp.top().second;
                pp.pop();
            }
            for(int i=1;i<=M;i++){
                for(int j=0;j<K;j++){
                    if(j) printf(" ");
                    printf("%d",node[ans[i]].dim[j]);
                }
                printf("\n");
            }
        }
    }
    return 0;
}