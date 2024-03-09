#include <iostream>
#include <queue>
using namespace std;
const int prime0 = 20101, prime1 = 1097;
int n, n2, ans;
bool hashTable[prime0 + prime1][prime1];
struct node{
	int a, b, g, h;
	bool operator< (const node &a) const {
		return g + h == a . g + a . h ? h > a . h : g + h > a . g + a . h;
	}
	node(){};
	node(int _a,int _b,int _g,int _h){a=_a;b=_b;g=_g;h=_h;}
};
node now;
priority_queue<node> q;
int gcd (int a, int b) { return b ? gcd (b, a % b) : a; }
bool add_node(int a,int b) {
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
		q. push (node(a, b, now.g + 1, h));
	}
	return false;
}
int Astar() {
	n2 = n + prime1;
	q. push(node(1, 0, 0, 0));
	hashTable[1][0] = true;
	while(!q.empty()) {
		now = q.top();
		int a = now.a, b = now.b;
		q.pop();
		if(add_node(a+a, b) || add_node(a+b, b) || add_node(b+b, b) || add_node(a, a+a) ||
			add_node(a, a+b) || add_node(a, b+b) || add_node(a, a-b) || add_node(a-b, a)) {
			ans = now.g + 1;
			break;
		}
	}
	return 0;
}
int main() {
	cin >> n;
	Astar();
	cout << ans;
	return 0;
}
