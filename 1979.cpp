#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

int W, H;
int sx, sy;
bool used[22][22];
char matrix[22][22];

int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

int dfs(int sx, int sy) {
	if (matrix[sy][sx] == '#') {
		return 0;
	}
	int nums = 1;
	used[sy][sx] = false;
	for (int i = 0; i < 4; i++) {
		if (sx + dx[i] >= 0 && sx + dx[i] < W && sy + dy[i] >= 0 && sy + dy[i] < H && used[sy + dy[i]][sx + dx[i]]) {
			nums += dfs(sx + dx[i], sy + dy[i]);

		}
	}
	return nums;

}

int main() {


	while (scanf("%d %d", &W, &H) != EOF) {
		if (W == 0 && H == 0) {
			break;
		}
		for (int i = 0; i < H; i++) {
			scanf("%s", &matrix[i]);
		}

		memset(used, true, sizeof(used));

		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				if (matrix[i][j] == '@') {
					sx = j;
					sy = i;
					goto L;
				}
			}
		}
L:
		printf("%d\n", dfs(sx, sy));
	}
}