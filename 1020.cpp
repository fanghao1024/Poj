#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int L[15],col[160];

int T,S,N;
bool dfs(int p){
    if(p>=N) return true;
    int c=S+1,pos;
    for(int i=1;i<=S;i++){
        if(c>col[i]){
            c=col[i];
            pos=i;
        }
    }
    for(int i=10;i>=1;i--){
        if(!L[i]) continue;
        if(pos+i-1<=S&&c+i<=S){
            bool flag=true;
            for(int k=pos;k<=pos+i-1;k++){
                if(col[k]!=col[pos]){
                    flag=false;
                    break;
                }
            }
            if(!flag) continue;
            for(int k=pos;k<=pos+i-1;k++){
                col[k]+=i;
            }
            L[i]--;
            if(dfs(p+1)) return true;
            L[i]++;
            for (int k = pos; k <= pos + i - 1; k++)
            {
                col[k] -= i;
            }
        }
    }
    return false;
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d %d",&S,&N);
        int x,area=0;
        memset(L,0,sizeof(L));
        memset(col,0,sizeof(col));
        for(int i=1;i<=N;i++){
            scanf("%d",&x);
            L[x]++;
            area+=x*x;
        }
        if(area!=S*S||!dfs(0))
            printf("HUTUTU!\n");
        else
            printf("KHOOOOB!\n");
    }
    return 0;
}