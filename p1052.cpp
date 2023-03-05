#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=20010;

int a[max_n],b[max_n],q[max_n],ff[max_n];
int L,S,T,M;

int main(){
	scanf("%d %d %d %d",&L,&S,&T,&M);
	a[0]=0;
	for(int i=1;i<=M;i++){
		scanf("%d",&a[i]);
	}
	a[M+1]=L;
	sort(a,a+M+2);
	memset(b,0,sizeof(b));
	int cnt=0;
	for(int i=1;i<=M+1;i++){
		if(a[i]-a[i-1]>=T) cnt+=T+((a[i]-a[i-1])%T);
		else cnt+=a[i]-a[i-1];
		b[cnt]=1;
	}
	b[cnt]=0;
	int f=0,r=-1;
	int l=0;
	//memset(ff,0x3f,sizeof(ff));
	//ff[0]=0;
	for(int i=1;i<=cnt+T-1;i++){
		//for(int j=S;j<=T;j++){
		//	if(i-j>=0) ff[i]=min(ff[i],ff[i-j]+b[i]);
		//}
		
		if(i<S){
			b[i]=0x3f3f3f3f;
			continue;
		}
		while(l<=i-S){
			while(f<=r&&b[l]<b[q[r]]) r--;
			q[++r]=l;
			l++;
		}
		while(f<=r&&q[f]<i-T) f++;
		b[i]+=b[q[f]];

	}
	int ans=0x3f3f3f3f;
	//for(int i=1;i<=cnt+T-1;i++) printf("%d ",b[i]);
	for(int i=cnt;i<=cnt+T-1;i++) ans=min(ans,b[i]);
	printf("%d\n",ans);
	return 0;
}
