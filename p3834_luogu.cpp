#include <bits/stdc++.h>
using namespace std ;
const int N = 200010;
int cnt = 0;        //用cnt标记可以使用的新结点
int a[N], b[N], root[N]; //a[]是原数组,b[]是排序后数组，root[i]记录第i棵线段树的根结点编号
struct{             //定义结点
	int L, R, sum;  //L左儿子, R右儿子，sum[i]是结点i的权值（即图中圆圈内的数字）
}tree[N<<5];        //  <<4是乘16倍，不够用；<<5差不多够用   
int build(int pl, int pr){        //初始化一棵空树，实际上无必要
	int rt = ++ cnt;              //cnt为当前结点编号
	tree[rt].sum = 0;
	int mid=(pl+pr)>>1;
	if (pl < pr){
		tree[rt].L = build(pl, mid);
		tree[rt].R = build(mid+1, pr);
	}
	return rt;      //返回当前结点的编号
}
int update(int pre, int pl, int pr, int x){   //建一棵只有logn个结点的新线段树
	int rt = ++cnt;           //新的结点，下面动态开点
	tree[rt].L = tree[pre].L; //该结点的左右儿子初始化为前一棵树相同位置结点的左右儿子
	tree[rt].R = tree[pre].R; 
	tree[rt].sum = tree[pre].sum + 1;  //插了1个数，在前一棵树的相同结点加1
	int mid = (pl+pr)>>1;
	if (pl < pr){            //从根结点往下建logn个结点
		if (x <= mid)        //x出现在左子树，修改左子树 
			tree[rt].L = update(tree[pre].L, pl, mid, x);
		else                 //x出现在右子树，修改右子树
			tree[rt].R = update(tree[pre].R, mid+1, pr, x);
	}
	return rt;               //返回当前分配使用的新结点的编号
}
int query(int u, int v, int pl, int pr, int k){    //查询区间[u,v]第k小
	if (pl == pr) return pl;  //到达叶子结点，找到第k小，pl是结点编号，答案是b[pl] 
	int x = tree[tree[v].L].sum - tree[tree[u].L].sum;   //线段树相减
	int mid = (pl+pr)>>1;
	if (x >= k)     //左儿子数字大于等于k时，说明第k小的数字在左子树
		return query(tree[u].L, tree[v].L, pl, mid, k);
	else            //否则在右子树找第k-x小的数字 
		return query(tree[u].R, tree[v].R, mid+1, pr, k-x);
}
int main(){
	int n, m;    scanf("%d%d", &n, &m);
	for (int i=1; i<=n; i++){ scanf("%d", &a[i]);  b[i]=a[i]; }
	sort(b+1, b+1+n);    //对b排序
	int size = unique(b+1, b+1+n)-b-1; //size等于b数组中不重复的数字的个数
	//root[0] = build(1, size);   //初始化一棵包含size个元素的空树，实际上无必要
	for (int i = 1; i <= n; i ++){     //建n棵线段树
		int x = lower_bound(b+1, b+1+size, a[i]) - b;
		//找等于a[i]的b[x]。x是离散化后a[i]对应的值
		root[i] = update(root[i-1], 1, size, x);  
		//建第i棵线段树，root[i]是第i棵线段树的根结点
	}
	while (m--){
		int x, y, k;      scanf("%d%d%d", &x, &y, &k);
		int t = query(root[x-1], root[y], 1, size, k); 
		//第y棵线段树减第x-1棵线段树，就是区间[x,y]的线段树
		printf("%d\n", b[t]);
	}
	return 0;
}

