#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=17;

int a[230][230];
int dir[5][2]={{0,0},{1,0},{-1,0},{0,1},{0,-1}};
int T,N,n;
char ch;
bool Gauss(){
    int r,c;
    for(r=0,c=0;c<N*N;c++){
        int t=r;
        for(int i=r;i<N*N;i++){
            if(a[i][c]){
                t=i;
                break;
            }
        }
        if(!a[t][c]) continue;
        for(int i=c;i<=N*N;i++) swap(a[t][i],a[r][i]);
        for(int i=r+1;i<N*N;i++){
            if(a[i][c]){
                for(int j=c;j<=N*N;j++) a[i][j]^=a[r][j];
            }
        }
        r++;
    }
    for(int i=r;i<N*N;i++){
        if(a[i][N*N]) return false;
    }
    for(int i=N*N-1;i>=0;i--){
        for(int j=i+1;j<N*N;j++){
            a[i][N*N]^=a[i][j]&a[j][N*N];
        }
    }
    return true;
}

int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&N);
        memset(a,0,sizeof(a));
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                for(int d=0;d<5;d++){
                    int x=i+dir[d][0],y=j+dir[d][1];
                    if(x>=0&&x<N&&y>=0&&y<N){
                        a[i*N+j][x*N+y]=1;
                    }
                }
            }
        }
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                scanf(" %c",&ch);
                if(ch=='w') a[i*N+j][N*N]=1;
                else a[i*N+j][N*N]=0;
            }
        }
        if(Gauss()){
            int ans=0;
            for(int i=0;i<N*N;i++) if(a[i][N*N]) ans++;
            printf("%d\n",ans);
        }else{
            printf("inf\n");
        }
    }
    return 0;
}
