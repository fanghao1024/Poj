#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=1024;

int X,N,T;
int v[max_n<<2][max_n<<2],tag[max_n<<2][max_n<<2];
int ls(int x){return x<<1;}
int rs(int x){return x<<1|1;}
void build2(int px,int p,int pl,int pr){
	v[px][p]=0;
}
void build1(int p,int pl,int pr){
	build2(p,1,1,N);
	if(pl==pr) return ;
	int mid=(pl+pr)>>1;
	build1(ls(p),pl,mid);
	build1(rs(p),mid+1,pr);
}
int main(){
	scanf("%d",&X);
	while(X--){
		scanf("%d %d",&N,&T);
		build1(1,1,N);
	}
	return 0;
}
