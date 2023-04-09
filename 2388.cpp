#include<cstdio>
#include<algorithm>
using namespace std;

const int max_n=1e4+10;
int num[max_n],N;
int read(){
    int n=0;
    char c=getchar();
    while(c>'9'||c<'0') c=getchar();
    while(c<='9'&&c>='0'){
        n=n*10+c-'0';
        c=getchar();
    }
    return n;
}
int quick_sort(int l,int r,int k){
    int mid=num[(l+r)>>1];
    int i=l,j=r-1;
    while(i<=j){
        while(num[i]<mid) i++;
        while(num[j]>mid) j--;
        if(i<=j){
            swap(num[i],num[j]);
            i++;
            j--;
        }
    }
    if(l<=j&&k<=j) return quick_sort(l,j+1,k);
    if(i<r&&k>=i) return quick_sort(i,r,k);
    return num[k];
}
int main(){
    N=read();
    for(int i=0;i<N;i++) num[i]=read();
    int k=N/2;
    printf("%d\n",quick_sort(0,N,k));
    return 0;
}