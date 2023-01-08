#include<stdio.h>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;

struct Cow{
    int score;
    int aid;
};
Cow cow[100010];
int bef[100010];
int aft[100010];
int N, C, F;

bool cmp(const Cow& a,const Cow& b){
    return a.score<b.score;
}


int main(){
    scanf("%d %d %d",&N,&C,&F);
    int score,aid;

    for(int i=0;i<C;i++){
        scanf("%d %d",&score,&aid);
        cow[i].score=score;
        cow[i].aid=aid;
    }
    
    sort(cow,cow+C,cmp);

    priority_queue<int,vector<int>,less<int> > pq;

    int sum=0;
    for(int i=0;i<C;i++){
        bef[i]=sum;
        sum+=cow[i].aid;
        pq.push(cow[i].aid);
        if(pq.size()>N/2){
            sum-=pq.top();
            pq.pop();
        }
        
    }

    while(!pq.empty()){
        pq.pop();
    }
    sum=0;
    for(int i=C-1;i>=0;i--){
        aft[i]=sum;
        sum+=cow[i].aid;
        pq.push(cow[i].aid);
        if(pq.size()>N/2){
            sum-=pq.top();
            pq.pop();
        }
        
    }
    
    int ans;
    bool flag=false;
    for(int i=C-1-N/2;i>=N/2;i--){
        if(bef[i]+cow[i].aid+aft[i]<=F){
            ans=cow[i].score;
            flag=true;
            break;
        }
    }
    if(flag){
        printf("%d\n",ans);
    }else{
        printf("-1\n");
    }
    
    return 0;
}