#include<cstdio>
#include<algorithm>
using namespace std;

const int max_n=1024;
int num[max_n];
int N,len,d[max_n];
int main(){
	scanf("%d",&N);
	for(int i=0;i<N;i++){
		scanf("%d",&num[i]);
	}
	len=1;
	d[1]=num[0];
	for(int i=1;i<N;i++){
		if(num[i]==d[len]) continue;
		if(num[i]>d[len]) d[++len]=num[i];
		else{
			*lower_bound(d+1,d+1+len,num[i])=num[i];
 		}
	}
	printf("%d\n",len);
	return 0;
}
