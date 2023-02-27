#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;

int main(){
	int n,ops,x;
	scanf("%d",&n);
	priority_queue<int,vector<int>,greater<int> > q;
	while(n--){
		scanf("%d",&ops);
		if(ops==1){
			scanf("%d",&x);
			q.push(x);
		}else if(ops==2){
			printf("%d\n",q.top());
		}else{
			q.pop();
		}
	}
	return 0;
}
