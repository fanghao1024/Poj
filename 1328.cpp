#include <stdio.h>
#include <cstdlib>
#include <cmath>

struct Info {
	double x;
	double y;
};

int cmp(const void *a, const void *b) {
	Info *s = (Info *)a;
	Info *l = (Info *)b;
	/*
	qsort的compare参数返回值是int
	如果用return (double) - (double),强制转换的时候就会出问题
	正确的方法应该是return (double)>(double)?1:-1;
	*/
	return  s->y > l->y ? 1 : -1;


}

Info info[1010];
Info dis[1010];

double distance(double x1, double y1, double x2, double y2) {
	return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

double get_left_loc(double x, double y, double d) {
	return x - sqrt(pow(d, 2) - pow(y, 2));
}

double get_right_loc(double x, double y, double d) {
	return x + sqrt(pow(d, 2) - pow(y, 2));
}

int main() {
	int n;
	double d;

	int case_num = 1;

	while (scanf("%d %lf", &n, &d) != EOF) {
		if (n == 0 && d == 0) {
			break;
		}
		int count = 0;
		bool flag = true;
		for (int i = 0; i < n; i++) {
			scanf("%lf %lf", &info[i].x, &info[i].y);
			if (info[i].y <= d) {
				dis[i].x = get_left_loc(info[i].x, info[i].y, d);
				dis[i].y = get_right_loc(info[i].x, info[i].y, d);
			}

			if (info[i].y > d || info[i].y < 0) {
				flag = false;
			}
		}

		if (flag == false || d <= 0) {
			printf("Case %d: -1\n", case_num++);
			continue;
		}
		if (n == 1) {
			printf("Case %d: 1\n", case_num++);
			continue;
		}
		qsort(dis, n, sizeof(Info), cmp);
		//for (int i = 0; i < n; i++) {
		//	printf("%lf %lf\n", dis[i].x, dis[i].y);
		//}
		//printf("\n\n\n");
		double last_time = dis[0].y;
		int choice = 0;

		//printf("%lf %lf\n", dis[0].x, dis[0].y);
		for (int i = 1; i < n; i++) {
			//printf("%lf %lf\n", dis[i].x, dis[i].y);
			if (dis[i].x > dis[choice].y) {
				count++;
				choice = i;
			}
		}

		printf("Case %d: %d\n", case_num++, count + 1);

	}
	return 0;
}