#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;

const int max_n=1e4+10;

int N,I,H,R;
int d[max_n];
map<pair<int,int>,bool> mp;
int main(){
	int x,y;
	scanf("%d %d %d %d",&N,&I,&H,&R);
	memset(d,0,sizeof(d));
	while(R--){
		scanf("%d %d",&x,&y);
		if(x>y) swap(x,y);
		if(mp[make_pair(x,y)]) continue;
		d[x+1]--;
		d[y]++;
		mp[make_pair(x,y)]=1;
	}
	for(int i=1;i<=N;i++){
		d[i]+=d[i-1];
	}
	x=H-d[I];
	for(int i=1;i<=N;i++){
		printf("%d\n",d[i]+x);
	}
	
	return 0;
}
