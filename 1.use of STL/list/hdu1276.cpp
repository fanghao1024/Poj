#include<iostream>
#include<list>
using namespace std;

int main(){
	int N,n;
	scanf("%d",&N);
	while(N--){
		scanf("%d",&n);
		list<int> a;
		for(int i=1;i<=n;i++)
			a.push_back(i);
		int k=2;
		while(a.size()>3){
			int cnt=1;
			for(list<int>::iterator it=a.begin();it!=a.end();){
				if(cnt++%k==0){
					it=a.erase(it);
				}else{
					it++;
				}
			}
			k=(k==2)?3:2;
		}
		for(list<int>::iterator it=a.begin();it!=a.end();it++){
			if(it!=a.begin()) printf(" ");
			printf("%d",*it);
		}
		printf("\n");
	}
	return 0;
}
