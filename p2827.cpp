#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_m=7e6+10;
int n, m, q, u, v, t;
int now[max_m],q1[max_m],q2[max_m];
bool cmp(int x,int y){
    return x>y;
}
int main(){
    scanf("%d %d %d %d %d %d",&n,&m,&q,&u,&v,&t);
    int x,sum=0;
    double p=(u+0.0)/v;
    for(int i=1;i<=n;i++){
        scanf("%d",&now[i]);
    }
    sort(now+1,now+1+n,cmp);
    int h=1,f1=1,f2=1;
    int r1=1,r2=1;
    int top;
    for(int i=1;i<=m;i++){
        if(h>n){
            if(q1[f1]>q2[f2]) top=q1[f1++];
            else top=q2[f2++];
        }
        else if(now[h]>=q1[f1]&&now[h]>=q2[f2]){
            top=now[h++];
        }
        else if(q1[f1]>=now[h]&&q1[f1]>=q2[f2]){
            top=q1[f1++];
        }else top=q2[f2++];
        top+=sum;
        if(i%t==0) printf("%d ",top);
        int a=int(top*p),b=top-a;
        q1[r1++]=a-sum-q;
        q2[r2++]=b-sum-q;
        sum+=q;
    }
    printf("\n");
    int count=1;
    priority_queue<int,vector<int>,less<int> > Q;
    while(h<=n) Q.push(now[h++]);
    while(f1<r1) Q.push(q1[f1++]); 
    while(f2<r2) Q.push(q2[f2++]);
    while(!Q.empty()){
        if(count%t==0){
            top=Q.top();
            printf("%d ",top+sum);
        }
        Q.pop();
        count++;
    }
    printf("\n");
    return 0;
}