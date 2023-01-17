#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

const int B=1000;
const int max_n=100010;
const int max_m=5010;
int A[max_n];
int num[max_n];
int I[max_m],J[max_m],K[max_m];
vector<int> bucket[max_n/B];

int N,M;
int main(){
	scanf("%d %d",&N,&M);
	for(int i=0;i<N;i++) scanf("%d",&A[i]);
	for(int i=0;i<M;i++) scanf("%d %d %d",&I[i],&J[i],&K[i]);
	for(int i=0;i<N;i++){
		bucket[i/B].push_back(A[i]);
		num[i]=A[i];
	}
	sort(num,num+N);
	for(int i=0;i<N/B;i++) sort(bucket[i].begin(),bucket[i].end());
	for(int i=0;i<M;i++){
		int l=I[i]-1,r=J[i],k=K[i];
		int lb=-1,ub=N-1;
		while(ub-lb>1){
			int mid=(ub+lb)>>1;
			int x=num[mid];
			
			int count=0;
			int tl=l,tr=r;
			
			while(tl<tr&&(tl%B!=0)){
				if(A[tl++]<=x)
					count++;
			}
			while(tl<tr&&(tr%B!=0)){
				if(A[--tr]<=x)
					count++;
			}
			while(tl<tr){
				int b=tl/B;
				count+=upper_bound(bucket[b].begin(),bucket[b].end(),x)-bucket[b].begin();
				tl+=B;
			}
			if(count<k){
				lb=mid;
			}else{
				ub=mid;
			}
		}
		printf("%d\n",num[ub]);
	}
	return 0;
}
