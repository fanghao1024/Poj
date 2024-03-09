#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef unsigned long long ull;
const int max_n=5e5+10;
const int P=131;

char s[max_n],t[max_n];
ull f[max_n],p[max_n],g[max_n];
int N;
ull ans;
void bin_search(int x){
	int L=0,R=min(x,N-x);
	int res;
	while(L<=R){
		int mid=(L+R)>>1;
		if((ull)(f[x]-f[x-mid]*p[mid])==(ull)(g[x+1]-g[x+1+mid]*p[mid])) res=mid,L=mid+1;
		else R=mid-1;
	}
	ans+=res;
}
int main(){
	scanf("%d",&N);
	scanf("%s",s+1);
	for(int i=1;i<=N;i++) t[i]=s[i]=='0'?'1':'0';
	p[0]=1;
	for(int i=1;i<=N;i++) p[i]=p[i-1]*P;
	for(int i=1;i<=N;i++) f[i]=f[i-1]*P+s[i]-'0'+1;
	for(int i=N;i>-1;i--) g[i]=g[i+1]*P+t[i]-'0'+1;
	ans=0;
	for(int i=1;i<=N;i++) bin_search(i);
	printf("%llu\n",ans);
	return 0;
}
