#include<stdio.h>
#include<set>
using namespace std;

int Ma,RL;
multiset<int> ms;
int Qrec[1005];
int main(){
	while(scanf("%d %d",&Ma,&RL)!=EOF){
		ms.clear();
		for(int i=0;i<RL;i++){
			scanf("%d",&Qrec[i]);
		}
		char ch;
		int p=1;
		int x;
		int cnt=0;
		int index=0;
		while(scanf(" %c",&ch)){
			if(ch=='e') break;
			switch (ch) {
			case 'a':
				scanf("%d",&x);
				ms.insert(x);
				break;
			case 'r':
				cnt++;
				if(ms.empty()){
					if(cnt==Qrec[index]){
						printf("-1\n");
						index++;
					}	
				}else{
					int ele;
					if(p==1){
						ele=*ms.begin();
						ms.erase(ms.begin());
					}else{
						multiset<int>::iterator it=ms.end();
						it--;
						ele=*it;
						ms.erase(it);
					}
					if(cnt==Qrec[index]){
						printf("%d\n",ele);
						index++;
					}
				}
				
				break;
			case 'p':
				scanf("%d",&x);
				p=x;
				break;
			}
		}
		printf("\n");
	}
	
	return 0;
}
