#include <iostream>
#include<queue>
#include<vector>
#include<functional>
using namespace std;
priority_queue<int,vector<int>,greater<int> >pq;
int main() {
	int n,k;
	while(scanf("%d %d",&n,&k)!=EOF){
		while(pq.size()){
			pq.pop();
		}
		char ope;
		int x;
		while(n--){
			scanf(" %c",&ope);
			switch (ope) {
				case 'I':
					scanf("%d",&x);
					if(pq.size()<k){
						pq.push(x);
					}else{
						if(x>pq.top()){
							pq.pop();
							pq.push(x);
						}
					}
					break;
				case 'Q':
					printf("%d\n",pq.top());
					break;
			}
		}
	}
	return 0;
}