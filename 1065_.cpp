#include<stdio.h>
#include<string.h>
#include<iostream>
#include<algorithm>
using namespace std;

struct Stick{
	int l;
	int w;
}stick[5010];
int record[5010];
bool cmp(const Stick& a,const Stick &b){
	if(a.l!=b.l){
		return a.l<b.l;
	}else{
		return a.w<b.w;
	}
}
int main(){
	int n,T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=0;i<n;i++){
			cin>>stick[i].l>>stick[i].w;
			
		}
		sort(stick,stick+n,cmp);
		memset(record,0x3f,sizeof(record));
		for(int i=0;i<n;i++){
			*lower_bound(record,record+n,-stick[i].w)=-stick[i].w;
		}
		cout<<lower_bound(record,record+n,0x3f)-record<<endl;
	}
	return 0;
}
