#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
const int max_n=2e7+10;
char a[max_n],b[max_n];
ll NExtd[max_n],Extd[max_n];
void qNExtd(char *c)
{
	int len = strlen(c);
	int p = 0, k = 1, l; //我们会在后面先逐位比较出 NExtd[1] 的值，这里先设 k 为 1
	//如果 k = 0，p 就会锁定在 |c| 不会被更改，无法达成算法优化的效果啦
	NExtd[0] = len; //以 c[0] 开始的后缀就是 c 本身，最长公共前缀自然为 |c|
	while(p + 1 < len && c[p] == c[p + 1]) p++;
	NExtd[1] = p; //先逐位比较出 NExtd[1] 的值
	for(int i = 2; i < len; i++)
	{
		p = k + NExtd[k] - 1; //定义
		l = NExtd[i - k]; //定义
		if(i + l <= p) NExtd[i] = l; //如果灰方框小于初始的绿方框,直接确定 NExtd[i] 的值
		else
		{
			int j = max(0, p - i + 1);
			while(i + j < len && c[i + j] == c[j]) j++; //否则进行逐位比较
			NExtd[i] = j;
			k = i; //此时的 x + NExtd[x] - 1 一定刷新了最大值，于是我们要重新赋值 k
		}
	}
}
void getNExtd(char* s){
	int k=1;
	int len=strlen(s);
	NExtd[0]=len;
	int j=0;
	while(j+1<len&&s[j]==s[j+1]) j++;
	NExtd[1]=j;
	for(int i=2;i<len;i++){
		int l=NExtd[i-k];
		int p=k+NExtd[k]-1;
		if(i+l-1<p) NExtd[i]=l;
		else{
			j=max(0,p-i+1);
			while(i+j<len&&s[i+j]==s[j]) j++;
			NExtd[i]=j;
			k=i;
		}
	}
	
}
void getExtd(char* s,char* t){
	int k=0;
	int lens=strlen(s),lent=strlen(t);
	int j=0;
	while(j<lens&&j<lent&&s[j]==t[j]) j++;
	Extd[0]=j;
	for(int i=1;i<lens;i++){
		int p=k+Extd[k]-1;
		int l=NExtd[i-k];
		if(i+l-1<p) Extd[i]=l;
		else{
			j=max(0,p-i+1);
			while(i+j<lens&&j<lent&&s[i+j]==t[j]) j++;
			Extd[i]=j;
			k=i;
		}
	}
}
void exkmp(char *a, char *b)
{
	int la = strlen(a), lb = strlen(b);
	int p = 0, k = 0, l;
	while(p < la && p < lb && a[p] == b[p]) p++; //先算出初值用于递推
	Extd[0] = p;
	for(int i = 1; i < la; i++) //下面都是一样的逻辑啦
	{
		p = k + Extd[k] - 1;
		l = NExtd[i - k];
		if(i + l <= p) Extd[i] = l;
		else
		{
			int j = max(0, p - i + 1);
			while(i + j < la && j < lb && a[i + j] == b[j]) j++;
			Extd[i] = j;
			k = i;
		}
	}
}
int main(){
	scanf("%s %s",a,b);
	getNExtd(b);
	//qNExtd(b);
	getExtd(a,b);
	//exkmp(a,b);
	ll ans=0;
	for(int i=0;i<strlen(b);i++) ans^=(i+1)*(NExtd[i]+1);
	printf("%lld\n",ans);
	ans=0;
	for(int i=0;i<strlen(a);i++) ans^=(i+1)*(Extd[i]+1);
	printf("%lld\n",ans);
	return 0;
}
