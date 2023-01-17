#include<stdio.h>
#include<bitset>
#include<algorithm>
using namespace std;

int L,T,O;
const int max_n=100010;
bitset<32> b[max_n<<2];
bool tag[max_n<<2];

int ls(int p){return p<<1;}
int rs(int p){return (p<<1)|1;}
void push_up(int p){
	b[p]=b[ls(p)]|b[rs(p)];
}
void build(int p,int pl,int pr){
	if(pl==pr){
		b[p][1]=1;
		tag[p]=0;
		return ;
	}
	int mid=(pl+pr)>>1;
	build(ls(p),pl,mid);
	build(rs(p),mid+1,pr);
	push_up(p);
}
void push_down(int p){
	if(tag[p]){
		tag[ls(p)]=tag[rs(p)]=1;
		b[ls(p)]=b[rs(p)]=b[p];
		tag[p]=0;
	}
}
void update(int L,int R,int d,int p,int pl,int pr){
	if(L>pr||R<pl) return;
	//printf("%d %d %d %d %d %d\n",L,R,d,p,pl,pr);
	if(L<=pl&&pr<=R){
		//printf("~~~%d %d %d %d %d %d\n",L,R,d,p,pl,pr);
		b[p]=1<<d;
		tag[p]=1;
		return ;
	}
	push_down(p);
	int mid=(pl+pr)/2;
	if(pl<=mid) update(L,R,d,ls(p),pl,mid);
	if(pr>mid) update(L,R,d,rs(p),mid+1,pr);
	push_up(p);
}
bitset<32> get_sum(int L,int R,int p,int pl,int pr){
	if(L<=pl&&pr<=R){
		return b[p];
	}
	push_down(p);
	int mid=(pl+pr)/2;
	bitset<32> bb;
	bb.reset();
	if(L<=mid) bb|=get_sum(L,R,ls(p),pl,mid);
	if(R>mid) bb|=get_sum(L,R,rs(p),mid+1,pr);
	push_up(p);
	return bb;
}
int main(){
	scanf("%d %d %d",&L,&T,&O);
	build(1,1,L);
	char M;
	int X,Y,Z;
	while(O--){
		scanf(" %c",&M);
		if(M=='C'){
			scanf("%d %d %d",&X,&Y,&Z);
			if(X>Y){
				swap(X,Y);
			}
			update(X,Y,Z,1,1,L);
		}else{
			scanf("%d %d",&X,&Y);
			if(X>Y){
				swap(X,Y);
			}
			printf("%d\n",get_sum(X,Y,1,1,L).count());
		}
	}
	return 0;
}
