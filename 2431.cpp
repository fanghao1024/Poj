#include<stdio.h>
#include<queue>
#include<algorithm>
using namespace std;

struct Info{
	int dis;
	int fuel;
}info[10010];
bool cmp(const Info& a,const Info& b){
	return a.dis>b.dis;
}
priority_queue<int> q;
int main(){
	int N,L,P;
	scanf("%d",&N);
	int i;
	for(i=0;i<N;i++){
		scanf("%d %d",&info[i].dis,&info[i].fuel);
	}
	info[N].dis=0;
	info[N].fuel=0;
	scanf("%d %d",&L,&P);
	
	sort(info,info+N+1,cmp);
	int now_fuel=P;
	bool flag=true;
	int ans=0;
	for(i=0;i<=N;i++){
		if(now_fuel>=L-info[i].dis){
			q.push(info[i].fuel);
		}else{
			if(q.empty()){
				flag=false;
				printf("-1\n");
				break;
			}else{
				now_fuel+=q.top();
				ans++;
				q.pop();
				i--;
			}
		}
	}
	if(flag){
		printf("%d\n",ans);
	}
	
	return 0;
}
