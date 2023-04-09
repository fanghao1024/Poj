#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int max_n = 1e7 + 10;

int rec[max_n];
int N, M;

int calPos(int x, int y)
{
    if(!x||!y) return 0;
    return (x - 1) * M + y;
}
int cal(int x1,int y1,int x2,int y2){
    return rec[calPos(x2,y2)]-rec[calPos(x1-1,y2)]-rec[calPos(x2,y1-1)]+rec[calPos(x1-1,y1-1)];
}
void div(int i,int j,int val){
    if(i>N||j>M) return ;
    else rec[calPos(i,j)]+=val;
}
int main()
{
    int x1, y1, x2, y2;
    int p, q;
    while (scanf("%d %d", &N, &M) != EOF)
    {
        memset(rec, 0, sizeof(rec));
        scanf("%d", &p);
        while (p--)
        {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            //rec[calPos(x1, y1)]++;
            //rec[calPos(x1, y2 + 1)]--;
            //rec[calPos(x2+1, y1)]--;
            //rec[calPos(x2 + 1, y2 + 1)]++;
            div(x1,y1,1);
            div(x1,y2+1,-1);
            div(x2+1,y1,-1);
            div(x2+1,y2+1,1);
        }
        for(int i=1;i<=N;i++){
            for(int j=1;j<=M;j++){
                rec[calPos(i,j)]+=rec[calPos(i-1,j)]+rec[calPos(i,j-1)]-rec[calPos(i-1,j-1)];
            }
        }
        /*
        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= M; j++)
            {
                if(rec[calPos(i,j)]>1) rec[calPos(i,j)]=1;
            }
        }
        */
       for(int i=1;i<=N*M;i++) if(rec[i]!=0) rec[i]=1;
       for (int i = 1; i <= N; i++)
       {
            for (int j = 1; j <= M; j++)
            {
                rec[calPos(i, j)] += rec[calPos(i - 1, j)] + rec[calPos(i, j - 1)] - rec[calPos(i - 1, j - 1)];
            }
       }
        scanf("%d",&p);
        while(p--){
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            /*
            if(cal(x1,y1,x2,y2)==(x2-x1+1)*(y2-y1+1)){
                printf("YES\n");
            }else{
                printf("No\n");
            }*/
            int s = rec[calPos(x2, y2)] - rec[calPos(x2, y1 - 1)] - rec[calPos(x1 - 1, y2)] + rec[calPos(x1 - 1, y1 - 1)];
            if (s == (y2 - y1 + 1) * (x2 - x1 + 1))
            {
                printf("YES\n");
            }
            else
            {
                printf("NO\n");
            }
        }
    }
    return 0;
}