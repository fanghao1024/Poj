#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef unsigned long long ull;
const int max_n=1e4+10;
char ch[max_n];
ull a[max_n];
int N;
ull BKDRHash(char* s){
	ull P=131,H=0;
	for(int i=0;i<strlen(s);i++){
		H=H*P+s[i]-'a'+1;
	}
	return H;
}
int main(){
	scanf("%d",&N);
	for(int i=0;i<N;i++){
		scanf("%s",ch);
		a[i]=BKDRHash(ch);
	}
	sort(a,a+N);
	int ans=0;
	for(int i=0;i<N;i++){
		if(a[i]!=a[i+1]) ans++;
	}
	printf("%d\n",ans);
	return 0;
}

