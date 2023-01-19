#include<stdio.h>
#include<deque>
using namespace std;

deque<int> D[150005];
int N,Q;

void read(int &x){
	char ch = getchar();x = 0;
	for (; ch < '0' || ch > '9'; ch = getchar());
	for (; ch >='0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
}

int main(){
	while(scanf("%d %d",&N,&Q)!=EOF){
		for(int i=1;i<=N;i++) D[i].clear();
		int a,b,c,d;
		while(Q--){
			read(a);
			switch (a) {
			case 1:
				read(b);read(c);read(d);
				if(c==0){
					D[b].push_front(d);
				}else{
					D[b].push_back(d);
				}
				break;
			case 2:
				read(b);read(c);
				if(!D[b].empty()){
					if(c==0){
						printf("%d\n",D[b].front());
						D[b].pop_front();
					}else{
						printf("%d\n",D[b].back());
						D[b].pop_back();
					}
				}else{
					printf("-1\n");
				}
				
				break;
			case 3:
				read(b),read(c);read(d);
				if(d==0){
					D[b].insert(D[b].end(),D[c].begin(),D[c].end());
				}else{
					D[b].insert(D[b].end(),D[c].rbegin(),D[c].rend());
				}
				D[c].clear();
				break;
			}
		}
	}
	return 0;
}
