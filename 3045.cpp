#include<stdio.h>
#include<algorithm>
using namespace std;

typedef long long ll;
int N;
const int INF=0x3fffffff;
struct Cow{
	int w;
	int s;
}cow[50010];
int weight[50010];
bool cmp(const Cow& a,const Cow& b){
	return a.s+a.w>b.s+b.w;
}
int main(){
	scanf("%d\n",&N);
	for(int i=0;i<N;i++){
		scanf("%d %d",&cow[i].w,&cow[i].s);
	}
	sort(cow,cow+N,cmp);
	int ans=-INF;
	weight[0]=0;
	for(int i=1;i<N;i++){
		weight[i]=weight[i-1]+cow[i].w;
	}
	for(int i=0;i<N;i++){
		//printf("%d\n",cow[i].w);
		ans=ans>(weight[N-1]-weight[i])-cow[i].s?ans:(weight[N-1]-weight[i])-cow[i].s;
	}
	printf("%d\n",ans);
	return 0;
}
