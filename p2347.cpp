#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=1024;

bool vis[max_n];
int v[6]={1,2,3,5,10,20};
int w[6];

int main(){
    int sum=0;
    for(int i=0;i<6;i++) scanf("%d",&w[i]),sum+=v[i]*w[i];
    vis[0]=1;
    int ans=0;
    for(int i=0;i<6;i++){
        for(int k=1;w[i]>0;k<<=1){
            int c=min(k,w[i]);
            for(int j=sum;j>=c*v[i];j--){
                if(!vis[j]&&vis[j-c*v[i]]){
                    vis[j]=1;
                    ans++;
                }
            }
            w[i]-=k;
        }
    }
    printf("Total=%d\n",ans);
    return 0;
}