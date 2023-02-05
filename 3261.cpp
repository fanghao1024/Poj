#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;

const int max_n=20005;
int rec[max_n],sa[max_n],rk[max_n],height[max_n];
int wa[max_n],wb[max_n],cnt[max_n];
int N,K;
void da(int *r,int n,int m){
	int *x=wa;
	int *y=wb;
	int i,j,k;
	for(i=0;i<m;i++){
		cnt[i]=0;
	}
	for(i=0;i<n;i++){
		cnt[x[i]=r[i]]++;
	}
	for(i=1;i<m;i++){
		cnt[i]+=cnt[i-1];
	}
	for(i=n-1;i>=0;i--){
		sa[--cnt[x[i]]]=i;
	}
	
	for(k=1;k<=n;k<<=1){
		int p=0;
		for(i=n-k;i<n;i++){
			y[p++]=i;
		}
		for(i=0;i<n;i++){
			if(sa[i]>=k){
				y[p++]=sa[i]-k;
			}
		}
		for(i=0;i<m;i++) cnt[i]=0;
		for(i=0;i<n;i++) cnt[x[y[i]]]++;
		for(i=1;i<m;i++) cnt[i]+=cnt[i-1];
		for(i=n-1;i>=0;i--) sa[--cnt[x[y[i]]]]=y[i];
		
		swap(x,y);
		p=1;
		x[sa[0]]=0;
		for(i=1;i<n;i++){
			x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?p-1:p++;
		}
		if(p>=n) break;
		m=p;
	}
}
void get_height(){
	int i,j,k=0;
	for(i=1;i<=N;i++){
		rk[sa[i]]=i;
	}
	for(i=0;i<N;i++){
		if(k) k--;
		j=sa[rk[i]-1];
		while(rec[i+k]==rec[j+k]) k++;
		height[rk[i]]=k;
	}
}
bool check(int mid){
	int a=0;
	for(int i=1;i<=N;i++){
		if(height[i]<mid){
			a=1;
		}else{
			if(++a>=K) return true;
		}
	}
	return false;
}
int solve(){
	int l=1,r=N;
	int ans=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)){
			ans=mid;
			l=mid+1;
		}else{
			r=mid-1;
		}
	}
	return ans;
}
int main(){
	scanf("%d %d",&N,&K);
	int nmax=0;
	for(int i=0;i<N;i++){
		scanf("%d",&rec[i]);
		rec[i]++;
		nmax=nmax>=rec[i]?nmax:rec[i];
	}
	rec[N]=0;
	da(rec,N+1,nmax+1);
	get_height();
	printf("%d\n",solve());
	return 0;
}
