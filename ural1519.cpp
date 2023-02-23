#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
#define LL long long
const int HASH=40001;
int n,m;
ll dp[2][1<<24],ans;
int state[2][1<<24];
int total[2];
int Hash[HASH];
bool map[15][15];
int endx,endy;
int now,pre;
void memsetnow(){
	memset(Hash,-1,sizeof(Hash));
	total[now]=0;
}
int getV(int S,int j,int l=2){
	return (S>>(l*j))&((1<<l)-1);
}
void setV(int& S,int j,int v,int l=2){
	S^=getV(S,j)<<(j*l);
	S|=v<<(j*l);
}
void HashIn(int S,ll num){
	int x=S%HASH;
	while(Hash[x]!=-1&&state[now][Hash[x]]!=S){
		x++;
		if(x>=HASH) x%=HASH;
	}
	if(Hash[x]==-1){
		dp[now][total[now]]=num;
		state[now][total[now]]=S;
		Hash[x]=total[now]++;
	}else{
		dp[now][Hash[x]]+=num;
	}
}
void init(){
	memset(map,0,sizeof(map));
	endx=-1;
	for(int i=0;i<n;i++){
		char ch[20];
		scanf("%s",ch);
		for(int j=0;j<m;j++){
			if(ch[j]=='*') map[i][j]=0;
			else{
				map[i][j]=1;
				endx=i;
				endy=j;
			}	
		}
	}
}

void solve(){
	init();
	if(endx==-1){
		printf("0\n");
		return ;
	}
	//memsetnow();
	pre=0;
	now=1;
	ans=0;
	dp[pre][0]=1;
	state[pre][0]=0;
	total[pre]=1;
	
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			memsetnow();
			for(int k=0;k<total[pre];k++){
				if(dp[pre][k]){
					ll num=dp[pre][k];
					int S=state[pre][k];
					int p=getV(S,j);
					int q=getV(S,j+1);
					if(!map[i][j]){
						if(!p&&!q) HashIn(S,num);
						continue;
					}
					if(!p&&!q){
						if(map[i+1][j]&&map[i][j+1])
						{
							int nS=S;
							setV(nS,j,1);
							setV(nS,j+1,2);
							HashIn(nS,num);
						}
						continue;	
					}
					if((p>0)^(q>0)){
						if(map[i+(p>0)][j+(q>0)]){
							HashIn(S,num);
						}
						if(map[i+(q>0)][j+(p>0)]){
							int nS=S;
							setV(nS,j,q);
							setV(nS,j+1,p);
							HashIn(nS,num);
						}
						continue;
					}
					if(p==1&&q==1){
						int nS=S;
						setV(nS,j,0);
						setV(nS,j+1,0);
						int find=1;
						for(int v=j+2;v<=m;v++){
							if(getV(nS,v)==1) find++;
							if(getV(nS,v)==2) find--;
							if(find==0){
								setV(nS,v,1);
								break;
							}
						}
						HashIn(nS,num);
						continue;
					}
					if(p==2&&q==2){
						int nS=S;
						setV(nS,j,0);
						setV(nS,j+1,0);
						int find=1;
						for(int v=j-1;v>=0;v--){
							if(getV(nS,v)==2) find++;
							if(getV(nS,v)==1) find--;
							if(find==0){
								setV(nS,v,2);
								break;
							}
						}
						HashIn(nS,num);
						continue;
					}
					if(p==2&&q==1){
						int nS=S;
						setV(nS,j,0);
						setV(nS,j+1,0);
						HashIn(nS,num);
						continue;
					}
					if(p==1&&q==2){
						if(i==endx&&j==endy) ans+=num;
					}
				}
			}
			swap(now,pre);
		}
		memsetnow();
		for(int s=0;s<total[pre];s++){
			if(dp[pre][s]){
				ll num=dp[pre][s];
				int S=state[pre][s]<<2;
				HashIn(S,num);
			}
		}
		swap(now,pre);
	}
	printf("%lld\n",ans);
}
int main(){
	while(scanf("%d %d",&n,&m)!=EOF){
		solve();
	}
	return 0;
}
