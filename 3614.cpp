#include<stdio.h>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

typedef pair<int,int> P;
P cow[2510];
P sunscreen[2510];

bool cmp(const P& a,const P& b){
    if(a.first!=b.first){
        return a.first < b.first;
    }else{
        return a.second<b.second;
    }
    
}

int main(){
    int C,L;
    scanf("%d %d",&C,&L);
    int x,y;
    for(int i=0;i<C;i++){
        scanf("%d%d",&x,&y);
        cow[i].first=x;
        cow[i].second=y;
    }
    for (int i = 0; i < L; i++)
    {
        scanf("%d%d", &x, &y);
        sunscreen[i].first = x;
        sunscreen[i].second = y;
    }
    sort(cow,cow+C,cmp);
    sort(sunscreen,sunscreen+L,cmp);
    priority_queue<P,vector<P>,greater<P> > pq;
    int ans=0;
    int index=0;
    for(int i=0;i<L;i++){
        while(index<C && cow[index].first<=sunscreen[i].first){
            pq.push(make_pair(cow[index].second,cow[index].first));
            index++;
        }
        while(!pq.empty()&&sunscreen[i].second){
            if(pq.top().first>=sunscreen[i].first){
                sunscreen[i].second--;
                ans++;
            }
            pq.pop();
        }
    }
    printf("%d\n",ans);
    return 0;
}