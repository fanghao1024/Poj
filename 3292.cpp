#include<stdio.h>
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

bool is_prime[250005];
int hemi_prime[250005];
vector<int> prime;
bool is_heimi(int x){
	int numx=4*x+1;
	int res=0;
	for(int i=0;i<prime.size();i++){
		//cout<<prime[i]<<endl;
		//cout<<prime[i]<<"---"<<sqrt(numx)<<endl;
		//if(prime[i]>sqrt(numx)) break;
		if(numx%prime[i]==0){
			int a=numx/prime[i];
			if(is_prime[(a-1)/4]){
				return true;
			}else{
				return false;
			}
		}
		
	}
}
void get_prime(){
	for(int i=0;i<=250000;i++){
		is_prime[i]=true;
	}
	is_prime[0]=false;
	for(int i=1;i<=250000;i++){
		if(is_prime[i]){
			prime.push_back(4*i+1);
			for(int j=1;4*i*j+i+j<=250000;j++){
				is_prime[4*i*j+i+j]=false;
			}
		}
	}
	for(int i=0;i<=250000;i++){
		hemi_prime[i]=0;
	}
	for(int i=1;i<=250000;i++){
		if(is_prime[i]){
			hemi_prime[i]=hemi_prime[i-1];
			continue;
		}
		if(is_heimi(i)){
			hemi_prime[i]=hemi_prime[i-1]+1;
		}else{
			hemi_prime[i]=hemi_prime[i-1];
		}
	}
}
int main(){
	int num;
	get_prime();
	
	while(1){
		//scanf("%d\n",&num);
		cin>>num;
		if(num==0) break;
		//printf("%d %d\n",num,hemi_prime[(num-1)/4]);
		cout<<num<<" "<<hemi_prime[(num-1)/4]<<endl;
	}
	return 0;
}
