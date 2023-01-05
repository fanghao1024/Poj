#include <stdio.h>
#include <cstdlib>
#include <algorithm>
using namespace std;

struct Info {
	int s;
	int e;
};
Info info[25010];

int cmp(const void *a, const void *b) {
	Info *x = (Info *)a;
	Info *y = (Info *)b;
	if (x->s != y->s) {
		return x->s - y->s;
	} else {
		return y->e - x->e;
	}

}

int main() {
	int N, T;
	while (scanf("%d %d", &N, &T) != EOF) {
		for (int i = 0; i < N; i++) {
			scanf("%d %d", &info[i].s, &info[i].e);
		}
		qsort(info, N, sizeof(Info), cmp);

		int temp = 0;
		int choice = 0;
		int count = 0;
		bool flag = true;
		if (info[0].s > 1) {
			printf("-1\n");
			continue;
		}
		if (info[0].e >= T) {
			printf("1\n");
			continue;
		}
		for (int i = 1; i < N; i++) {
			if (info[i].s <= temp + 1) {
				if (info[i].e > info[choice].e) {
					choice = i;
				}
			} else {
				if (info[choice].s <= temp + 1) {
					count++;
					//printf("%d %d %d %d\n", choice, info[choice].s, info[choice].e, count);
					if (info[choice].e >= T) {
						temp = T;
						break;
					}


					temp = info[choice].e;

					if (info[i].s <= temp + 1) {
						choice = i;
					} else {
						printf("-1\n");
						flag = false;
						break;
					}

				} else {
					printf("-1\n");
					flag = false;
					break;
				}
			}
		}
		//printf("%d %d %d\n", flag, choice, info[choice].e);
		if (flag == true) {
			if (info[choice].e < T) {
				printf("-1\n");
				continue;
			} else {
				if (temp < T) {
					count++;
				}

			}
			printf("%d\n", count);
		}
	}
}