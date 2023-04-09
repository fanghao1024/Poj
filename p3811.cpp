#include<cstdio>

typedef long long ll;

const int max_n=3e6+10;
ll N,P;
ll num[max_n];

int main(){
    scanf("%lld %lld",&N,&P);
    num[1]=1;
    for(int i=2;i<=N;i++){
        num[i]=((P-P/i)*num[P%i])%P;
    }
    for(int i=1;i<=N;i++) printf("%lld\n",num[i]);
    return 0;
}