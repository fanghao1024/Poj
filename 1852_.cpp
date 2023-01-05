#include <stdio.h>
#include <math.h>

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
			min_time = max(min(n - dis, dis), min_time);
			max_time = max(max(n - dis, dis), max_time);
		}
		
		printf('%d %d\n', min_time, max_time);
	}
	return 0;
}
