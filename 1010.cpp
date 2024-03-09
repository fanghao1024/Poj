#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=205;
int stamp[max_n];
int types,require;
int end_comb[4],now[4];
int end_comb_num;
int total;
bool Tie,None;
int get_types(int rec[],int n){
	
	sort(rec,rec+n);
	int res=0;
	if(n>0) res=1;
	for(int i=1;i<n;i++){
		if(rec[i]!=rec[i-1]) res++;
	}
	return res;
}
int get_Max(int rec[],int n){
	int res=-1;
	for(int i=0;i<n;i++) res=max(res,stamp[rec[i]]);
	return res;
}
void dfs(int index,int num,int val){
	if(val>require) return ;
	if(val==require){
		int nowtypes=get_types(now,num);
		int endtypes=get_types(end_comb,end_comb_num);
		int nowMax=get_Max(now,num);
		int endMax=get_Max(end_comb,end_comb_num);
		if(end_comb_num==0||nowtypes>endtypes||(nowtypes==endtypes&&num<end_comb_num)
			||(nowtypes==endtypes&&num==end_comb_num&&nowMax>endMax)){
			None=false;
			Tie=false;
			end_comb_num=num;
			for(int i=0;i<num;i++) end_comb[i]=now[i];
		}
		if(nowtypes==endtypes&&num==end_comb_num&&nowMax==endMax){
			None=false;
			Tie=true;
		}
		return ;
	}
	if(num>=4) return ;
	for(int i=index;i<types;i++){
		now[num]=i;
		dfs(i,num+1,val+stamp[i]);
	}
}
int main(){
	int x;
	while(scanf("%d",&x)!=EOF){
		types=0;
		while(x){
			stamp[types++]=x;
			scanf("%d",&x);
		}
		sort(stamp,stamp+types);
		while(scanf("%d",&require)&&require){
			end_comb_num=0;
			total=0;
			Tie=false;
			None=true;
			dfs(0,0,0);
			if(None){
				printf("%d ---- none\n",require);
			}else{
				if(Tie){
					printf("%d (%d): tie\n",require,get_types(end_comb,end_comb_num));
				}
				else{
					//7 (3): 1 1 2 3
					
					printf("%d (%d):",require,get_types(end_comb,end_comb_num));
					sort(end_comb,end_comb+end_comb_num);
					for(int i=0;i<end_comb_num;i++){
						printf(" %d",stamp[end_comb[i]]);
					}
					printf("\n");
				}
			}
		}
	}	
	return 0;
}
