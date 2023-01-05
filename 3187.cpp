#include <stdio.h>
#include <algorithm>
using namespace std;
int shape[11][11];

int main() {
	shape[1][1] = 1;
	int n;
	int sum;
	scanf("%d %d", &n, &sum);
	for (int i = 2; i <= n; i++) {
		shape[i][1] = 1;
		shape[i][i] = 1;
		for (int j = 2; j < i; j++) {
			shape[i][j] = shape[i - 1][j - 1] + shape[i - 1][j];
		}
	}
	int ans[10];
	for (int i = 0; i < n; i++) {
		ans[i] = i + 1;
	}
	int num;
	do {
		num = 0;
		for (int i = 0; i < n; i++) {
			num += ans[i] * shape[n][i + 1];
			if (num > sum) {
				break;
			}
		}
		if (num == sum) {
			break;
		}

	} while (next_permutation(ans, ans + n));
	for (int i = 0; i < n; i++) {
		if (i != 0) {
			printf(" ");
		}
		printf("%d", ans[i]);
	}
	printf("\n");
	return 0;
}