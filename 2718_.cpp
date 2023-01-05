#include <stdio.h>
#include <string.h>
#include <cmath>
#include <algorithm>

using namespace std;

int get_num(int a[], int index) {
	int num = 0;
	for (int i = 0; i < index; i++) {
		num *= 10;
		num += a[i];
	}
	return num;
}

int main() {
	int case_num;
	int nums[11];

	scanf("%d", &case_num);
	getchar();
	for (int ii = 0; ii < case_num; ii++) {
		int index = 0;
		int min_num = 0x3fffffff;
		char temp_num;

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

		int a;
		int b;
		do {
			a = get_num(nums, index / 2);
			b = get_num(nums + index / 2, index - index / 2);
			if (nums[0] == 0 && a != 0) {
				continue;
			}
			if (nums[index / 2] == 0 && b != 0) {
				continue;
			}

			min_num = min(min_num, abs(a - b));

		} while (next_permutation(nums, nums + index));
		if (index == 2) {
			printf("%d\n", abs(nums[1] - nums[0]));
		} else {
			printf("%d\n", min_num);
		}

	}

	return 0;
}