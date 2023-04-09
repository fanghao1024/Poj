#include<cstdio>

const int inf=0x3f3f3f3f;

int N,x,y,z;
void calc(){
    int area=inf;
    for(int i=1;i<=N;i++){
        if(N%i!=0) continue;
        for(int j=1;j<=(N/i);j++){
            if((N/i)%j!=0) continue;
            int k=(N/i)/j;
            if(area>2*(i*j+i*k+j*k)){
                area=2*(i*j+i*k+j*k);
                x=i;y=j;z=k;
            }
        }
    }
}
int main(){
    scanf("%d",&N);
    calc();
    printf("%d %d %d\n",x,y,z);
    return 0;
}