#include<cstdio>
#include<cmath>

const int max_n=20;
const double eps=1e-7;

double C[max_n];
int N;
double l,r;
double check(double x){
    double sum=0;
    double xx=1;
    for(int i=N;i>=0;i--){
        sum+=C[i]*xx;
        xx*=x;
    }
    return sum;
}
int main(){
    scanf("%d %lf %lf",&N,&l,&r);
    for(int i=0;i<=N;i++) scanf("%lf",&C[i]);
    while(r-l>=eps){
        double mid1=l+(r-l)/3;
        double mid2=l+(r-l)*2/3;
        if(check(mid1)<check(mid2)){
            l=mid1;
        }else{
            r=mid2;
        }
    }
    printf("%.5f\n",l);
    return 0;
}