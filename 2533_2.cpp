#include<cstdio>
#include<algorithm>
using namespace std;

const int max_n=1024;
int rec[max_n];
int d[max_n],len;
int N;

int main(){
	scanf("%d",&N);
	for(int i=0;i<N;i++) scanf("%d",&rec[i]);
	d[1]=rec[0];
	len=1;
	for(int i=1;i<N;i++){
		if(rec[i]==d[len]) continue;
		if(rec[i]>d[len]) d[++len]=rec[i];
		else{
			*lower_bound(d+1,d+1+len,rec[i])=rec[i];
		}
	}
	printf("%d\n",len);
	return 0;
}
