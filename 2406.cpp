#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=1000010;
char s[max_n];
int Next[max_n];
void getNext(){
	Next[0]=-1;
	int k=-1,j=0;
	int len=strlen(s);
	while(j<len){
		if(k==-1||s[j]==s[k]) Next[++j]=++k;
		else k=Next[k];
	}
}
int main(){
	while(scanf("%s",s)!=EOF){
		if(s[0]=='.') break;
		getNext();
		int N=strlen(s);
		int ans=1;
		if(N%(N-Next[N])==0) ans=N/(N-Next[N]);
		printf("%d\n",ans);
	}
	return 0;
}
