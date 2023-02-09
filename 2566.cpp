#include <stdio.h>
#include<algorithm>
using namespace std;

int N,K;
int num[100010];
//int query[100010];
struct Info{
	int nums;
	int id;
	Info(){};
	Info(int x){
		this->nums=x;
	}
	bool operator<(const Info& temp) const{
		return this->nums<temp.nums;
	}
}info[100010];
bool cmp(const Info& a,const Info& b){
	return a.nums<b.nums;
}

int get_data(int x,int target,bool& mark){
	int up_index=lower_bound(info, info+N, Info(x+target))-info;
	int low_index=lower_bound(info, info+N, Info(x-target))-info;
	int up_error=abs(info[up_index].nums-x)-target;
	if(up_index-1>=0){
		int up_error1=abs(info[up_index-1].nums-x)-target;
		if(abs(up_error1)<abs(up_error)){
			up_index=up_index-1;
			up_error=up_error1;
		}
	}
	int low_error=abs(info[low_index].nums-x)-target;
	if(low_index-1>=0){
		int low_error1=abs(info[low_index-1].nums-x)-target;
		if(abs(low_error1)<abs(low_error)){
			low_index=low_index-1;
			low_error=low_error1;
		}
	}
	if(abs(up_error)<=abs(low_error)){
		mark=true;
		return up_index;
	}else{
		mark=false;
		return low_index;
	}
}
int main() {
	
	while(scanf("%d %d",&N,&K)!=EOF){
		if(N==0&&K==0) break;
		for(int i=0;i<N;i++){
			scanf("%d",&num[i]);
		}
		info[0].nums=0;
		info[0].id=0;
		for(int i=1;i<=N;i++){
			info[i].nums=info[i-1].nums+num[i-1];
			info[i].id=i;
		}
		sort(info,info+N+1,cmp);
		int query;
		for(int i=0;i<K;i++) {
			scanf("%d",&query);
			int l=0,r=1;
			int minans=0x3fffffff;
			int ans,ansl,ansr;
			while(r<=N&&minans){
				int delta=info[r].nums-info[l].nums;
				if(abs(delta-query)<minans){
					minans=abs(delta-query);
					ans=delta;
					ansl=info[l].id;
					ansr=info[r].id;
				}
				if(delta<query) r++;
				if(delta>query) l++;
				if(l==r) r++;
			}
			if(ansl>ansr) swap(ansl,ansr);
			printf("%d %d %d\n",ans,ansl+1,ansr);
			/*
			bool mark,flag;
			int min_index=0;
			int min_to_index=get_data(info[0].nums,query,mark);
			flag=mark;
			int min_dis=abs(abs(info[min_to_index].nums-info[0].nums)-query);
			for(int j=1;j<N;j++){
				//printf("===%d %d %d\n",min_dis,info[min_index].id,info[min_to_index].id);
				int index=get_data(info[j].nums,query,mark);
				int dis=abs(abs(info[index].nums-info[j].nums)-query);
				if(dis<min_dis){
					//printf("===%d %d %d\n",dis,j,index);
					min_index=j;
					min_to_index=index;
					min_dis=dis;
					flag=mark;
				}
			}
			int x,y;
			if(flag){
				x=info[min_index].id+2;
				y=info[min_to_index].id+1;
			}else{
				y=info[min_index].id+1;
				x=info[min_to_index].id+2;
			}
			if(x>y){
				int temp=x;
				x=y;
				y=temp;
			}
			printf("%d %d %d\n",abs(info[min_to_index].nums-info[min_index].nums),x,y);*/
		}
	}
	return 0;
}