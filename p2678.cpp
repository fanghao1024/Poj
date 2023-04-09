#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=5e4+10;

int rec[max_n];
int L,N,M;
bool check(int mid){
    int num=0;
    int pos=0;
    for(int i=1;i<=N;i++){
        if(rec[i]-pos<mid){
            num++;
            if(num>M) return false;
        }
        else{
            pos=rec[i];
        }
    }
    return true;
}
int main(){
    scanf("%d %d %d",&L,&N,&M);
    for(int i=1;i<=N;i++) scanf("%d",&rec[i]);
    N++;
    rec[N]=L;
    int l=0,r=rec[N];
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