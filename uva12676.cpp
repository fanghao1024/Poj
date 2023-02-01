#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;
int N;
const int max_n=55;
typedef long long ll;

vector<ll> rec[max_n];
int main() {
	while(cin>>N){
		for(int i=0;i<=N;i++){
			rec[i].clear();
		}
		ll x;
		ll ma=-1;
		for(int i=0;i<N;i++){
			cin>>x;
			rec[x].push_back(0LL);
			ma=max(ma,x);
		}
		ll temp=1;
		for(int i=ma;i>0;i--){
			for(int j=0;j<rec[i].size();j++){
				if(!rec[i][j]){
					rec[i][j]=temp;
				}
			}
			sort(rec[i].begin(),rec[i].end());
			for(int j=0;j<rec[i].size();j+=2){
				rec[i-1].push_back(rec[i][j]+rec[i][j+1]);
			}
			temp=*(rec[i].end()-1);
		}
		cout<<rec[0][0]<<endl;
	}
	return 0;
}