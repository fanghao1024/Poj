#include<stdio.h>
#include<queue>
#include<vector>
using namespace std;
const int max_n=30005;
int A[max_n];
int U[max_n];
priority_queue<int,vector<int>,greater<int> > KMax; //最小值的优先队列，堆顶保存剩下元素中最小的元素，随时加入下面的队列
priority_queue<int,vector<int>,less<int> > OtherMin;//最小的K个数根据最大堆来保存，堆顶的是这K个元素元素中最大的元素，也是所有元素中第K小的数

void run(int i){
	
}
int main(){
	int N,M;
	scanf("%d %d",&M,&N);
	for(int i=1;i<=M;i++) scanf("%d",A+i);
	for(int i=1;i<=N;i++) scanf("%d",U+i);
	
	int index=1;
	
	for(int i=1;i<=N;i++){
		while(KMax.size()+OtherMin.size()<U[i]&&index<=M){
			while(!KMax.empty()&&OtherMin.size()<i){
				OtherMin.push(KMax.top());
				KMax.pop();
			}
			OtherMin.push(A[index++]);
			while(OtherMin.size()>i){
				KMax.push(OtherMin.top());
				OtherMin.pop();
			}
		}
		while(OtherMin.size()<i){
			while(!KMax.empty()&&OtherMin.size()<i){
				OtherMin.push(KMax.top());
				KMax.pop();
			}
		}
		printf("%d\n",OtherMin.top());
	}
	
	return 0;
}
