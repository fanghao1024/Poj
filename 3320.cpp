#include<stdio.h>
#include<set>
#include<map>
using namespace std;

int num[1000010];
int main(){
	int P;
	scanf("%d",&P);
	set<int> ss;
	for(int i=0;i<P;i++){
		scanf("%d",&num[i]);
		ss.insert(num[i]);
	}
	int s=0,t=0,min_len=P;
	int record=0;
	int lens=ss.size();
	map<int,int> mp;
	for(;;){
		while(t<P&&record<lens){
			record+=(mp[num[t++]]++==0);
		}
		if(record<lens) break;
		min_len=min_len<(t-s)?min_len:(t-s);
		record-=(--mp[num[s++]]==0);
		
	}
	printf("%d\n",min_len);
	return 0;
}
