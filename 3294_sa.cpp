#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=105;
const int max_l=100500;
char s[max_l];
int r[max_l];
int N,n,len;
int belong[max_l];
bool vis[max_n];

struct SA{
	int sa[max_l],wa[max_l],wb[max_l],c[max_l];
	int height[max_l],rk[max_l];
	void get_sa(int n,int m){
		int i;
		int *x=wa,*y=wb;
		for(i=0;i<m;i++) c[i]=0;
		for(i=0;i<n;i++) c[x[i]=r[i]]++;
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
			x[sa[0]]=0;
			p=1;
			for(i=1;i<n;i++) x[sa[i]]=(y[sa[i]]==y[sa[i-1]])&&(y[sa[i]+k]==y[sa[i-1]+k])?p-1:p++;
			if(p>=n) break;
			m=p;
		}
	}
	void get_height(){
		int i,j,k=0;
		for(i=1;i<=n;i++) rk[sa[i]]=i;
		for(i=0;i<n;i++){
			if(k) k--;
			j=sa[rk[i]-1];
			while(r[i+k]==r[j+k]) k++;
			height[rk[i]]=k;
		}
	}
	bool check(int mid,bool flag){
		int i=2;
		while(1){
			memset(vis,0,sizeof(vis));
			while(i<=n&&height[i]<mid) i++;
			if(i>n) break;
			vis[belong[sa[i-1]]]=1;
			while(i<=n&&height[i]>=mid){
				vis[belong[sa[i]]]=1;
				i++;
			}
			int cnt=0;
			for(int j=1;j<=N;j++){
				if(vis[j]) cnt++;
			}
			if(cnt>N/2){
				if(!flag) return true;
				else{
					for(int k=sa[i-1],t=0;t<mid;k++,t++){
						printf("%c",s[k]);
					}
					printf("\n");
				}
			}
		}
		return false;
	}
	void work(){
		int l=1,r=len;
		int ans=-1;
		while(l<=r){
			int mid=(l+r)>>1;
			if(check(mid,0)){
				ans=mid;
				l=mid+1;
			}else{
				r=mid-1;
			}
		}
		if(ans==-1){
			printf("?\n");
		}else{
			check(ans,1);
		}
	}
}sa;
int main(){
	while(scanf("%d",&N)&&N){
		n=0;
		for(int i=1;i<=N;i++){
			scanf("%s",s+n);
			if(i==1)
				len=strlen(s);
			for(;s[n]!='\0';n++){
				r[n]=s[n]-'a'+1;
				belong[n]=i;
			}
			s[n]='#';
			r[n]=i+100;
			n++;
		}
		n--;
		r[n]=0;
		sa.get_sa(n+1,220);
		sa.get_height();
		sa.work();
		printf("\n");
	}		
	return 0;
}
