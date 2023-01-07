#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

short int dp[2][400005];

struct Block {
	int h, a, c;
} block[405];

bool cmp(const Block &a, const Block &b) {
	return a.a < b.a;
}
bool used[400005];

int main() {
	int K;
	scanf("%d", &K);
	for (int i = 0; i < K; i++) {
		scanf("%d %d %d", &block[i].h, &block[i].a, &block[i].c);
	}
	sort(block, block + K, cmp);

	//fill(dp,dp+405*400005,-1);
	memset(dp, -1, sizeof(short int) * 2 * 400005);
	memset(used, 0, sizeof(bool) * 400005);
	int index=0;
	dp[index][0] = 0;
	index=(index+1)%2;
	for (int i = 1; i <= K; i++) {
		
		for (int j = 0; j <= 400000; j++) {
			if (block[i-1].a < j) {
				break;
			}
			if (dp[(index+1)%2][j] >= 0) {
				dp[index][j] = block[i-1].c;
				used[j] = 1;
			} else {
				if (j < block[i-1].h || dp[index][j - block[i-1].h] <= 0) {
					dp[index][j] = -1;
				} else {
					dp[index][j] = dp[index][j - block[i-1].h] - 1;
					used[j] = 1;
				}
			}
			
		}
		index=(index+1)%2;
	}

	
	for (index = 400000; index >= 0; index--) {
		if (used[index] > 0) {
			break;
		}
	}
	printf("%d\n", index);
	return 0;
}
