#include<stdio.h>
#include<algorithm>
using namespace std;
struct Cow{
	int T;
	int D;
	double value;
}cow[100010];
bool cmp(const Cow &a,const Cow &b){
	return a.value>b.value;
}

int main(){
	int N;
	scanf("%d",&N);
	for(int i=0;i<N;i++){
		scanf("%d %d",&cow[i].T,&cow[i].D);
		cow[i].value=(cow[i].D+0.0)/cow[i].T;
	}
	sort(cow,cow+N,cmp);
	int ans=0;
	int time=cow[0].T;
	for(int i=1;i<N;i++){
		ans+=2*time*cow[i].D;
		time+=cow[i].T;
	}
	printf("%d\n",ans);
	return 0;
}
