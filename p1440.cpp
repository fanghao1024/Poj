#include<cstdio>
#include<cstring>
#include<deque>
using namespace std;

const int max_n=2e6+10;

int num[max_n],q[max_n];
int N,M;
int main(){
	scanf("%d %d",&N,&M);
	int f=0,r=-1;
	int x;
	for(int i=1;i<=N;i++){
		scanf("%d",&num[i]);
		if(f>r) printf("0\n");
		else printf("%d\n",num[q[f]]);
		while(f<=r&&num[q[r]]>num[i]) r--;
		q[++r]=i;
		while(f<=r&&q[f]<i+1-M) f++;
	}
	return 0;
}
