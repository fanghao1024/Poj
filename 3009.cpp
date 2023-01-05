#include <stdio.h>
int w, h;
int matrix[22][22];
int sx, sy;
int gx, gy;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

struct position {
	int x;
	int y;
	int result;
};

position get_nextpos(int x, int y, int dir) {
	position pos;
	pos.x = -1;
	pos.y = -1;
	pos.result = -1;
	while (x + dx[dir] >= 0 && x + dx[dir] < w && y + dy[dir] >= 0 && y + dy[dir] < h) {
		switch (matrix[y + dy[dir]][x + dx[dir]]) {
			case 0:
				x += dx[dir];
				y += dy[dir];
				break;
			case 1:
				pos.x = x;
				pos.y = y;
				pos.result = 0;
				return pos;
			case 2:
				x += dx[dir];
				y += dy[dir];
				break;
			case 3:
				x += dx[dir];
				y += dy[dir];
				pos.x = x;
				pos.y = y;
				pos.result = 1;
				return pos;
		}

	}
	return pos;
}

int dfs(int x, int y, int count) {
	if (count > 10) {
		return -1;
	}
	int next_x, next_y;
	position pos;
	int nums = 100;
	for (int i = 0; i < 4; i++) {

		if (x + dx[i] >= 0 && x + dx[i] < w && y + dy[i] >= 0 && y + dy[i] < h && matrix[y + dy[i]][x + dx[i]] != 1) {
			pos = get_nextpos(x, y, i);

			switch (pos.result) {
				case -1:
					break;
				case 1:
					return count + 1;
				case 0:
					matrix[pos.y + dy[i]][pos.x + dx[i]] = 0;
					int num = dfs(pos.x, pos.y, count + 1);

					if (num > -1) {
						if (nums > num) {
							nums = num;
						}
					}
					matrix[pos.y + dy[i]][pos.x + dx[i]] = 1;
					break;
			}
		}
	}
	if (nums > 10) {
		return -1;
	} else {
		return nums;
	}

}
int main() {
	while (scanf("%d %d", &w, &h) != EOF) {
		if (w == 0 && h == 0) {
			break;
		}
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				scanf("%d", &matrix[i][j]);
				if (matrix[i][j] == 2) {
					sx = j;
					sy = i;
				}
				if (matrix[i][j] == 3) {
					gx = j;
					gy = i;
				}
			}
		}
		printf("%d\n", dfs(sx, sy, 0));
	}
	return 0;
}