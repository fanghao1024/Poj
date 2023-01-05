#include <stdio.h>
#include <string>
#include <set>
#include <string.h>
#include <stdlib.h>
using namespace std;

int grid[5][5];

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

set<string> ss;

int dfs(int x, int y, string s, int count) {
	if (count == 5) {
		ss.insert(s);

	} else {
		for (int i = 0; i < 4; i++) {
			if (x + dx[i] >= 0 && x + dx[i] < 5 && y + dy[i] >= 0 && y + dy[i] < 5) {
				char c = '0' + grid[x + dx[i]][y + dy[i]];
				string s_(1, c);
				s_ = s + s_;
				dfs(x + dx[i], y + dy[i], s_, count + 1);
			}
		}
	}
	return 0;
}

int main() {
	string s;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			scanf("%d", &grid[i][j]);
		}
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			s = '0' + grid[i][j];
			dfs(i, j, s, 0);
		}
	}
	printf("%d\n", ss.size());
	return 0;
}