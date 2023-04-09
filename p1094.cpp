#include<cstdio>
#include<algorithm>
using namespace std;

const int max_n=3e4+10;

int w,n;
int num[max_n];
int main(){
    scanf("%d %d",&w,&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&num[i]);
    }
    sort(num+1,num+1+n);
    int ans=0;
    int j=n,i=1;
    while(j>=i){
        if(num[j]+num[i]<=w){
            ans++;
            j--;
            i++;
        }else
        {
            ans++;
            j--;
        }
    }
    printf("%d\n",ans);
    return 0;
}