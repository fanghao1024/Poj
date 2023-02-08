#include<stdio.h>
#include<string.h>

const int max_n=1000003;
int N,cnt;
int head[max_n];
struct Snow{
	int x[6];
}snow[max_n];
struct Edge{
	int id;
	int nxt;
}edge[max_n];
void add_hash(int index,int x){
	edge[cnt].id=x;
	edge[cnt].nxt=head[index];
	head[index]=cnt++;
}
bool cmp(int id1,int id2){
	
	for(int i=0;i<6;i++){
		int j=0;
		if(snow[id1].x[i]==snow[id2].x[j]){
			bool flag=true;
			for(int s=1;s<6;s++){
				if(snow[id1].x[(i+s)%6]!=snow[id2].x[(j+s)%6]){
					flag=false;
					break;
				}
			}
			if(flag) return true;
			flag=true;
			for(int s=1;s<6;s++){
				if(snow[id1].x[(i+s)%6]!=snow[id2].x[(j-s+6)%6]){
					flag=false;
					break;
				}
			}
			if(flag) return true;
		}
	}
	return false;
}
int main(){
	scanf("%d",&N);
	int x1,x2,x3,x4,x5,x6;
	bool flag=false;
	memset(head,-1,sizeof(head));
	cnt=0;
	int l=0;
	for(int i=0;i<N;i++){
		scanf("%d%d%d%d%d%d",&x1,&x2,&x3,&x4,&x5,&x6);
		if(flag) continue;
		int index=(x1+x2+x3+x4+x5+x6)%max_n;
		snow[l].x[0]=x1;
		snow[l].x[1]=x2;
		snow[l].x[2]=x3;
		snow[l].x[3]=x4;
		snow[l].x[4]=x5;
		snow[l].x[5]=x6;
		l++;
		if(head[index]==-1){
			add_hash(index,l-1);
		}else{
			for(int j=head[index];j!=-1;j=edge[j].nxt){
				if(cmp(l-1,edge[j].id)){
					flag=true;
				}else{
					add_hash(index,l-1);
				}
			}
		}	
	}
	if(flag){
		printf("Twin snowflakes found.\n");
	}else{
		printf("No two snowflakes are alike.\n");
	}
	return 0;
}
