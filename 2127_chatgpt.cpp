#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 505;
int n, m;
int a[MAXN], b[MAXN], f[MAXN][MAXN], dp[MAXN];

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	
	cin >> m;
	for (int i = 1; i <= m; i++) {
		cin >> b[i];
	}
	
	for (int i = 1; i <= n; i++) {
		int len = 0;
		for (int j = 1; j <= m; j++) {
			f[i][j] = f[i - 1][j];
			if (a[i] == b[j] && f[i][j] < len + 1) {
				f[i][j] = len + 1;
			}
			if (b[j] < a[i] && len < f[i - 1][j]) {
				len = f[i - 1][j];
			}
		}
	}
	
	int k = 0;
	for (int j = 1; j <= m; j++) {
		if (f[n][j] > f[n][k]) {
			k = j;
		}
	}
	
	cout << f[n][k] << endl;
	
	vector<int> ans;
	for (int i = n; i >= 1; i--) {
		if (a[i] == b[k] && f[i][k] == f[i - 1][k] + 1) {
			ans.push_back(a[i]);
			k--;
		}
	}
	
	for (int j = ans.size() - 1; j >= 0; j--) {
		cout << ans[j] << " ";
	}
	cout << endl;
	
	return 0;
}

