#include<bits/stdc++.h>
using namespace std;
const int N=100010;
int n,W;
int dp[N],q[N],num[N];
int v,w,m;                      //物品的价值v、体积c、数量m
int main(){
	cin >> n >> W;              //物品数量n，背包容量W
	memset(dp,0,sizeof(dp));        
	for(int i=1;i<=n;i++){
		cin>>v>>w>>m;            //物品i的价值v、体积c、数量m
		if(m>W/w) m = W/w;       //计算 min{m, j/c}
		for(int b=0;b<w;b++){    //按余数b进行循环
			int head=1, tail=0;
			for(int y=0;y<=(W-b)/w;y++){      //y = j/c
				int tmp = dp[b+y*w]-y*v;      //用队列处理tmp = dp[b + xc] - xv
				while(head<=tail && q[tail]<=tmp)   tail--;
				q[++tail] = tmp;
				num[tail] = y;
				while(head<=tail && y-num[head]>m)    head++;
				//约束条件y-min(mi,y)≤x≤y
				dp[b+y*w] = max(dp[b+y*w],q[head]+y*v);  //计算新的dp[]
			}
		}
	}
	cout << dp[W] << endl;
	return 0;
}

