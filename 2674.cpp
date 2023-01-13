#include<stdio.h>
#include<cmath>

const int max_n=32005;
char name[max_n][300];
char dir[max_n];
double pos[max_n];
double L,V;
int main(){
	int N;
	while(scanf("%d",&N)!=EOF){
		if(N==0) break;
		scanf("%lf %lf",&L,&V);
		for(int i=0;i<N;i++){
			scanf(" %c %lf %s",&dir[i],&pos[i],name[i]);
		}
		double ans=-1;
		double t;
		int left=0;
		char d;
		for(int i=0;i<N;i++){
			switch (dir[i]) {
			case 'p':
				t=(L-pos[i])/V;
				break;
			case 'P':
				t=(L-pos[i])/V;
				break;
			case 'n':
				t=pos[i]/V;
				left++;
				break;
			case 'N':
				t=pos[i]/V;
				left++;
				break;
			}
			if(ans<t){
				ans=t;
				d=dir[i];
			}
		}
		printf("%13.2f ",int(ans*100)/100.0);
		if(d=='p'||d=='P'){
			printf("%s\n",name[left]);
			
		}else{
			printf("%s\n",name[left-1]);
		}
	}
	return 0;
}
