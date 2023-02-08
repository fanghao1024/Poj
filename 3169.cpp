#include<stdio.h>

const int max_n=10010;
int AL[max_n],BL[max_n],DL[max_n];
int AD[max_n],BD[max_n],DD[max_n];
int d[max_n];
const int INF=0x3fffffff;
int main(){
	int N,ML,MD;
	scanf("%d %d %d",&N,&ML,&MD);
	for(int i=0;i<ML;i++){
		scanf("%d %d %d",&AL[i],&BL[i],&DL[i]);
	}
	for(int i=0;i<MD;i++){
		scanf("%d %d %d",&AD[i],&BD[i],&DD[i]);
	}
	for(int i=1;i<N;i++){
		d[i]=INF;
	}
	d[0]=0;
	for(int i=0;i<N;i++){
		//d[i+1]>=d[i]
		for(int i=0;i<N-1;i++){
			if(d[i+1]<INF){
				d[i]=d[i+1]<d[i]?d[i+1]:d[i];
			}
		}
		for(int i=0;i<ML;i++){
			if(d[AL[i]-1]<INF){
				d[BL[i]-1]=d[BL[i]-1]<d[AL[i]-1]+DL[i]?d[BL[i]-1]:d[AL[i]-1]+DL[i];
			}
		}
		for(int i=0;i<MD;i++){
			if(d[BD[i]-1]<INF){
				d[AD[i]-1]=d[AD[i]-1]<d[BD[i]-1]-DD[i]?d[AD[i]-1]:d[BD[i]-1]-DD[i];
			}
		}
		
	}
	int ans=d[N-1];
	if(d[0]<0){
		ans=-1;
	}else{
		if(ans==INF){
			ans=-2;
		}
	}
	printf("%d\n",ans);
	return 0;
}
