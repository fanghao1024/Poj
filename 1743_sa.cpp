#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=20005;
int recs[max_n];
int N;
struct SA{
	int rec[max_n];
	int sa[max_n],wa[max_n],wb[max_n],c[max_n];
	int height[max_n],rk[max_n];
	void get_sa(int n){
		int m=300;
		int i;
		int *x=wa,*y=wb;
		for(i=0;i<m;i++) c[i]=0;
		for(i=0;i<n;i++) c[x[i]=rec[i]]++;
		for(i=1;i<m;i++) c[i]+=c[i-1];
		for(i=n-1;i>=0;i--) sa[--c[x[i]]]=i;
		for(int k=1;k<=n;k<<=1){
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
		for(int i=1;i<=N;i++) rk[sa[i]]=i;
		int k=0;
		for(int i=0;i<N;i++){
			if(k) k--;
			int j=sa[rk[i]-1];
			while(rec[i+k]==rec[j+k]) k++;
			height[rk[i]]=k;
		}
	}
	bool check(int mid){
		int left=sa[1];
		int right=sa[1];
		for(int i=2;i<=N;i++){
			if(height[i]<mid){
				left=right=sa[i];
			}else{
				if(left>sa[i]) left=sa[i];
				if(right<sa[i]) right=sa[i];
				if(right-left>=mid) return true;
			}
			//if(mid==4) printf("%d %d %d\n",a,left,right);
			//if(a>1&&right-left>=mid) return true;
		}
		return false;
	}
	void solve(){
		int l=1,r=N;
		int ans=-1;
		while(l<=r){
			int mid=(l+r)>>1;
			//printf("~~~%d %d\n",mid,check(mid));
			if(check(mid)){
				ans=mid;
				l=mid+1;
			}else{
				r=mid-1;
			}
		}
		if(ans<4){
			printf("0\n");
		}else{
			printf("%d\n",ans+1);
		}
	}
}sa;

int main(){
	while(scanf("%d",&N)&&N){
		for(int i=0;i<N;i++){
			scanf("%d",&recs[i]);
		}
		if(N<9){
			printf("0\n");
			continue;
		}
		int minnum=300;
		N--;
		for(int i=0;i<N;i++){
			recs[i]=recs[i+1]-recs[i];
			minnum=min(minnum,recs[i]);
		}
		for(int i=0;i<N;i++){
			sa.rec[i]=recs[i]-minnum+1;
			//printf("%d ",sa.rec[i]);
		}
		//printf("\n");
		sa.rec[N]=0;
		sa.get_sa(N+1);
		sa.get_height();
		
		sa.solve();
	}	
	return 0;
}
