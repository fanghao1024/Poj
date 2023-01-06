#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <string>
#include <sstream>
#include <math.h> 
#include <string.h>
#include <algorithm>
#include <numeric>
#include <deque>
#include <climits>

using namespace std;

typedef long long ll;

// const double M_PI = acos(-1.0);
// const double E = 2.71828182845904523536029;

const int S = 1000000000;
const int NUM = 4;
struct BigInt {
	ll val[NUM];
	BigInt() {
		for (int i = 0; i < NUM; i++)
			val[i] = 0;
	}
}dp[1010];

void add(BigInt& b1, BigInt& b2) {
	for (int i = 0; i < NUM; i++) {
		b1.val[i] += b2.val[i];
	}
	for (int i = 1; i < NUM; i++) {
		b1.val[i] += b1.val[i - 1] / S;
	}
	for (int i = 0; i < NUM; i++) {
		b1.val[i] %= S;
	}
}

int main() {
	int n, k; cin >> n >> k;
	
	for (int i = 1; i <= n; i++) {
		dp[i].val[0] = 1;
	}
	
	for (int i = 2; i <= k; i++) {
		for (int j = i; j <= n; j++) {
			add(dp[j], dp[j - i]);
		}
		for (int j = i; j <= n; j += i) {
			BigInt bi;
			bi.val[0] = 1;
			add(dp[j], bi);
		}
	}
	
	bool startZero = true;
	for (int i = 3; i >= 0; i--) {
		if (dp[n].val[i] == 0 && startZero)
			continue;
		startZero = false;
		cout << dp[n].val[i];
	}
	cout << endl;
	
	return 0;
}
