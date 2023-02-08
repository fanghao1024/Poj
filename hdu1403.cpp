#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int N=200010;
char s[N];
int sa[N],ranks[N];
int t1[N],t2[N],cnt[N],height[N];
int n,k;

void da(){
	int m=127;
	int i,*x=t1,*y=t2;
	for(i=0;i<m;i++) cnt[i]=0;
	for(i=0;i<n;i++) cnt[x[i]=s[i]]++;
	for(i=1;i<m;i++) cnt[i]+=cnt[i-1];
	for(i=n-1;i>=0;i--)	sa[--cnt[x[i]]]=i;
	
	for(int k=1;k<=n;k=2*k){
		//对第2个关键字排序
		int p=0;
		for(i=n-k;i<n;i++)	y[p++]=i;
		for(i=0;i<n;i++) if(sa[i]>=k) y[p++]=sa[i]-k;

		//对第一个关键字排序
		for(i=0;i<m;i++) cnt[i]=0;
		for(i=0;i<n;i++) cnt[x[y[i]]]++;
		for(i=1;i<m;i++) cnt[i]+=cnt[i-1];
		for(i=n-1;i>=0;i--) sa[--cnt[x[y[i]]]]=y[i];
		//第一个关键字排序完毕
		swap(x,y);
		p=1;
		x[sa[0]]=0;
		for(i=1;i<n;i++){
			//x[sa[i]]=(!cmp(y,sa[i],sa[i-1],n))?p-1:p++;
			x[sa[i]] =y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+k]==y[sa[i]+k]?p-1:p++;
		}	
		if(p>=n) break;
		m=p;
	}
	
}
void calc_height(int n){
	int i,j,k=0;
	for(i=0;i<n;i++) ranks[sa[i]]=i;
	for(i=0;i<n;i++){
		if(k){
			k--;
		}
		j=sa[ranks[i]-1];
		while(s[i+k]==s[j+k]){
			k++;
		}
		height[ranks[i]]=k;
	}
}

int main(){
	int len1,ans;
	while(scanf("%s",s)!=EOF){
		n=strlen(s);
		len1=n;
		s[n]='$';
		scanf("%s",s+n+1);
		n=strlen(s);
		da();
		calc_height(n);
		ans=0;
		for(int i = 1; i < n; i++)
			//找最大的height[i]，并且它对应的sa[i-1]和sa[i]分别属于前后2个字符串。
		if(height[i]>ans && 
				((sa[i-1]<len1 &&sa[i]>=len1) || (sa[i-1]>=len1&&sa[i]<len1)))
				ans = height[i];
		printf("%d\n",ans);
		/*
		for(int i=1;i<n;i++){
			if(height[i]>ans&&((sa[i]<len1&&sa[i-1]>=len1)||(sa[i]>=len1)&&\sa[i-1]<len1)){
				ans=height[i];
			}
		}
		printf("%d\n",ans);
		 */
	}
	return 0;
}
