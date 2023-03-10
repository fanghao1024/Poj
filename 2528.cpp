#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;

const int max_n=1e5+100;

int L[max_n],R[max_n];
int rec[max_n<<1];
bool vis[max_n<<1];
int tree[max_n*8];
int C,N,cnt,ind,n;
map<int,int> mii;
int ls(int x){return x<<1;}
int rs(int x){return x<<1|1;}

void push_down(int p){
	if(tree[p]!=-1){
		tree[ls(p)]=tree[rs(p)]=tree[p];
		tree[p]=-1;
	}
	
}
void update(int p,int pl,int pr,int L,int R,int val){
	if(L<=pl&&pr<=R){
		tree[p]=val;
		return ;
	}
	push_down(p);
	int mid=(pl+pr)>>1;
	if(L<=mid) update(ls(p),pl,mid,L,R,val);
	if(R>mid) update(rs(p),mid+1,pr,L,R,val);
}
void down(int p,int pl,int pr){
	if(pl==pr&&tree[p]!=-1){
		vis[tree[p]]=1;
		return ;
	}
	push_down(p);
	int mid=(pl+pr)>>1;
	down(ls(p),pl,mid);
	down(rs(p),mid+1,pr);
}
int main(){
	scanf("%d",&C);
	while(C--){
		scanf("%d",&N);
		ind=0;
		for(int i=1;i<=N;i++){
			scanf("%d %d",&L[i],&R[i]);
			rec[++ind]=L[i];
			rec[++ind]=R[i];
		}
		sort(rec+1,rec+1+ind);
		cnt=unique(rec+1,rec+1+ind)-rec-1;
		//mii.clear();
		//mii[rec[1]]=1;
		for(int i=cnt;i>1;i--){
			if(rec[i]-rec[i-1]>1){
				rec[++cnt]=rec[i]-1;
			}
		}
		sort(rec+1,rec+1+cnt);
		/*
		for(int i=2;i<=cnt;i++){
			if(rec[i]!=rec[i-1]+1){
				mii[rec[i]]=mii[rec[i-1]]+2;
			}else{
				mii[rec[i]]=mii[rec[i-1]]+1;
			}
		}
		n=mii[rec[cnt]];
		 */
		memset(tree,0,sizeof(tree));
		for(int i=1;i<=N;i++){
			int l=lower_bound(rec+1,rec+1+cnt,L[i])-rec;
			int r=lower_bound(rec+1,rec+1+cnt,R[i])-rec;
			update(1,1,cnt,l,r,i);
		}
		memset(vis,0,sizeof(vis));
		down(1,1,cnt);
		int ans=0;
		for(int i=1;i<=cnt;i++) if(vis[i]) ans++;
		printf("%d\n",ans);
	}
	return 0;
}

