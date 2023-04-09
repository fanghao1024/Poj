#include<cstdio>

const int max_n=55;
int num[max_n];

int N,sum;

int main(){
    int kase=1;
    while(scanf("%d",&N)&&N){
        sum=0;
        for(int i=0;i<N;i++){
            scanf("%d",&num[i]);
            sum+=num[i];
        }
        int x=sum/N;
        int ans=0;
        for(int i=0;i<N;i++) if(num[i]>x) ans+=(num[i]-x);
        printf("Set #%d\n",kase++);
        printf("The minimum number of moves is %d.\n", ans);
        printf("\n");
    }
    return 0;
}