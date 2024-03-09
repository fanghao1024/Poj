#include<cstdio>
#include<algorithm>
#include<cstring>
#include<set>
#include<map>
using namespace std;

const int max_n=2023;

int v[max_n<<1],temp[max_n<<1],tree[(max_n<<1)<<4],tag[(max_n<<1)<<4],color[max_n<<1];
struct Edge{
	int x,y;
	int c;
}edge[max_n];

int N,ptr;
int ls(int x){return x<<1;}
int rs(int x){return x<<1|1;}
void push_down(int p,int pl,int pr){
	if(tag[p]!=-1){
		tag[ls(p)]=tag[rs(p)]=tag[p];
		tag[p]=-1;
	}
}
void update(int p,int pl,int pr,int l,int r,int c){
	if(l<=pl&&pr<=r){
		tree[p]=c;
		return ;
	}
	push_down(p,pl,pr);
	int mid=(pl+pr)>>1;
	if(r<=mid) update(ls(p),pl,mid,l,r,c);
	else if(l>mid) update(rs(p),mid+1,pr,l,r,c);
	else{
		update(ls(p),pl,mid,mid,r,c);
		update(rs(p),mid+1,pr,mid+1,r,c);
	}
}
void query(int p,int pl,int pr){
	if(tag[p]!=-1){
		for(int i=pl;i<=pr;i++) color[i]=tag[p];
		return ;
	}
	push_down(p,pl,pr);
	int mid=(pl+pr)>>1;
	query(ls(p),pl,mid);
	query(rs(p),mid+1,pr);
}
int main(){
	int x,y;
	char ch[10];
	while(scanf("%d",&N)!=EOF){
		int cnt=1;
		for(int i=1;i<=N;i++){
			scanf("%d %d %s",&edge[i].x,&edge[i].y,ch);
			if(*ch=='w') edge[i].c=1;
			else edge[i].c=0;
			temp[cnt++]=edge[i].x;
			temp[cnt++]=edge[i].y;
		}
		sort(temp,temp+cnt);
		v[1]=temp[1];
		cnt=1;
		map<int,int> mii;
		mii[temp[1]]=1;
		for(int i=2;i<=2*N;i++){
			if(temp[i]==v[cnt]) continue;
			v[++cnt]=temp[i];
			mii[temp[i]]=cnt;
		}
		for(int i=1;i<=cnt;i++) color[i]=0;
		for(int i=1;i<=N;i++){
			for(int j=mii[edge[i].x];j<=mii[edge[i].y];j++)
				color[j]=edge[i].c;
		}
		
		/*
		memset(tag,-1,sizeof(tag));
		memset(tree,0,sizeof(tree));
		for(int i=1;i<=N;i++){
			update(1,1,cnt,mii[edge[i].x],mii[edge[i].y],edge[i].c);
		}
		ptr=1;
		query(1,1,cnt);
		 */
		int s=0,t=0;
		int anss=0,anst=0;
		for(int i=1;i<=cnt;i++){
			if(color[i]!=1) continue;
			s=v[i];
			while(i<=cnt&&color[i]==1) i++;
			t=v[i-1];
			if(t-s>anst-anss){
				anss=s;
				anst=t;
			}
		}
		if(anss==0) printf("Oh, my god\n");
		else printf("%d %d\n",anss,anst);
		  
		
	}
	return 0;
}
