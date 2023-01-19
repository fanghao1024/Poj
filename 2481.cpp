#include<stdio.h>
#include<map>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

map<int,int> mp;

int main(){
	int ops;
	int K,P;
	while(scanf("%d",&ops)){
		if(ops==0) break;
		switch (ops) {
		case 1:
			scanf("%d %d",&K,&P);
			mp[P]=K;
			break;
		case 2:
			if(mp.empty()){
				printf("0\n");
			}else{
				map<int,int>::iterator it=mp.end();
				it--;
				printf("%d\n",it->second);
				mp.erase(it);
			}
			break;
		case 3:
			if(mp.empty()){
				printf("0\n");
			}else{
				printf("%d\n",mp.begin()->second);
				mp.erase(mp.begin());
			}
			break;
		}
	}
	return 0;
}
