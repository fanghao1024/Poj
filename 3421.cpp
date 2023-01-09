#include<stdio.h>
#include<vector>
#include<map>
#include<string.h>
using namespace std;

const int max_n=1024*1024+1;
vector<int> prime;
bool is_prime[max_n];
void get_prime(){
	for(int i=2;i<=max_n;i++){
		is_prime[i]=true;
	}
	is_prime[1]=false;
	for(int i=2;i<=max_n;i++){
		if(is_prime[i]){
			prime.push_back(i);
			for(int j=2*i;j<=max_n;j+=i){
				is_prime[j]=false;
			}
		}
	}
}
long long factorial(int x,int y){
	long long res=1;
	while(y>0){
		res*=x;
		x--;
		y--;
	}
	return res;
}
int main(){
	int X;
	get_prime();
	while(scanf("%d",&X)!=EOF){
		map<int,int> mp;
		int ans=0;
		long long res=1;
		for(int i=0;i<prime.size();i++){
			//printf("===%d\n",prime[i]);
			if(prime[i]>X){
				break;
			}
			while(X%prime[i]==0){
				mp[prime[i]]+=1;
				X/=prime[i];
				ans+=1;
			}
		}
		//printf("ans:%d\n",ans);
		int temp=ans;
		for(map<int,int>::iterator it=mp.begin();it!=mp.end();it++){
			//printf("%d\n",it->second);
			res*=factorial(temp,it->second)/factorial(it->second,it->second);
			temp-=it->second;
		}
		printf("%d %lld\n",ans,res);
		
	}
	return 0;
}
