#include<cstdio>
#include<cstring>

const int max_n=1024;
int a[max_n][max_n],d[max_n][max_n];
int n,m;
int main(){
    scanf("%d %d",&n,&m);
    int x1,y1,x2,y2;
    memset(a,0,sizeof(a));
    memset(d,0,sizeof(d));
    while(m--){
        scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
        d[x1][y1]+=1;
        d[x1][y2+1]-=1;
        d[x2+1][y1]-=1;
        d[x2+1][y2+1]+=1;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            a[i][j]=d[i][j]+a[i-1][j]+a[i][j-1]-a[i-1][j-1];
            if(j-1) printf(" ");
            printf("%d",a[i][j]);
        }
        printf("\n");
    }
    return 0;
}