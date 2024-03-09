#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
const int HASH=40001;

ll dp[2][1<<24],ans;
int state[2][1<<24];
int N,M,now,pre,endx,endy;
int total[2];
int Hash[HASH];
int rec[15][15];
void init(){
	memset(rec,0,sizeof(rec));
	endx=-1;
	for(int i=0;i<N;i++){
		char ch[20];
		scanf("%s",ch);
		for(int j=0;j<M;j++){
			if(ch[j]=='*') rec[i][j]=0;
			else{
				rec[i][j]=1;
				endx=i;
				endy=j;
			}
		}
	}
	
}
int getV(int S,int p,int l=2){
	return (S>>(p*l))&&((1<<l)-1);
}
void setV(int& S,int p,int v,int l=2){
	S^=getV(S,p)<<(l*p);
	S|=v<<(l*p);
}
void memsetnow(){
	memset(Hash,-1,sizeof(Hash));
	total[now]=0;
}
void HashIn(int S,ll num){
	int x=S%HASH;
	while(Hash[x]!=-1&&state[now][Hash[x]]!=S){
		x++;
		if(x>=HASH) x-=HASH;
	}
	if(Hash[x]==-1){
		dp[now][total[now]]=num;
		state[now][total[now]]=S;
		Hash[x]=total[now]++;
	}else{
		dp[now][Hash[x]]+=num;
	}
}
void solve(){
	init();
	if(endx==-1){
		printf("0\n");
		return ;
	}
	ans=0;
	pre=0;
	now=1;
	dp[pre][0]=1;
	state[pre][0]=0;
	total[pre]=1;
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			memsetnow();
			for(int s=0;s<total[pre];s++){
				if(dp[pre][s]){
					ll num=dp[pre][s];
					int S=state[pre][s];
					int p=getV(S,j);
					int q=getV(S,j+1);
					if(!rec[i][j]){
						if(!p&&!q){
							HashIn(S,num);
						}
						continue;
					}
					if(!p&&!q){
						if(rec[i+1][j]&&rec[i][j+1]){
							int nS=S;
							setV(nS,j,1);
							setV(nS,j+1,2);
							HashIn(nS,num);
						}
						continue;
					}
					if((p>0)^(q>0)){
						if(rec[i+(p>0)][j+(q>0)]){
							HashIn(S,num);
						}
						if(rec[i+(q>0)][j+(p>0)]){
							int nS=S;
							setV(nS,j,q);
							setV(nS,j+1,p);
							HashIn(nS,num);
						}
						continue;
					}
					if(p==1&&q==1){
						int find=1;
						for(int v=j+2;v<=M;v++){
							int k=getV(S,v);
							if(k==1) find++;
							if(k==2) find--;
							if(!find){
								int nS=S;
								setV(nS,j,0);
								setV(nS,j+1,0);
								setV(nS,v,1);
								HashIn(nS,num);
								break;
							}
						}
						continue;
					}
					if(p==2&&q==2){
						int find=1;
						for(int v=j-1;v>=0;v--){
							int k=getV(S,v);
							if(k==2) find++;
							if(k==1) find--;
							if(!find){
								int nS=S;
								setV(nS,j,0);
								setV(nS,j+1,0);
								setV(nS,v,2);
								HashIn(nS,num);
								break;
							}
						}
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
	while(scanf("%d%d",&N,&M)!=EOF){
		solve();
	}
	return 0;
}

