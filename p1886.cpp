#include<cstdio>
#include<queue>
#include<deque>
#include<cstring>
using namespace std;

const int max_n=1e6+10;
int num[max_n];
int N,K;
int Ma[max_n],Mi[max_n];
int main(){
	scanf("%d %d",&N,&K);
	for(int i=0;i<N;i++) scanf("%d",num+i);
	deque<int> dma,dmi;
	for(int i=0;i<N;i++){
		while(!dma.empty()&&num[dma.back()]<num[i]) dma.pop_back();
		while(!dmi.empty()&&num[dmi.back()]>num[i]) dmi.pop_back();
		dma.push_back(i);
		dmi.push_back(i);
		while(!dma.empty()&&dma.front()<i-K+1) dma.pop_front();
		while(!dmi.empty()&&dmi.front()<i-K+1) dmi.pop_front();
		Ma[i]=num[dma.front()];
		Mi[i]=num[dmi.front()];
	}
	int count=0;
	for(int i=K-1;i<N;i++){
		if(count++) printf(" ");
		printf("%d",Mi[i]);
	}
	printf("\n");
	count=0;
	for(int i=K-1;i<N;i++){
		if(count++) printf(" ");
		printf("%d",Ma[i]);
	}
	printf("\n");
	return 0;
}
