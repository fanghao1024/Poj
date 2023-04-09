#include<cstdio>
#include<cstring>
#include<algorithm>
#include<deque>
#include<map>
#include<cmath>
using namespace std;

const int max_n=1e5+10;
const double eps=1e-5;
int n,S,T;
int rec[max_n],sum[max_n],q[max_n];
double b[max_n];
typedef pair<int,int> P;
bool check(double mid){
    int f=1,r=0;
    b[0]=0;
    for(int i=1;i<=n;i++){
        b[i]=rec[i]-mid+b[i-1];
    }
    for(int i=1;i<=n;i++){
        if(i>=S){
            while (f <= r && i - S >= 1 && b[i - S] < b[q[r]])
                r--;
            q[++r] = i - S;
        }
        while(f<=r&&i-T>=1&&q[f]<i-T) f++;
        if(f<=r&&b[i]-b[q[f]]>=0) return true;
    }
    return false;
}
int main(){
    scanf("%d %d %d",&n,&S,&T);
    double l=1e4,r=-1e4;
    sum[0]=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&rec[i]);
        l=fmin(l,rec[i]);
        r=fmax(r,rec[i]);
        sum[i]=sum[i-1]+rec[i];
    }
    while(r-l>=eps){
        double mid=l+(r-l)/2;
        if(check(mid)){
            l=mid;
        }else{
            r=mid;
        }
    }
    printf("%.3f\n",l);
    return 0;
}
