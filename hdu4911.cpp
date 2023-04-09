#include<cstdio>

typedef long long ll;

const int max_n=1e5+10;
ll n,k,sum;
ll a[max_n],b[max_n];
void merge(int l,int mid,int r){
    int i=l,j=mid+1,t=0;
    while(i<=mid&&j<=r){
        if(a[i]>a[j]){
            sum+=mid-i+1;
            b[t++]=a[j++];
        }else{
            b[t++]=a[i++];
        }
    }
    while(i<=mid) b[t++]=a[i++];
    while(j<=r) b[t++]=a[j++];
    for(int i=0;i<t;i++) a[l+i]=b[i];
}
void merge_sort(int l,int r){
    if(l<r){
        int mid=l+((r-l)>>1);
        merge_sort(l,mid);
        merge_sort(mid+1,r);
        merge(l,mid,r);
    }
}
int main(){
    while(scanf("%lld %lld",&n,&k)!=EOF){
        sum=0;
        for(int i=1;i<=n;i++) scanf("%lld",a+i);
        merge_sort(1,n);
        if(sum<=k) printf("0\n");
        else printf("%lld\n",sum-k);
    }
    return 0;
}