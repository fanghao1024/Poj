#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;

const int max_n=20005;
int N,K;

struct SA{
	int rec[max_n];
	int sa[max_n],wa[max_n],wb[max_n],c[max_n];
	int height[max_n],rk[max_n];
	void get_sa(int n,int m){
		int i;
		int *x=wa,*y=wb;
		for(i=0;i<m;i++) c[i]=0;
		for(i=0;i<n;i++) c[x[i]=rec[i]]++;
		for(i=1;i<m;i++) c[i]+=c[i-1];
		for(i=n-1;i>=0;i--) sa[--c[x[i]]]=i;
		for(int k=1;k<=n;k*=2){
			int p=0;
			for(i=n-k;i<n;i++) y[p++]=i;
			for(i=0;i<n;i++) if(sa[i]>=k) y[p++]=sa[i]-k;
			for(i=0;i<m;i++) c[i]=0;
			for(i=0;i<n;i++) c[x[y[i]]]++;
			for(i=1;i<m;i++) c[i]+=c[i-1];
			for(i=n-1;i>=0;i--) sa[--c[x[y[i]]]]=y[i];
			swap(x,y);
			p=1;
			x[sa[0]]=0;
			for(i=1;i<n;i++){
				x[sa[i]]=(y[sa[i]]==y[sa[i-1]])&&(y[sa[i]+k]==y[sa[i-1]+k])?p-1:p++;
			}
			if(p>=n) break;
			m=p;
		}
	}
	void get_height(){
		for(int i=1;i<=N;i++){
			rk[sa[i]]=i;
		}
		int k=0;
		for(int i=0;i<N;i++){
			if(k) k--;
			int j=sa[rk[i]-1];
			while(rec[i+k]==rec[j+k]) k++;
			height[rk[i]]=k;
		}
	}
	bool check(int mid){
		int a=1;
		for(int i=1;i<=N;i++){
			if(height[i]<mid) a=1;
			else{
				if(++a>=K) return true;
			}
		}
		return false;
	}
	void solve(){
		int ans=-1;
		int l=1,r=N;
		while(l<=r){
			int mid=(l+r)>>1;
			if(check(mid)){
				ans=mid;
				l=mid+1;
			}else{
				r=mid-1;
			}
		}
		printf("%d\n",ans);
	}
}sa;
int main(){
	scanf("%d %d",&N,&K);
	int maxm=-1;
	for(int i=0;i<N;i++){
		scanf("%d",&sa.rec[i]);
		sa.rec[i]++;
		maxm=maxm>sa.rec[i]?maxm:sa.rec[i];
	}
	sa.rec[N]=0;
	sa.get_sa(N+1,maxm+1);
	sa.get_height();
	sa.solve();
	return 0;
}
