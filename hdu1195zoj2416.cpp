#include<cstdio>
#include<cstring>
#include<queue>
#include<set>
#include<string>
#include<iostream>
#include<algorithm>
#include<map>
using namespace std;

int vis[10][10][10][10];
int T;
int d1,d2;
string s1,s2;
int ans;
typedef pair<int,int> P;
int ten[5]={1,10,100,1000,10000};
int getpos(int num,int i){
	return (num/ten[i])%10;
}
void setpos(int& num,int i,int val){
	num+=(val-getpos(num,i))*ten[i];
}
void dbfs(){
	queue<P> q;
	q.push(make_pair(d1,1));
	q.push(make_pair(d2,-1));
	while(!q.empty()){
		P p=q.front();
		q.pop();
		int d=p.first;
		int ch0=getpos(d,0),ch1=getpos(d,1),ch2=getpos(d,2),ch3=getpos(d,3);
		if(p.second>0){
			if(vis[ch0][ch1][ch2][ch3]<0){
				ans=p.second-vis[ch0][ch1][ch2][ch3]-2;
				break ;
			}
			if(vis[ch0][ch1][ch2][ch3]>0)  continue;
		}
		if(p.second<0){
			if(vis[ch0][ch1][ch2][ch3]>0){
				ans=vis[ch0][ch1][ch2][ch3]-p.second-2;
				break ;
			}
			if(vis[ch0][ch1][ch2][ch3]<0) continue;
		}
		if(vis[ch0][ch1][ch2][ch3]==0) vis[ch0][ch1][ch2][ch3]=p.second;
		for(int i=0;i<4;i++){
			if(getpos(d,i)+1<=9){
				int temp=d+ten[i];
				if(vis[getpos(temp,0)][getpos(temp,1)][getpos(temp,2)][getpos(temp,3)]==0){
					//vis[temp[0]-'0'][temp[1]-'0'][temp[2]-'0'][temp[3]-'0']=p.second>0?p.second+1:p.second-1;
					q.push(make_pair(temp,p.second>0?p.second+1:p.second-1));
				}
			}else{
				int temp=d;
				setpos(temp,i,1);
				if(vis[getpos(temp,0)][getpos(temp,1)][getpos(temp,2)][getpos(temp,3)]==0){
					//vis[temp[0]-'0'][temp[1]-'0'][temp[2]-'0'][temp[3]-'0']=p.second>0?p.second+1:p.second-1;
					q.push(make_pair(temp,p.second>0?p.second+1:p.second-1));
				}
			}
			if(getpos(d,i)-1>0){
				int temp=d-ten[i];
				if(vis[getpos(temp,0)][getpos(temp,1)][getpos(temp,2)][getpos(temp,3)]==0){
					//vis[temp[0]-'0'][temp[1]-'0'][temp[2]-'0'][temp[3]-'0']=p.second>0?p.second+1:p.second-1;
					q.push(make_pair(temp,p.second>0?p.second+1:p.second-1));
				}
			}else{
				int temp=d;
				setpos(temp,i,9);
				if(vis[getpos(temp,0)][getpos(temp,1)][getpos(temp,2)][getpos(temp,3)]==0){
					//vis[temp[0]-'0'][temp[1]-'0'][temp[2]-'0'][temp[3]-'0']=p.second>0?p.second+1:p.second-1;
					q.push(make_pair(temp,p.second>0?p.second+1:p.second-1));
				}
			}
		}
		for(int i=0;i<3;i++){
			int temp=d;
			setpos(temp,i,getpos(d,i+1));
			setpos(temp,i+1,getpos(d,i));
			if(vis[getpos(temp,0)][getpos(temp,1)][getpos(temp,2)][getpos(temp,3)]==0){
				//vis[temp[0]-'0'][temp[1]-'0'][temp[2]-'0'][temp[3]-'0']=p.second>0?p.second+1:p.second-1;
				q.push(make_pair(temp,p.second>0?p.second+1:p.second-1));
			}
		}
	}
}
int main(){
	cin>>T;
	while(T--){
		memset(vis,0,sizeof(vis));
		cin>>d1>>d2;
		dbfs();
		printf("%d\n",ans);
	}
	return 0;
}
