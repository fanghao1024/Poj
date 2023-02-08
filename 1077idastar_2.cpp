#include<stdio.h>
#include<string.h>
#include<cmath>
#include<algorithm>
using namespace std;

const int cantor_num=362890;
const int max_l=12;
const int Len=9;
char inputs[max_l];
int a[max_l];
char ans[cantor_num];
int dep,minidep;
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
const char dname[]="drul";

bool check(){
	int res=0;
	for(int i=0;i<9;i++){
		if(a[i]!=8){
			for(int j=i+1;j<9;j++){
				if(a[i]>a[j]) res++;
			}
		}
	}
	return (res%2)==0;
}
int h(){
	int res=0;
	for(int i=0;i<9;i++){
		if(a[i]!=8){
			res+=abs(i%3-a[i]%3)+abs(i/3-a[i]/3);
		}
	}
	return res;
}
bool dfs(int x,int d,int pre){
	int t=h();
	if(!t){
		ans[d]='\0';
		return true;
	}
	if(d+t>dep){ 
		minidep=minidep<d+t?minidep:d+t;
		return false;
	}
	for(int i=0;i<4;i++){
		int row=x/3+dx[i];
		int col=x%3+dy[i];
		int nx=row*3+col;
		if(row<0||row>2||col<0||col>2||nx==pre) continue;
		swap(a[x],a[nx]);
		ans[d]=dname[i];
		if(dfs(nx,d+1,x)) return true;
		swap(a[x],a[nx]);
	}
	return false;
	
}
void idastar(int x){
	dep=h();
	while(1){
		minidep=0x3f3f3f3f;
		if(dfs(x,0,-1)){
			break;
		}
		dep=minidep;
	}
}
int main(){
	int x;
	while(~scanf("%s",ans)){
		if(ans[0]>'0'&&ans[0]<'9')
			a[0]=ans[0]-'0'-1;
		else if(ans[0]=='x')
			x=0,a[0]=8;
		for(int i=1;i<9;i++){
			scanf("%s",ans);
			if(ans[0]>'0'&&ans[0]<'9')
				a[i]=ans[0]-'0'-1;
			else if(ans[0]=='x')
				x=i,a[i]=8;
		}
		
		if(check()){
			idastar(x);
			printf("%s\n",ans);
		}else{
			printf("unsolvable\n");
		}

	}
	
	return 0;
}

