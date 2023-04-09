#include<cstdio>
#include<cmath>

const int max_n=1e4+10;
const double Pi=acos(-1.0);
double S[max_n];
int N,F;
bool check(double mid){
    int ans=0;
    for(int i=1;i<=N;i++){
        ans+=(int)(S[i]/mid);
        if(ans>=F+1) return true;
    }
    return false;
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d %d", &N, &F);
        double l = 0, r = 0;
        int x;
        for (int i = 1; i <= N; i++)
        {
            scanf("%d", &x);
            S[i] = Pi * x * x;
            if(r<S[i]) r=S[i];
        }
        while (abs(r - l) > 1e-5)
        {
            double mid = l + (r - l) / 2;
            if (check(mid))
            {
                l = mid;
            }
            else
            {
                r = mid;
            }
        }
        printf("%.4f\n", r);
    }
    return 0;
}
