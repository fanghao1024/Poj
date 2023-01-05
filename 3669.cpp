#include <stdio.h>
#include <string.h>
#include <queue>
#include <utility>
using namespace std;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

struct Pos {
	int x;
	int y;
	int seq;
};
int M;
int x_pos, y_pos, t;
int hit[310][310];
bool used[310][310];


queue<Pos> q;
Pos p;
int min_(int x, int y) {
	if (x < y) {
		return x;
	} else {
		return y;
	}
}
int solve() {

	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &x_pos, &y_pos, &t);
		if (hit[y_pos][x_pos] == -1) {
			hit[y_pos][x_pos] = t;
		}
		for (int j = 0; j < 4; j++) {
			if (x_pos + dx[j] >= 0 && x_pos + dx[j] <= 302 && y_pos + dy[j] >= 0 && y_pos + dy[j] <= 302) {
				if (hit[y_pos + dy[j]][x_pos + dx[j]] == -1) {
					hit[y_pos + dy[j]][x_pos + dx[j]] = t;
				} else {
					hit[y_pos + dy[j]][x_pos + dx[j]] = min_(hit[y_pos + dy[j]][x_pos + dx[j]], t);
				}

			}
		}

	}
	p.x = 0;
	p.y = 0;
	p.seq = 0;
	used[p.y][p.x] = false;
	q.push(p);
	Pos item;
	int x, y, seq;
	while (!q.empty()) {
		item = q.front();
		q.pop();
		x = item.x;
		y = item.y;
		seq = item.seq;
		if (hit[y][x] == -1) {

			return seq;
		}
		if (hit[y][x] <= seq) {
			return -1;
		}
		for (int i = 0; i < 4; i++) {
			if (x + dx[i] >= 0 && x + dx[i] <= 302 && y + dy[i] >= 0 && y + dy[i] <= 302 && used[y + dy[i]][x + dx[i]]) {
				used[y + dy[i]][x + dx[i]] = false;
				if (hit[y + dy[i]][x + dx[i]] == -1) {

					return seq + 1;
				} else {
					if (hit[y + dy[i]][x + dx[i]] > seq + 1) {
						p.x = x + dx[i];
						p.y = y + dy[i];
						p.seq = seq + 1;
						q.push(p);
					}
				}
			}
		}

	}
	return -1;
}
int main() {
	memset(hit, -1, sizeof(hit));
	memset(used, true, sizeof(used));
	scanf("%d", &M);
	int ans = solve();
	printf("%d\n", ans);
	return 0;
}
