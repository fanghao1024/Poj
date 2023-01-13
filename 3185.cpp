#include<stdio.h>

int rec[20];
bool flip[20];
int main(){
	for(int i=0;i<20;i++) scanf("%d",&rec[i]);
	int res=20;
	for(int iii=0;iii<2;iii++){
		flip[0]=iii;
		for(int i=1;i<20;i++){
			if(i==1){
				flip[i]=(flip[0]+rec[0])%2;
			}else{
				flip[i]=(flip[i-2]+flip[i-1]+rec[i-1])%2;
			}
		}
		int ans=0;
		for(int i=0;i<20;i++){
			ans+=flip[i];
		}
		res=res<ans?res:ans;
	}
	printf("%d\n",res);
	return 0;
}

