#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

const int max_n=3010;
int num[max_n];
int vis[max_n];
int N;

int main(){
    while(scanf("%d",&N)!=EOF){
        int pre,cur;
        scanf("%d",&pre);
        memset(vis, 0, sizeof(vis));
        for(int i=1;i<N;i++){
            scanf("%d",&cur);
            vis[abs(pre-cur)]++;
            pre=cur;
        }
        if(N==1){printf("Jolly\n");continue;}
        
        int i;
        for(i=1;i<N;i++){
            if(vis[i]==0) break;
        }
        if(i==N)
            printf("Jolly\n");
        else
            printf("Not jolly\n");
    }
    return 0;
}
