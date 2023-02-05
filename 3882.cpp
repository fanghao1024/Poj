#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int max_n=40010;
int sa[max_n],rk[max_n],height[max_n];
int wa[max_n],wb[max_n],cnt[max_n];
int K;
char word[max_n];

void da(char* ch,int n){
	int m=127,i,k;
	int *x=wa,*y=wb;
	for(i=0;i<=m;i++) cnt[i]=0;
	for(i=0;i<n;i++) cnt[x[i]=ch[i]]++;
	for(i=1;i<=m;i++) cnt[i]+=cnt[i-1];
	for(i=n-1;i>=0;i--) sa[--cnt[ch[i]]]=i;
	for(k=1;k<=n;k*=2){
		int p=0;
		for(i=n-k;i<n;i++) y[p++]=i;
		for(i=0;i<n;i++){
			if(sa[i]>=k){
				y[p++]=sa[i]-k;
			}
		}
		for(i=0;i<=m;i++) cnt[i]=0;
		for(i=0;i<n;i++) cnt[x[y[i]]]++;
		for(i=1;i<=m;i++) cnt[i]+=cnt[i-1];
		for(i=n-1;i>=0;i--) sa[--cnt[x[y[i]]]]=y[i];
		swap(x,y);
		p=1;x[sa[0]]=0;
		for(i=1;i<n;i++){
			x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?p-1:p++;
		}
		if(p>=n) break;
		m=p;
		
	}
}
void get_height(int n){
	int i,j,k=0;
	for(i=1;i<=n;i++){
		rk[sa[i]]=i;
	}
	for(i=0;i<n;i++){
		if(k) k--;
		j=sa[rk[i]-1];
		while(word[i+k]==word[j+k]) k++;
		height[rk[i]]=k;
	}
}
int check(int n,int mid){
	int a=1;
	int temp=sa[1];
	int ans=-1;
	for(int i=1;i<=n;i++){
		if(height[i]<mid) {
			a=1;
			temp=sa[i];
		}	
		else{
			a++;
			temp=max(temp,sa[i]);
			//temp=max(temp,sa[i-1]);
		}
		if(a>=K){
			ans=max(ans,temp);
		}
	}
	return ans;
}
void solve(int n,int& ans1,int& ans2){
	int l=1,r=n;
	int temp;
	bool flag=false;
	while(l<=r){
		int mid=(l+r)>>1;
		int temp1=check(n,mid);
		if(temp1!=-1){
			temp=mid;
			l=mid+1;
			ans2=temp1;
			flag=true;
		}else{
			r=mid-1;
		}
	}
	if(flag&&ans1<temp) ans1=temp;
}
int main(){
	while(scanf("%d",&K)&&K){
		scanf("%s",word);
		int lens=strlen(word);
		if(K==1){
			printf("%d 0\n",lens);
			continue;
		}
		da(word,lens+1);
		get_height(lens);
		int ans1=-1,ans2=-1;
		solve(lens,ans1,ans2);
		if(ans1==-1){
			printf("none\n");
		}else{
			printf("%d %d\n",ans1,ans2);
		}
	}	
	return 0;
}
