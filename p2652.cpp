#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int max_n=1e5+10;
const int inf=0x3f3f3f3f;

struct Node{
	int a,b;
}a[max_n],b[max_n];
bool cmp(const Node& m,const Node& n){
	if(m.a!=n.a) return m.a<n.a;
	else return m.b<n.b;
}
int main(){
	int n,x,y;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d %d",&a[i].a,&a[i].b);
	sort(a+1,a+1+n,cmp);
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(a[i].a==a[i-1].a&&a[i].b==a[i-1].b) continue;
		b[++cnt]=a[i];
	}
	int ans=1;
	int start;
	b[0].a=-1;
	queue<int> q;
	for(int i=1;i<=cnt;i++){
	
		if(b[i].a!=b[i-1].a){
			start=i;
		}else{
			while(b[start].b<b[i].b-n+1) start++;
			ans=max(i-start+1,ans);
		}
			/*
		if(b[i].a!=b[i-1].a){
			while(!q.empty()) q.pop();
		}
		while(!q.empty()&&b[i].b-q.front()>n-1) q.pop();
		q.push(b[i].b);
		ans=max(ans,(int)q.size()); */
	}
	printf("%d\n",n-ans);
	return 0;
}
