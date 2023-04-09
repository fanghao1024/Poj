#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

struct Point{
    double x,y;
};
Point A,B,C,D;
Point L1,R1,L2,R2;
Point l1,r1,l2,r2;

int T;
double P,Q,R;
double dis(double x1,double y1,double x2,double y2){
    return sqrt(1e-7+(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
double cal2(double x1,double y1,double x2,double y2){
    return dis(x1,y1,x2,y2)/R+dis(x2,y2,D.x,D.y)/Q;
}
double cal1(double x,double y){
    l1.x=C.x;l1.y=C.y;l2.x=D.x;l2.y=D.y;
    for(int i=0;i<100;i++){
        int dx=(l2.x-l1.x)/3;
        int dy=(l2.y-l1.y)/3;
        int x1=l1.x+dx;
        int y1=l1.y+dy;
        int x2=l2.x-dx;
        int y2=l2.y-dy;
        if(cal2(x,y,x1,y1)>cal2(x,y,x2,y2)){
            l1.x=x1;
            l1.y=y1;
        }else{
            l2.x=x2;
            l2.y=y2;
        }
    }
    return cal2(x,y,l1.x,l1.y)+dis(A.x,A.y,x,y)/P;
}
int main(){
    scanf("%d",&T);
    while(T--){ 
        scanf("%lf %lf",&A.x,&A.y);
        scanf("%lf %lf", &B.x, &B.y);
        scanf("%lf %lf", &C.x, &C.y);
        scanf("%lf %lf", &D.x, &D.y);
        scanf("%lf %lf %lf",&P,&Q,&R);
        L1.x=A.x;L1.y=A.y;L2.x=B.x;L2.y=B.y;
        for(int i=0;i<100;i++){
            int dx=(L2.x-L1.x)/3;
            int dy=(L2.y-L1.y)/3;
            int x1=L1.x+dx,y1=L1.y+dy;
            int x2=L2.x-dx,y2=L2.y-dy;
            if(cal1(x1,y1)>cal1(x2,y2)){
                L1.x=x1;
                L1.y=y1;
            }else{
                L2.x=x2;
                L2.y=y2;
            }
        }
        printf("%.2f\n",cal1(L1.x,L1.y));
    }
    return 0;
}