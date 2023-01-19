#include<stdio.h>
#include<set>
using namespace std;

set<int>a;
int main(){
	int N,M;
	while(scanf("%d %d",&N,&M)!=EOF){
		a.clear();
		int x;
		for(int i=0;i<N;i++){
			scanf("%d",&x);
			a.insert(x);
		}
		for(int i=0;i<M;i++){
			scanf("%d",&x);
			a.insert(x);
		}
		for(set<int>::iterator it=a.begin();it!=a.end();it++){
			if(it!=a.begin()) printf(" ");
			printf("%d",*it);
		}
		printf("\n");
	}
	return 0;
}
