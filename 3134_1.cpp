#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=100;

int num[max_n];
int N,dep;
bool dfs(int now,int d){
    if(d>dep) return false;
    if(now==N) return true;
    if((now<<(dep-d))<N) return false;
    num[d]=now;
    for(int i=0;i<=d;i++){
        if(dfs(now+num[i],d+1)) return true;
        if(dfs(now-num[i],d+1)) return true;
    }
    return false;
}
int main(){
    while(scanf("%d",&N)&&N){
        for(dep=0;dep<=max_n;dep++){
            //memset(num,0,sizeof(num));
            if(dfs(1,0)){
                printf("%d\n",dep);
                break;
            }
        }
    }
    return 0;
}