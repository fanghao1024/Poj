#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=1e5+10;

int num[max_n];
int N,C;
bool check(int mid){
    int ans=1;
    int pos=num[1];
    for(int i=2;i<=N;i++){
        if(num[i]-pos>=mid){
            ans++;
            pos=num[i];
            if(ans>=C) return true;
        }
    }
    return false;
}
int main(){
    scanf("%d %d",&N,&C);
    for(int i=1;i<=N;i++) scanf("%d",&num[i]);
    sort(num+1,num+1+N);
    int l=1,r=num[N];
    int ans=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            ans=mid;
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    printf("%d\n",ans);
    return 0;
}