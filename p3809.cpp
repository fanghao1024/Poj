#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=1e6+10;
int sa[max_n],a[max_n],b[max_n],cnt[max_n];
char s[max_n];
void cal_sa(char* ch,int n){
	int m=128;
	int *x=a,*y=b;
	for(int i=0;i<m;i++) cnt[i]=0;
	for(int i=0;i<n;i++) cnt[x[i]=ch[i]]++;
	for(int i=1;i<m;i++) cnt[i]+=cnt[i-1];
	for(int i=n-1;i>=0;i--) sa[--cnt[x[i]]]=i;
	for(int k=1;k<=n;k<<=1){
		int p=0;
		for(int i=n-k;i<n;i++) y[p++]=i;
		for(int i=0;i<n;i++) if(sa[i]>=k) y[p++]=sa[i]-k;
		
		for(int i=0;i<m;i++) cnt[i]=0;
		for(int i=0;i<n;i++) cnt[x[y[i]]]++;
		for(int i=0;i<m;i++) cnt[i]+=cnt[i-1];
		for(int i=n-1;i>=0;i--) sa[--cnt[x[y[i]]]]=y[i];
		swap(x,y);
		p=1;
		x[sa[0]]=0;
		for(int i=1;i<n;i++){
			x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?p-1:p++;
		}
		if(p>=n) break;
		m=p;
	}
	
}
int main(){
	scanf("%s",s);
	int n=strlen(s);
	cal_sa(s,n+1);
	for(int i=1;i<=n;i++){
		if(i-1) printf(" ");
		printf("%d",sa[i]+1);
	}
	printf("\n");
	return 0;
}
