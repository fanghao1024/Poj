#include <iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

int main() {
	int T,N,M;
	cin>>T;
	while(T--){
		cin>>N>>M;
		vector<int>a,b;
		queue<int> q;
		int x;
		for(int i=0;i<N;i++){
			cin>>x;
			a.push_back(x);
			b.push_back(x);
			q.push(i);
		}
		sort(b.begin(),b.end(),greater<int>());
		int ans=0;
		int w=0;
		while(!q.empty()){
			int p=q.front();
			q.pop();
			if(a[p]==b[w]){
				w++;
				ans++;
				if(p==M) break;
			}else{
				if(a[p]<b[w]){
					q.push(p);
				}
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}