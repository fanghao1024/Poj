#include <stdio.h>
#include<string.h>
#include<vector>
using namespace std;

vector<int> prime;
bool used[10010];

void get_prime(){
	memset(used,true,sizeof(used));
	for(int i=2;i<=10010;i++){
		if(used[i]){
			prime.push_back(i);
			for(int j=i*2;j<=10010;j+=i) used[j]=false;
		}
	}
}
int main() {
	get_prime();
	int num;
	while(scanf("%d",&num)){
		if(num==0) break;
		int l=0,r=0,sums=0,ans=0;
		while(true){
			while(r<prime.size()&&sums<num){
				sums+=prime[r++];
			}
			if(sums<num) break;
			if(sums==num) ans++;
			sums-=prime[l++];
			if(prime[l]>num) break;
		}
		printf("%d\n",ans);
		
	}
	return 0;
}