#include<cstdio>

int A,a,B,b,P;

int main(){
    scanf("%d %d %d %d %d",&A,&a,&B,&b,&P);
    if((B<=a&&A<=P)||(A<=b&&B<=P)||(A+B<=P)) printf("Yes\n");
    else printf("No\n");
    return 0;
}