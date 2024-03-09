#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef unsigned long long ull;
const int max_n=1e6+10;
const int PP=131;

char s[max_n];
ull f[max_n],p[max_n];
int N;
ull get_hash(int L,int R){
	return f[R]-f[L-1]*p[R-L+1];
}
int main(){
	scanf("%d",&N);
	scanf("%s",s+1);
	p[0]=1;
	for(int i=1;i<=N;i++) p[i]=p[i-1]*PP;
	for(int i=1;i<=N;i++) f[i]=f[i-1]*PP+s[i]-'a'+1;
	for(int i=1;i<=N;i++){
		bool flag=true;
		ull last=get_hash(1,i);
		for(int j=1;(j+1)*i<=N;j++){
			if(get_hash(j*i+1,(j+1)*i)!=last){
				flag=false;
				break;
			}
		}
		if(N%i!=0){
			int len=N%i;
			if(get_hash(1,len)!=get_hash(N-len+1,N)) flag=false;
		}
		if(flag){printf("%d\n",i);break;}
	}
	return 0;
}


