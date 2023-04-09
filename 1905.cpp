#include<cstdio>
#include<cmath>

const double Pi=acos(-1.0);
const double eps=1e-11;
double L,n,C;

int main(){
    while(scanf("%lf %lf %lf",&L,&n,&C)!=EOF){
        if(L==-1&&n==-1&&C==-1) break;
        if(n*C==0) {printf("0.000\n");continue;}
        double l=eps,r=Pi/2;
        while(fabs(r-l)>eps){
            double mid=(l+r)/2;
            double hu=mid/sin(mid);
            if(hu>1+n*C) r=mid;
            else l=mid;
        }
        double theta=l;
        double R=L/(2*sin(theta));
        printf("%.3f\n",R*(1-cos(theta)));
    }
    return 0;
}