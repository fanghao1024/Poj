#include<stdio.h>
#include<string.h>

int N,cnt;
const int H=10007;
const int max_n=1005;
int head[H];
int sx[max_n],sy[max_n];
struct Point{
	int x,y;
	int nxt;
}point[max_n];
void add_point(int x,int y){
	int h=(x*x+y*y)%H;
	point[cnt].x=x;
	point[cnt].y=y;
	point[cnt].nxt=head[h];
	head[h]=cnt++;
}
bool find(int x,int y){
	int h=(x*x+y*y)%H;
	for(int j=head[h];j!=-1;j=point[j].nxt){
		if(point[j].x==x&&point[j].y==y) return true;
	}
	return false;
}
int main(){
	while(scanf("%d",&N)&&N){
		memset(head,-1,sizeof(head));
		cnt=0;
		for(int i=0;i<N;i++){
			scanf("%d %d",&sx[i],&sy[i]);
			add_point(sx[i],sy[i]);
		}
		long long ans=0;
		for(int i=0;i<N;i++){
			for(int j=i+1;j<N;j++){
				int x4=sx[i]-(sy[i]-sy[j]);
				int y4=sy[i]+(sx[i]-sx[j]);
				int x3=sx[j]-(sy[i]-sy[j]);
				int y3=sy[j]+(sx[i]-sx[j]);
				if(find(x4,y4)&&find(x3,y3)){
					ans++;
				}
				x4=sx[i]+(sy[i]-sy[j]);
				y4=sy[i]-(sx[i]-sx[j]);
				x3=sx[j]+(sy[i]-sy[j]);
				y3=sy[j]-(sx[i]-sx[j]);
				if(find(x4,y4)&&find(x3,y3)){
					ans++;
				}
				
			}
		}
		ans>>=2;
		printf("%lld\n",ans);
	}
	return 0;
}

