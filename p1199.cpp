#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=505;

int num[max_n][max_n];

int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            scanf("%d",&num[i][j]);
            num[j][i]=num[i][j];
        }
    }
    int ans=-1;
    for(int i=1;i<=n;i++){
        sort(num[i]+1,num[i]+1+n);
        ans=max(ans,num[i][n-1]);
    }
    printf("1\n%d\n",ans);
    return 0;
}