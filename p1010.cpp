#include<cstdio>
#include<iostream>
#include<string>
using namespace std;

const int max_n=2e4+10;

string ch[5];
bool flag;
void init(){
	ch[1]="2(0)";
	ch[2]="2";
	ch[3]="2+2(0)";
	ch[4]="2(2)";
}
void solve(int n,int k){
		if(n==0) return ;
		int temp=n%2;
		solve(n/2,k+1);
		if(temp){
			int num=temp<<k;
			if(num<=4){
				if(!flag) flag=true;
				else printf("+");
				cout<<ch[num];
			}else{
				if(!flag) flag=true;
				else printf("+");
				cout<<"2(";
				flag=false;
				solve(k,0);
				cout<<")";
			}
		}
	
}
int main(){
	int n;
	init();
	cin>>n;
	flag=false;
	solve(n,0);
	return 0;
}
