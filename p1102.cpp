#include<cstdio>
#include<algorithm>
using namespace std;


const int max_n=2e5+10;
int num[max_n];
int N,C;
int main(){
    scanf("%d %d",&N,&C);
    for(int i=1;i<=N;i++){
        scanf("%d",num+i);
    }
    sort(num+1,num+1+N);
    int l=1,x=1,y=1;
    long long ans=0;
    for(int i=1;i<=N;i++){
        while(x<=N&&num[x]-num[i]<C) x++;
        while(y<=N&&num[y]-num[i]<=C) y++;
        if(num[x]-num[i]==C&&num[y-1]-num[i]==C){
            ans+=y-x;
        }
    }
    printf("%lld\n",ans);
    return 0;
}