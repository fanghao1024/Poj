#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
const int max_n=5e5+10;

int N,M;
//int a[max_n],b[max_n];
int ma[max_n<<2],se[max_n<<2],num[max_n<<2],mb[max_n<<2];
int tag1[max_n<<2],tag2[max_n<<2],tag3[max_n<<2],tag4[max_n<<2];
ll sum[max_n<<2];
int ls(int x){return x<<1;}
int rs(int x){return x<<1|1;}
void push_up(int p){
	ma[p]=max(ma[ls(p)],ma[rs(p)]);
	mb[p]=max(mb[ls(p)],mb[rs(p)]);
	sum[p]=sum[ls(p)]+sum[rs(p)];
	if(ma[ls(p)]==ma[rs(p)]){
		num[p]=num[ls(p)]+num[rs(p)];
		se[p]=max(se[ls(p)],se[rs(p)]);
	}else{
		if(ma[ls(p)]>ma[rs(p)]){
			num[p]=num[ls(p)];
			se[p]=max(se[ls(p)],ma[rs(p)]);
		}
		else{
			num[p]=num[rs(p)];
			se[p]=max(se[rs(p)],ma[ls(p)]);
		}
	}	
}
void build(int p,int pl,int pr){
	tag1[p]=tag2[p]=tag3[p]=tag4[p]=0;
	if(pl==pr){
		int x;
		scanf("%d",&x);
		ma[p]=mb[p]=sum[p]=x;
		se[p]=-2e9;
		num[p]=1;
		return ;
	}
	int mid=(pl+pr)>>1;
	build(ls(p),pl,mid);
	build(rs(p),mid+1,pr);
	push_up(p);
}
void change(int p,int pl,int pr,int t1,int t2,int t3,int t4){
	sum[p]+=1LL*t1*num[p]+1LL*t2*(pr-pl+1-num[p]);
	mb[p]=max(mb[p],ma[p]+t3);
	ma[p]+=t1;
	if(se[p]!=-2e9) se[p]+=t2;
	tag3[p]=max(tag3[p],tag1[p]+t3);
	tag4[p]=max(tag4[p],tag2[p]+t4);
	tag1[p]+=t1;
	tag2[p]+=t2;
}
void push_down(int p,int pl,int pr){
	int Max=max(ma[ls(p)],ma[rs(p)]);
	int mid=(pl+pr)>>1;
	if(ma[ls(p)]==Max){
		change(ls(p),pl,mid,tag1[p],tag2[p],tag3[p],tag4[p]);
	}else{
		change(ls(p),pl,mid,tag2[p],tag2[p],tag4[p],tag4[p]);
	}
	if(ma[rs(p)]==Max){
		change(rs(p),mid+1,pr,tag1[p],tag2[p],tag3[p],tag4[p]);
	}else{
		change(rs(p),mid+1,pr,tag2[p],tag2[p],tag4[p],tag4[p]);
	}
	tag1[p]=tag2[p]=tag3[p]=tag4[p]=0;
}
ll querySum(int p,int pl,int pr,int L,int R){
	if(L<=pl&&pr<=R){
		return sum[p];
	}
	int mid=(pl+pr)>>1;
	push_down(p,pl,pr);
	if(R<=mid) return querySum(ls(p),pl,mid,L,R);
	if(L>mid) return querySum(rs(p),mid+1,pr,L,R);
	return querySum(ls(p),pl,mid,L,mid)+querySum(rs(p),mid+1,pr,mid+1,R);
}
int query_maxa(int p,int pl,int pr,int L,int R){
	if(L<=pl&&pr<=R){
		return ma[p];
	}
	push_down(p,pl,pr);
	int mid=(pl+pr)>>1;
	if(R<=mid) return query_maxa(ls(p),pl,mid,L,R);
	if(L>mid) return query_maxa(rs(p),mid+1,pr,L,R);
	return max(query_maxa(ls(p),pl,mid,L,mid),query_maxa(rs(p),mid+1,pr,mid+1,R));
}
int query_maxb(int p,int pl,int pr,int L,int R){
	if(L<=pl&&pr<=R){
		return mb[p];
	}
	push_down(p,pl,pr);
	int mid=(pl+pr)>>1;
	if(R<=mid) return query_maxb(ls(p),pl,mid,L,R);
	if(L>mid) return query_maxb(rs(p),mid+1,pr,L,R);
	return max(query_maxb(ls(p),pl,mid,L,mid),query_maxb(rs(p),mid+1,pr,mid+1,R));
}
void update_add(int p,int pl,int pr,int L,int R,int val){

	if(L<=pl&&pr<=R){
		ma[p]+=val;
		mb[p]=max(mb[p],ma[p]);
		if(se[p]!=-2e9) se[p]+=val;
		sum[p]+=1LL*(pr-pl+1)*val;
		tag1[p]+=val;tag2[p]+=val;
		tag3[p]=max(tag3[p],tag1[p]);
		tag4[p]=max(tag4[p],tag2[p]);
		return ;
	}
	push_down(p,pl,pr);
	int mid=(pl+pr)>>1;
	if(L<=mid) update_add(ls(p),pl,mid,L,R,val);
	if(R>mid) update_add(rs(p),mid+1,pr,L,R,val);
	push_up(p);
}
void update_min(int p,int pl,int pr,int L,int R,int val){
	if(val>ma[p]) return ;
	if(L<=pl&&pr<=R&&val>se[p]){
		sum[p]-=1LL*num[p]*(ma[p]-val);
		tag1[p]-=ma[p]-val;
		ma[p]=val;
		return ;
	}
	push_down(p,pl,pr);
	int mid=(pl+pr)>>1;
	if(L<=mid) update_min(ls(p),pl,mid,L,R,val);
	if(R>mid) update_min(rs(p),mid+1,pr,L,R,val);
	push_up(p);
}
int main(){
	int ops,l,r,v,k;
	scanf("%d %d",&N,&M);
	//for(int i=1;i<=N;i++){
	//	scanf("%d",&a[i]);
	//}
	build(1,1,N);
	while(M--){
		scanf("%d",&ops);
		switch (ops) {
		case 1:
			scanf("%d %d %d",&l,&r,&k);
			update_add(1,1,N,l,r,k);
			break;
		case 2:
			scanf("%d %d %d",&l,&r,&v);
			update_min(1,1,N,l,r,v);
			break;
		case 3:
			scanf("%d %d",&l,&r);
			printf("%lld\n",querySum(1,1,N,l,r));
			break;
		case 4:
			scanf("%d %d",&l,&r);
			printf("%d\n",query_maxa(1,1,N,l,r));
			break;
		case 5:
			scanf("%d %d",&l,&r);
			printf("%d\n",query_maxb(1,1,N,l,r));
			break;
		}
	}
	return 0;
}
