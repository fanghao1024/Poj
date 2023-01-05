#include <stdio.h>
#include <string.h>
#include <cmath>
#include <algorithm>

using namespace std;

bool used[10];

int get_num(int a[], int index) {
	int num = 0;
	for (int i = 0; i < index; i++) {
		num *= 10;
		num += a[i];
	}
	return num;
}

int permutation(int a[], int index_a, int b[], int index_b) {
	int min_num = 999999;

	while (next_permutation(a, a + index_a)) {
		if (a[0] != 0) {
			while (next_permutation(b, b + index_b)) {
				if (b[0] != 0) {
					//printf("%d %d %d\n", get_num(a, index_a), get_num(b, index_b), abs(get_num(a, index_a) - get_num(b, index_b)));
					min_num = min(min_num, abs(get_num(a, index_a) - get_num(b, index_b)));
				}
			}
		}
	}
	return min_num;

}

int solve(int nums[], int sx, int index) {
	int min_num = 999999;
	//printf("%d\n",sx);
	if (sx == index) {
		int a[10];
		int b[10];
		int index_a = 0;
		int index_b = 0;
		for (int i = 0; i < index; i++) {
			//printf("%d %d\n", used[i], nums[i]);
			if (used[i]) {
				a[index_a++] = nums[i];
			} else {
				b[index_b++] = nums[i];
			}
		}
		return permutation(a, index_a, b, index_b);

	} else {
		for (int i = sx; i < index; i++) {
			//printf("%d\n", i);
			used[i] = false;
			min_num = min(min_num, solve(nums, i + 1, index));
			used[i] = true;
			min_num = min(min_num, solve(nums, i + 1, index));
		}
	}
	return min_num;
}


int main() {
	int case_num;
	int nums[11];
	memset(used, true, sizeof(used));
	scanf("%d", &case_num);

	for (int ii = 0; ii < case_num; ii++) {
		int index = 0;
		char temp_num;
		getchar();
		while (scanf("%c", &temp_num)) {
			if (temp_num == '\n') {
				break;
			}
			if (temp_num == ' ') {
				continue;
			}
			nums[index] = int(temp_num) - int('0');
			index++;
		}
		if (index == 2) {
			printf("%d\n", abs(nums[1] - nums[0]));
		} else {
			printf("%d\n", solve(nums, 0, index));
		}

	}

	return 0;
}