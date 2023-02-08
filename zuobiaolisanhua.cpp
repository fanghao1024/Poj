#include<stdio.h>
#include<string.h>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int W,H,N;
const int MAX_N=100;
int X1[MAX_N],X2[MAX_N],Y1[MAX_N],Y2[MAX_N];

bool fld[MAX_N*6][MAX_N*6];

int compress(int *x1,int* x2,int w){
	vector<int> xs;
	for(int i=0;i<N;i++){
		for(int d=-1;d<=1;d++){
			int tx1=x1[i]+d,tx2=x2[i]+d;
			cout<<x1[i]<<"###"<<x2[i]<<"~~~"<<tx1<<"---"<<tx2<<endl;
			if(1<=tx1 && tx1<=w) xs.push_back(tx1);
			if(1<=tx2 && tx2<=w) xs.push_back(tx2);
		}
	}
	for(auto it=xs.begin();it!=xs.end();it++) cout<<"===="<<*it<<endl;
	cout<<"hello"<<endl;
	sort(xs.begin(),xs.end());
	for(auto it=xs.begin();it!=xs.end();it++) cout<<"===="<<*it<<endl;
	cout<<"ok"<<endl;
	xs.erase(unique(xs.begin(),xs.end()),xs.end());
	for(auto it=xs.begin();it!=xs.end();it++) cout<<"===="<<*it<<endl;
	cout<<"ok!!!"<<endl;
	
	for(int i=0;i<N;i++){
		x1[i]=find(xs.begin(),xs.end(),x1[i])-xs.begin();
		x2[i]=find(xs.begin(),xs.end(),x2[i])-xs.begin();
	}
	
	return xs.size();
	
}

void solve(){
	W=compress(X1,X2,W);
	H=compress(Y1,Y2,H);
	printf("W:%d H:%d\n",W,H);
	memset(fld,0,sizeof(fld));
	for(int i=0;i<N;i++){
		for(int y=Y1[i];y<=Y2[i];y++){
			for(int x=X1[i];x<=X2[i];x++){
				fld[y][x]=true;
			}
		}
	}
	for(int i=1;i<=H;i++){
		for(int j=1;j<=W;j++){
			printf("%d ",fld[i][j]);
		}
		printf("\n");
	}
}

int main(){
	W=10;
	H=10;
	N=5;
	int xx1[5]={1,1,4,9,10};
	int xx2[5]={6,10,4,9,10};
	int yy1[5]={4,8,1,1,6};
	int yy2[5]={4,8,10,5,10};
	for(int i=0;i<5;i++){
		X1[i]=xx1[i];
		X2[i]=xx2[i];
		Y1[i]=yy1[i];
		Y2[i]=yy2[i];
	}
	solve();
	return 0;
}
