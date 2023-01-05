#include<stdio.h>
#include<vector>
#include<queue>
#include<cmath>
using namespace std;

priority_queue<double,vector<double>,less<double> > pq;

int main(){
	int N;
	int num;
	scanf("%d",&N);
	double a,b;
	for(int i=0;i<N;i++){
		scanf("%d",&num);
		pq.push(num+0.0);
	}
	while(pq.size()>1){
		a=pq.top();
		pq.pop();
		b=pq.top();
		pq.pop();
		pq.push(2*sqrt(a*b));
	}
	printf("%.3f\n",pq.top());
	return 0;
}
