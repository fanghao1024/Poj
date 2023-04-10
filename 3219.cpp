#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,k;
int main(){
	while(scanf("%d %d",&n,&k)!=EOF){
		if((n&k)==k) printf("1\n");
		else printf("0\n");
	}
	return 0;
}
