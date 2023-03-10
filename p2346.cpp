#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<sstream>
using namespace std;

int m[4][4];
int pos[2][2];
int dep;
int dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
int rec[1000];
void Print(){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			printf("%d ",m[i][j]);
		}
		printf("\n");
	}
}
bool check(){
	int res=4;
	for(int i=0;i<4;i++){
		int w=0,b=0;
		for(int j=0;j<4;j++){
			if(m[i][j]==1) b++;
			if(m[i][j]==2) w++;
		}
		res=min(res,min(4-w,4-b));
	}
	for(int i=0;i<4;i++){
		int w=0,b=0;
		for(int j=0;j<4;j++){
			if(m[j][i]==1) b++;
			if(m[j][i]==2) w++;
		}
		res=min(res,min(4-w,4-b));
	}
	for(int i=0;i<4;i++){
		int w=0,b=0;
		if(m[i][i]==1) b++;
		if(m[i][i]==2) w++;
		res=min(res,min(4-w,4-b));
	}
	for(int i=0;i<4;i++){
		int w=0,b=0;
		if(m[3-i][i]==1) b++;
		if(m[3-i][i]==2) w++;
		res=min(res,min(4-w,4-b));
	}
	return res;
}
bool ida(int d,int wb){
	if(!check()){
		//for(int i=0;i<d;i++) printf("%d ",rec[i]);
		//printf("\n");
		return true;
	}
	if(d>=dep){return false;}
	if(d+check()>dep) return false;
	int index=0;
	int p[2][2];
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(m[i][j]==3){
				p[index][0]=i;
				p[index][1]=j;
				index++;
			}
		}
	}
	for(int i=0;i<2;i++){
		for(int j=0;j<4;j++){
			int nr=p[i][0]+dir[j][0];
			int nc=p[i][1]+dir[j][1];
			if(nr>=0&&nr<=3&&nc>=0&&nc<=3&&m[nr][nc]==wb){
				rec[d]=j;//printf("swap^^^^^^^^^^^begin^^^^^^^^^^^^^\n");
				//Print();
				swap(m[p[i][0]][p[i][1]],m[nr][nc]);//printf("%d swap1---------------------------\n",d);
				//printf("%d ops:%d====%d %d->%d %d\n",d,j,pos[i][0],pos[i][1],nr,nc);
				//Print();
				if(ida(d+1,wb==1?2:1)) return true;
				swap(m[p[i][0]][p[i][1]],m[nr][nc]);//printf("%d swap2******************************\n",d);
				//Print();printf("swap^^^^^^^^^^^^end^^^^^^^^^^^\n");
				//printf("end iteration\n");
			}
		}
	}
	return false;
}
int main(){
	char ch;
	int index=0;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			cin>>ch;
			if(ch=='B'){
				m[i][j]=1;
			}
			else if(ch=='W'){
				m[i][j]=2;
			}
			else{
				pos[index][0]=i;
				pos[index][1]=j;
				index++;
				m[i][j]=3;
			}
		}
	}
	//Print();
	for(dep=0;;dep++){
		//printf("ok================================================\n");
		//Print();
		//printf("what===========================================\n");
		if(ida(0,1)||ida(0,2)){
			printf("%d\n",dep);
			break;
		}
	}
	//Print();
	return 0;
}
