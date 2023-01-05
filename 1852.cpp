#include <stdio.h>
#include <math.h>

int max_(int x, int y) {
	if (x > y) {
		return x;

	} else {
		return y;
	}
}



int min_(int x, int y) {
	if (x < y) {
		return x;
	} else {
		return y;
	}
}

int main() {
	int case_nums;
	int L, n;

	scanf("%d", &case_nums);
	for (int case_num = 0; case_num < case_nums; case_num++) {
		scanf("%d %d", &L, &n);
		int min_time = -1;
		int max_time = -1;
		int dis;
		for (int i = 0; i < n; i++) {
			scanf("%d", &dis);
			min_time = max_(min_(L - dis, dis), min_time);
			max_time = max_(max_(L - dis, dis), max_time);
		}

		printf("%d %d\n", min_time, max_time);
	}
	return 0;
}