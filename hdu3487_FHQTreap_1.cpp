#include<vector>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

int root;

struct treap {
	struct Node {
		int son[2];
		int val, key;
		int siz, tag;
	};
	
	const int n;
	std::vector<Node> tr;
	int idx, x, y, z, num;
	
	treap(int n) : n(n), tr(n) {
		idx = x = y = z = num = 0;
	}
	
	inline int newnode(int val) {
		tr[ ++ idx].key = rand();
		tr[idx].val = val;
		tr[idx].siz = 1;
		return idx;
	}
	
	inline void pull(int u) {
		tr[u].siz = tr[tr[u].son[0]].siz + tr[tr[u].son[1]].siz + 1;
	}
	
	inline void push(int u) { // 区间翻转打标记
		swap(tr[u].son[0], tr[u].son[1]);
		if(tr[u].son[0]) tr[tr[u].son[0]].tag ^= 1;
		if(tr[u].son[1]) tr[tr[u].son[1]].tag ^= 1;
		tr[u].tag ^= 0;
	}
	
	void split(int u, int cnt, int& x, int& y) {
		if (!u) {x = y = 0;return ;}
		if (tr[u].tag) push(u);
		if (tr[tr[u].son[0]].siz+1 <= cnt) {
			x = u;
			split(tr[u].son[1], cnt - tr[tr[u].son[0]].siz - 1, tr[u].son[1], y);
		} else {
			y = u;
			split(tr[u].son[0], cnt, x, tr[u].son[0]);
		}
		pull(u);
	}
	
	int merge(int u, int v) {
		if (!u || !v) return u | v;
		if (tr[u].key < tr[v].key) {
			if (tr[u].tag) push(u); // 如果有标记就要先传标记然后再合并
			tr[u].son[1] = merge(tr[u].son[1], v);
			pull(u);
			return u;
		} else {
			if (tr[v].tag) push(v);
			tr[v].son[0] = merge(u, tr[v].son[0]);
			pull(v);
			return v;
		}
	}
	
	void reverse(int l, int r) { // 区间翻转操作
		int x, y, z; 
		// 将区间分成[1, l - 1], [l, r], [r + 1, n]三个区间
		split(root, l - 1, x, y);
		split(y, r - l + 1, y, z);
		tr[y].tag ^= 1;
		root = merge(merge(x, y), z);
	}
	
	void ldr(int u) { // 输出树的中序遍历
		if (!u) return ;
		if (tr[u].tag) push(u);
		num++;
		ldr(tr[u].son[0]);
		cout << tr[u].val;
		if (num != n - 1) cout<<" ";
		ldr(tr[u].son[1]);
	}
};

signed main() {
		
	int n, m;
	while(std::cin >> n >> m, ~n && ~m) {
		root = 0;
		treap fhq(n + 1);
		for (int i = 1; i <= n; i++) {
			root = fhq.merge(root, fhq.newnode(i));
		}
		for (int i = 0; i < m; i ++) {
			std::string s;
			std::cin >> s;
			if (s[0] == 'C') {
				int a, b, c;
				std::cin >> a >> b >> c;
				int x, y, z;
				fhq.split(root, a - 1, x, y);
				fhq.split(y, b - a + 1, y, z);
				root = fhq.merge(x, z);
				fhq.split(root, c, x, z);
				root = fhq.merge(fhq.merge(x, y), z);
			} else {
				int a, b;
				std::cin >> a >> b;
				fhq.reverse(a, b);
			}
		}
		fhq.ldr(root);
		cout << "\n";
	}
	
	return 0 ^ 0;
}
