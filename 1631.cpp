#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
int port[40010];
int record[40010];

int main(){
	int N,p;
	
	scanf("%d",&N);
	while(N--){
		scanf("%d",&p);
		for(int i=0;i<p;i++){
			scanf("%d",&port[i]);
		}
		//fill(record,record+p,0x3fffffff);
		memset(record,0x3fffffff,sizeof(record));
		for(int i=0;i<p;i++){
			*lower_bound(record,record+p,port[i])=port[i];
		}
		printf("%d\n",lower_bound(record,record+p,0x3fffffff)-record);
	}
	return 0;
}
