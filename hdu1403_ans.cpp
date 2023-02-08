#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int N = 200005;    // 字符串的长度。
char s[N];               //输入字符串
int sa[N], rk[N];
int n, k;

int cnt[N],t1[N],t2[N],height[N];
void calc_sa() { 
	int m = 127;
	int i,*x=t1,*y=t2;
	for(i=0;i<m;i++)   cnt[i]=0;
	for(i=0;i<n;i++)    cnt[x[i]=s[i]]++;
	for(i=1;i<m;i++)   cnt[i]+=cnt[i-1];
	for(i=n-1;i>=0;i--)  sa[--cnt[x[i]]]=i;
	//sa[]: 从0到n-1
	for(int k=1;k<=n;k=k*2){  //利用对长度为k的排序的结果对长度为2*k的排序
		int p=0;
		//2nd
		for(i=n-k;i<n;i++)  y[p++]=i;
		for(i=0;i<n;i++)    if(sa[i]>=k) y[p++]=sa[i]-k;
		//1st
		for(i=0;i<m;i++)   cnt[i]=0;
		for(i=0;i<n;i++)   cnt[x[y[i]]]++;
		for(i=1;i<m;i++)   cnt[i]+=cnt[i-1];
		for(i=n-1;i>=0;i--)  sa[--cnt[x[y[i]]]]=y[i];
		swap(x,y);
		p=1; x[sa[0]]=0;
		for(i=1;i<n;i++)            
			x[sa[i]] = 
			y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+k]==y[sa[i]+k]?p-1:p++;
		if(p>=n) break;
		m=p;
	}
}
void getheight(int n){                  //n是字符串长度。
	int i, j, k=0;
	for(i=0 ;i<n; i++)  rk[sa[i]]=i;    //用sa[]推导rk[]
	for(i=0; i<n; i++) {
		if(k)  k--;  
		int j = sa[rk[i]-1];
		while(s[i+k]==s[j+k])  k++;
		height[rk[i]] = k;
	}
}
int main(){
	int len1, ans;
	while(scanf("%s", s)!=EOF) {      //读第1个字符串
		n = strlen(s);
		len1 = n;
		s[n] = '$';                   //用'$'分隔2个字符串。
		scanf("%s", s+n+1);           //读第2个字符串，与第1个合并。
		n = strlen(s);
		calc_sa();                    //求后缀数组sa[]
		getheight(n);                 //求height[]数组
		ans = 0;
		for(int i = 1; i < n; i++)
			//找最大的height[i]，并且它对应的sa[i-1]和sa[i]分别属于前后2个字符串。
			if(height[i]>ans && 
				((sa[i-1]<len1 &&sa[i]>=len1) || (sa[i-1]>=len1&&sa[i]<len1)))
				ans = height[i];
		printf("%d\n",ans);
	}
	return 0;
}

