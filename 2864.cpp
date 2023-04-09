#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=110;
const int max_m=505;

bool vis[max_n];
int N,D;
int main(){
    while(scanf("%d %d",&N,&D)!=EOF){
        if(!N&&!D) break;
        int x;
       
        for(int i=0;i<N;i++){scanf("%d",&x);vis[i]=x;}
        for(int i=1;i<D;i++){
            for(int j=0;j<N;j++){
                scanf("%d",&x);
                vis[j]&=x;
            }
        }
        bool flag=false;;
        for(int i=0;i<N;i++){
            if(vis[i]){
                flag=true;
                break;
            }
        }
        if(flag) printf("yes\n");
        else printf("no\n");
    }
    return 0;
}