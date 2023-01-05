#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;

const int maxn = 50000 + 5;

struct Cow {
	int A;
	int B;
	int id;
	bool operator<(const Cow &C) const {
		if (this->A != C.A) {
			return this->A < C.A;
		} else {
			return this->B < C.B;
		}
	}
};
Cow cow[maxn];
int stall[maxn];

typedef pair<int, int> P;
priority_queue<P, vector<P>, greater<P> >pq;

int main() {
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &cow[i].A, &cow[i].B);
		cow[i].id = i;
	}
	sort(cow, cow + N);
	pq.push(make_pair(cow[0].B, 1));
	stall[cow[0].id] = 1;
	int min_cap = 0;
	for (int i = 1; i < N; i++) {
		if (cow[i].A <= pq.top().first) {
			stall[cow[i].id] = pq.size() + 1;
			pq.push(make_pair(cow[i].B, pq.size() + 1));

		} else {
			P top = pq.top();
			stall[cow[i].id] = top.second;
			pq.pop();
			pq.push(make_pair(cow[i].B, top.second));
		}
		//printf("---%d\n", pq.size());
		//min_cap = max(min_cap, pq.size());
	}
	printf("%d\n", pq.size());
	for (int i = 0; i < N; i++) {
		printf("%d\n", stall[i]);
	}


	return 0;
}