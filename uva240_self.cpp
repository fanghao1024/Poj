#include <iostream>
#include<stdio.h>
#include<queue>
#include<string.h>
#include<string>
#include<algorithm>
using namespace std;
const int max_n=100;
int R,N;
struct Node{
	int freq,val,id;//频率，优先级，id号
	Node(){};
	Node(int x,int y,int z){
		this->freq=x;
		this->val=y;
		this->id=z;
	}
	bool operator<(const Node& t) const{
		if(this->freq==t.freq){
			return this->val>t.val;
		}else{
			return this->freq>t.freq;
		}
	}
};
int freq[max_n],par[max_n],route[max_n];
int main() {
	int case_num=1;
	while(cin>>R && R){
		cin>>N;
		int total=0;
		memset(freq,0,sizeof(freq));
		for(int i=0;i<N;i++){
			cin>>freq[i];
			total+=freq[i];
		}
		int x;
		priority_queue<Node> pq;
		
		int n=N;
		while((n-R)%(R-1)!=0){
			n++;
		}
		for(int i=0;i<n;i++){
			pq.push(Node(freq[i],i,i));
		}
		int C=n;
		int rec=0;
		while(pq.size()!=1){
			int sum=0;
			int minV=n;
			for(int i=0;i<R;i++){
				Node node=pq.top();pq.pop();
				//cout<<i<<" "<<node.freq<<" "<<node.val<<" "<<node.id<<endl;
				sum+=node.freq;
				minV=minV<node.val?minV:node.val;
				par[node.id]=C;
				route[node.id]=i;
			}
			rec+=sum;
			pq.push(Node(sum,minV,C));
			C++;
		}
		C--;

		printf("Set %d; average length %0.2f\n",case_num++,1.0*rec/total);
		for(int i=0;i<N;i++){
			string s;
			int cur=i;
			while(cur!=C){
				//cout<<cur<<" "<<par[cur]<<"####"<<route[cur]<<endl;
				s.push_back('0'+route[cur]);
				cur=par[cur];
			}
			reverse(s.begin(), s.end());
			cout<<"    "<<char('A'+i)<<": "<<s<<endl;
		}
		cout<<endl;
	}
	return 0;
}