#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;

const int max_n=2e5+10;

int N,M,N2;
int go[max_n<<1][20];
int res[max_n];
struct W{
	int L,R,id;
	bool operator<(const W& a) const{
		if(L!=a.L) return L<a.L;
		else return R<a.R;
	}
}w[max_n<<1];

void init(){
	int cur=1;
	for(int i=1;i<=N2;i++){
		while(cur<=N2&&w[cur].L<=w[i].R) cur++;
		go[i][0]=cur-1;
	}
	for(int i=1;(1<<i)<=N;i++){
		for(int s=1;s<=N2;s++){
			go[s][i]=go[go[s][i-1]][i-1];
		}
	}
}
void getans(int p){
	int ans=1;
	int len=w[p].L+M;
	int cur=p;
	for(int i=log2(N);i>=0;i--){
		int pos=go[cur][i];
		if(pos&&w[pos].R<len){
			ans+=(1<<i);
			cur=pos;
		}
	}
	res[w[p].id]=ans+1;
}
int main(){
	scanf("%d %d",&N,&M);
	for(int i=1;i<=N;i++){
		scanf("%d %d",&w[i].L,&w[i].R);
		w[i].id=i;
		if(w[i].R<w[i].L) w[i].R+=M;
	}
	N2=N;
	for(int i=1;i<=N;i++){
		N2++;
		
		w[N2].L=w[i].L+M;
		w[N2].R=w[i].R+M;
	}
	sort(w+1,w+1+N2);
	init();
	for(int i=1;i<=N;i++) getans(i);
	for(int i=1;i<=N;i++){
		if(i-1) printf(" ");
		printf("%d",res[i]);
	}
	printf("\n");
	return 0;
}

