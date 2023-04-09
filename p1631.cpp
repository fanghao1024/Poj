#include<cstdio>
#include<algorithm>
#include<queue>
#include<map>
using namespace std;

const int max_n=1e5+10;
int a[max_n],b[max_n],step[max_n];
int N;
typedef pair<int,int> P;
priority_queue<P,vector<P>,greater<P> > q;
int main(){
    scanf("%d",&N);
    for(int i=1;i<=N;i++) scanf("%d",&a[i]);
    for(int i=1;i<=N;i++) scanf("%d",&b[i]);
    sort(a+1,a+1+N);sort(b+1,b+1+N);
    for(int i=1;i<=N;i++) q.push(make_pair(a[i]+b[1],i)),step[i]=1;
    int k=0;
    while(k<N){
        P p=q.top();
        q.pop();
        if(k++) printf(" ");
        printf("%d",p.first);
        step[p.second]++;
        q.push(make_pair(a[p.second]+b[step[p.second]],p.second));

    }
    printf("\n");
    return 0;
}