#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
using namespace std;

const int prime0=20101,prime1=1097;

bool hashTable[prime0+prime1][prime1];

int n;
struct Node{
	int a,b;
	int g,h;
	Node(){};
	Node(int _a,int _b,int _g){
		a=_a;b=_b;g=_g;
		int x=0;
		int temp=a;
		while(temp<n){
			x++;
			temp<<=1;
		}
		h=temp;
	}
	Node(int _a,int _b,int _g,int _h){
		a=_a;b=_b;g=_g;h=_h;
	}
	bool operator<(const Node& m) const{
		if(g+h==m.g+m.h) return h>m.h;
		else return g+h>m.g+m.h;
	}
};
Node now;
priority_queue<Node> q;
int ans,n2;
int gcd(int a,int b){
	if(b==0) return a;
	return gcd(b,a%b);
}
bool add(int a,int b){
	if(a==n||b==n) return true;
	if(a<b) swap(a,b);
	if(a>2*n) return false;
	if(a>n&&b==0) return false;
	if(a==b) return false;
	if(n%gcd(a,b)) return false; 
	if(a>=n2||b>=prime1) return false;
	if(!hashTable[a][b]){
		q.push(Node(a,b,now.g+1));
		hashTable[a][b]=1;
	}
	return false;
}
bool add_now(int a,int b) {
	if (a == n || b == n)
		return true;
	if (a < b) {
		int temp = a;
		a = b;
		b = temp;
	}
	if (a > 2 * n) return false;
	if (a > n && b == 0) return false;
	if (a == b) return false;
	if (n % gcd (a, b)) return false;
	if (a >= n2 || b >= prime1)
		return false;
	if (!hashTable[a][b]) {
		hashTable[a][b] = true;
		int h = 0, tx = a;
		while (tx < n) h ++, tx <<= 1;
		q. push (Node(a, b, now.g + 1, h));
	}
	return false;
}
void astar(){
	n2=n+prime1;
	while(!q.empty()) q.pop();
	memset(hashTable,0,sizeof(hashTable));
	q.push(Node(1,0,0,0));
	hashTable[1][0]=1;
	while(!q.empty()){
		now=q.top();
		q.pop();
		//if(hashTable[now.a][now.b]) continue;
		
		int a=now.a,b=now.b;
		//if(add(a+a,b)||add(a+b,b)||add(b+b,b)||add(a,a+b)||add(a,b+b)||add(a,a+a)||add(a-b,a)||add(a,a-b)){
		//	ans=now.g+1;
		//	break;
		//}
		if(add_now(a+a, b) || add_now(a+b, b) || add_now(b+b, b) || add_now(a, a+a) ||
			add_now(a, a+b) || add_now(a, b+b) || add_now(a, a-b) || add_now(a-b, a)) {
			ans = now.g + 1;
			break;
		}
	}
}
int main(){
	scanf("%d",&n);
	astar();
	printf("%d\n",ans);
	return 0;
}
