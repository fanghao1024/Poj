#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int r[8][7]={
	{1,3,7,12,16,21,23},
	{2,4,9,13,18,22,24},
	{11,10,9,8,7,6,5},
	{20,19,18,17,16,15,14},
	{24,22,18,13,9,4,2},
	{23,21,16,12,7,3,1},
	{14,15,16,17,18,19,20},
	{5,6,7,8,9,10,11}
};
int pos[8]={7,8,9,12,13,16,17,18};
char dir[9]={'A','B','C','D','E','F','G','H'};
int a[30],rec[2000];
int dep;
bool check(){
	for(int i=1;i<8;i++){
		if(a[pos[i]]!=a[pos[0]]) return false;
	}
	return true;
}
int h(){
	int res=8;
	for(int i=1;i<=3;i++){
		int cnt=0;
		for(int j=0;j<8;j++){
			if(a[pos[j]]!=i) cnt++;
		}
		res=min(res,cnt);
	}
	return res;
}
bool ida(int d){
	if(check()){
		if(d==0){
			printf("No moves needed\n");
		}else{
			for(int i=0;i<d;i++){
				printf("%c",dir[rec[i]]);
			}
			printf("\n");
		}
		return true;
	}
	if(d>=dep) return false;
	if(d+h()>dep) return false;
	int b[25];
	for(int i=1;i<=24;i++) b[i]=a[i];
	for(int i=0;i<8;i++){
		rec[d]=i;
		for(int j=0;j<=5;j++){
			swap(a[r[i][j]],a[r[i][j+1]]);
		}
		if(ida(d+1)) return true;
		for(int j=1;j<=24;j++) a[j]=b[j];
	}
	return false;
}
int main(){
	while(scanf("%d",&a[1])&&a[1]){
		for(int i=2;i<=24;i++) scanf("%d",&a[i]);
		dep=0;
		while(1){
			if(ida(0)) break;
			dep++;
		}
		printf("%d\n",a[7]);
	}
	return 0;
}
