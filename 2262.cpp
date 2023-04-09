#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=1e6+10;
bool vis[max_n];
int prime[100024];
int tot;
void getprime(){
    memset(vis,0,sizeof(vis));
    vis[0]=vis[1]=1;
    tot=0;
    for(int i=2;i<=1000000;i++){
        if(!vis[i]){
            prime[tot++]=i;
            for(int j=i+i;j<=1000000;j+=i){
                vis[j]=1;
            }
        }
    }
}
int main(){
    int num,a,b;
    getprime();
    
    while(scanf("%d",&num)&&num){
        a=upper_bound(prime,prime+tot,num-1)-prime-1;
        bool flag=false;
        while(a>0){
            if(!vis[num-prime[a]]){
                flag=true;
                break;
            }
            a--;
        }
        if(flag)
            printf("%d = %d + %d\n",num,num-prime[a],prime[a]);
        else
            printf("Goldbach's conjecture is wrong.\n");
    }
    
    return 0;
}