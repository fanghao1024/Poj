#include<cstdio>
#include<cstring>

char s1[30],s2[30];
int N;
int sp[105];
int main(){
    while(scanf("%d",&N)&&N){
        int num=0;
        int mi=25;
        for(int i=0;i<N;i++){
            scanf("%s", s1);
            if(strlen(s1)<25){
                scanf("%s",s2);
                sp[i] = 25 - strlen(s1) - strlen(s2);
            }
            else sp[i]=25-strlen(s1);
            if(mi>sp[i]) mi=sp[i];
        }
        for(int i=0;i<N;i++) num+=sp[i]-mi;
        printf("%d\n",num);
        
    }
    return 0;
}