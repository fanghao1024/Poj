#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

const int max_l=12;
const int cantor_num=362890;
char ans[cantor_num];
char ch1[max_l];
char ch2[max_l];
int num1[max_l];
int num2[max_l];
int pos2[max_l];
int dx[4]={1,0,0,-1};
int dy[4]={0,-1,1,0};
int dep,minidep;

const char dname[]="dlru";
int h(){
	int res=0;
	for(int i=0;i<9;i++){
		if(num1[i]==8) continue;
		res+=abs(i/3-pos2[num1[i]]/3)+abs(i%3-pos2[num1[i]]%3);
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
		minidep=minidep<(d+t)?minidep:(d+t);
		return false;
	}
	for(int i=0;i<4;i++){
		int row=x/3+dx[i];
		int col=x%3+dy[i];
		int nx=row*3+col;
		if(row<0||row>2||col<0||col>2||nx==pre) continue;
		swap(num1[x],num1[nx]);
		ans[d]=dname[i];
		if(dfs(nx,d+1,x)) return true;
		swap(num1[x],num1[nx]);
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
	int T,x;
	scanf("%d",&T);
	for(int case_num=1;case_num<=T;case_num++){
		scanf("%s",ch1);
		scanf("%s",ch2);
		
		for(int i=0;i<9;i++){
			if(ch1[i]!='X'){
				num1[i]=ch1[i]-'1';
			}else{
				num1[i]=8;
				x=i;
			}
		}
		for(int i=0;i<9;i++){
			if(ch2[i]!='X'){
				num2[i]=ch2[i]-'1';
			}else{
				num2[i]=8;
			}
			pos2[num2[i]]=i;
		}

		idastar(x);
		printf("Case %d: %d\n",case_num,strlen(ans));
		printf("%s\n",ans);
	}
	return 0;
}
