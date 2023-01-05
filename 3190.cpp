#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <queue>
using namespace std;

struct Cow {
	int id;
	int A;
	int B;
	int mark;
};
Cow cow[50010];


int cmp(const void *a, const void *b) {
	Cow *x = (Cow *)a;
	Cow *y = (Cow *)b;
	if (x->B != y->B) {
		return x->B - y->B;
	} else {
		return x->A - y->A;
	}
}

int cmp_id(const void *a, const void *b) {
	Cow *x = (Cow *)a;
	Cow *y = (Cow *)b;
	return x->id - y->id;
}

int main() {
	int N;
	queue<Cow> q;
	queue<int> p;
	while (scanf("%d", &N) != EOF) {

		for (int i = 0; i < N; i++) {
			scanf("%d %d", &cow[i].A, &cow[i].B);
			cow[i].mark = -1;
			cow[i].id = i;
		}
		qsort(cow, N, sizeof(Cow), cmp);

		int count = 0;
		int flag;
		int a, b;
		while (!p.empty()) {
			p.pop();
		}
		while (!q.empty()) {
			q.pop();
		}
		for (int i = 0; i < N; i++) {
			//printf("%d %d\n", cow[i].A, cow[i].B);
			a = cow[i].A;
			b = cow[i].B;
			while (!q.empty() && q.front().B < a) {
				p.push(q.front().mark);
				q.pop();
			}
			if (p.empty()) {
				count++;
				cow[i].mark = count;
				q.push(cow[i]);
			} else {
				flag = p.front();
				p.pop();
				cow[i].mark = flag;
				q.push(cow[i]);
			}
		}
		qsort(cow, N, sizeof(Cow), cmp_id);
		printf("%d\n", count);
		for (int i = 0; i < N; i++) {
			printf("%d\n", cow[i].mark);
		}
	}
	return 0;
}