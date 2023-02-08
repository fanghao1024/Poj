#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int max_n=40005;
int M,N;
char ch[max_n];
int s[max_n];
struct SA{
	int sa[max_n],c[max_n],wa[max_n],wb[max_n];
	int height[max_n],rk[max_n];
	void get_sa(int n,int m){
		int i=0;
		int *x=wa,*y=wb;
		for(i=0;i<m;i++) c[i]=0;
		for(i=0;i<n;i++) c[x[i]=s[i]]++;
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
		for(int i=1;i<=N;i++) rk[sa[i]]=i;
		int k=0;
		for(int i=0;i<N;i++){
			if(k) k--;
			int j=sa[rk[i]-1];
			while(s[i+k]==s[j+k]) k++;
			height[rk[i]]=k;
		}
	}
	int check(int mid){
		int a=1;
		int ans=-1;
		int temp=sa[1];
		for(int i=1;i<=N;i++){
			if(height[i]<mid){
				a=1;
				temp=sa[i];
			}else{
				a++;
				temp=max(temp,sa[i]);
			}
			if(a>=M){
				ans=max(ans,temp);
			}
		}
		return ans;
	}
	void solve(){
		int l=1,r=N;
		int ans1=-1;
		int ans2=-1;
		while(l<=r){
			int mid=(l+r)>>1;
			int tar=check(mid);
			if(tar!=-1){
				ans1=mid;
				ans2=tar;
				l=mid+1;
			}else{
				r=mid-1;
			}
		}
		if(ans1==-1){
			printf("none\n");
		}else{
			printf("%d %d\n",ans1,ans2);
		}
	}
}sa;
int main(){
	while(scanf("%d",&M)&&M){
		scanf("%s",ch);
		if(M==1){
			printf("%d 0\n",strlen(ch));
			continue;
		}
		N=strlen(ch);
		for(int i=0;i<N;i++){
			s[i]=ch[i]-'a'+1;
		}
		s[N]=0;
		sa.get_sa(N+1,27);
		sa.get_height();
		sa.solve();
	}
	return 0;
}
