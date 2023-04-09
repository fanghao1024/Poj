#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=55;
const int max_d=105;
int N,Q,n,x;
int day[max_d];
int main(){
    while(scanf("%d %d",&N,&Q)!=EOF){
        if(!N&&!Q) break;
        memset(day,0,sizeof(day));
        int ma=0;
        for(int i=0;i<N;i++){
            scanf("%d",&n);
            for(int j=0;j<n;j++){
                scanf("%d",&x);
                day[x]++;
                ma=max(ma,x);
            }
        }
        int ans=-1;
        x=0;
        for(int i=1;i<=ma;i++){
            if(day[i]>x){
                x=day[i];
                ans=i;
            }
        }
        if(x>=Q) printf("%d\n",ans);
        else printf("0\n");
    }
    return 0;
}