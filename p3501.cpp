#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef unsigned long long ull;

const int max_n=5e5+10;

int N,tot;
char s[max_n],str[max_n<<1];
int P[max_n<<1];
char to[500]; 
ull ans;
void change(){
	tot=1;
	str[0]='$';str[1]='#';
	for(int i=0;i<N;i++) str[++tot]=s[i],str[++tot]='#';
	str[++tot]='&';
}
void manacher(){
	int R=0,c;
	for(int i=1;i<tot;i+=2){
		if(i<R){
			P[i]=min(P[(c<<1)-i],R-i);
		}else{
			P[i]=1;
		}
		while(str[i+P[i]]==to[str[i-P[i]]]) P[i]++;
		if(i+P[i]>R){
			R=i+P[i];
			c=i;
		}
		//printf("%c,%d,%d\n",str[i],P[i],P[i]>>1);
		ans+=P[i]>>1;
	}
}
int main(){
	scanf("%d",&N);
	scanf("%s",s);
	to['0']='1',to['1']='0',to['#']='#',to['$']='$',to['&']='&';
	change();
	ans=0;
	manacher();
	printf("%llu\n",ans);
	return 0;
}
