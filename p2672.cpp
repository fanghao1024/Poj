#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=1e5+10;

struct Node{
    int s,a;
}node[max_n];
int n;
int sum[max_n],q[max_n],h[max_n];
bool cmp(const Node& m,const Node& n){
    return m.a>n.a;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&node[i].s);
    for(int i=1;i<=n;i++) scanf("%d",&node[i].a);
    sort(node+1,node+1+n,cmp);
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+node[i].a;
    for(int i=1;i<=n;i++) q[i]=max(q[i-1],2*node[i].s);
    for(int i=n;i>=1;i--) h[i]=max(h[i+1],node[i].a+node[i].s*2);
    for(int i=1;i<=n;i++) printf("%d\n",max(sum[i]+q[i],sum[i-1]+h[i]));
    return 0;
}