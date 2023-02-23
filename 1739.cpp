#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
const int HASH=4001;
ll dp[2][1<<18],ans;
int state[2][1<<18];
int rec[15][15];
int N,M,endx,endy,now,pre;
int Hash[HASH];
int total[2];

void init(){
	memset(rec,0,sizeof(rec));
	for(int i=0;i<N;i++){
		char ch[15];
		scanf("%s",ch);
		for(int j=0;j<M;j++){
			if(ch[j]=='#') rec[i][j]=0;
			else{
				rec[i][j]=1;
			}
		}
	}
	if(!rec[N-1][M-1]||!rec[N-1][0]){endx=endy=-1;}
	else{
		for(int i=0;i<M;i++){
			rec[N][i]=0;
			rec[N+1][i]=1;
		}
		rec[N][0]=rec[N][M-1]=1;
		endx=N+1;
		endy=M-1;
		N+=2;
	}
}
void memsetnow(){
	memset(Hash,-1,sizeof(Hash));
	total[now]=0;
}
int getV(int S,int j,int l=2){
	return (S>>(l*j))&((1<<l)-1);
}
void setV(int& S,int j,int v,int l=2){
	S^=getV(S,j)<<(l*j);
	S|=v<<(l*j);
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
	now=1;
	pre=0;
	dp[pre][0]=1;
	state[pre][0]=0;
	total[pre]=1;
	ans=0;
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
						if(!p&&!q) HashIn(S,num); 
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
	while(scanf("%d %d",&N,&M)&&(N+M)){
		if(N==1&&M==1){
			char ch[10];
			scanf("%s",ch);
			if(ch[0]=='#') printf("0\n");
			else printf("1\n");
		}
		else if(M==1){
			char ch[10][5];
			for(int i=0;i<N;i++){
				scanf("%s",ch[i]);
			}
			if(ch[N-1][0]=='#') printf("0\n");
			else{
				bool flag=1;
				for(int i=0;i<N-1;i++){
					if(ch[i][0]=='.'){
						flag=0;
						break;
					}
				}
				if(flag) printf("1\n");
				else printf("0\n");
			}
		}
		else solve();
	}	
	return 0;
}
