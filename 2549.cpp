#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;


typedef pair<int,int> P;
const int max_n=1010;
int num[max_n];
bool cmp(const P& a,const P& b){
	if(a.first!=b.first){
		return a.first<b.first;
	}else{
		return a.second<b.second;
	}
}
int main(){
	int N;
	while(scanf("%d",&N)){
		if(!N) break;
		for(int i=0;i<N;i++) scanf("%d",&num[i]);
		vector<P> vp;
		for(int i=0;i<N;i++){
			for(int j=i+1;j<N;j++){
				vp.push_back(make_pair(num[i]+num[j],(1<<i)+(1<<j)));
			}
		}
		sort(vp.begin(),vp.end());
		bool flag=false;
		int d;
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				if(i!=j){
					int dif=num[i]-num[j];
					P p=*lower_bound(vp.begin(),vp.end(),make_pair(-dif,0));
					if(p.first==-dif){
						if((p.second&((1<<i)+(1<<j)))==0){
							if(flag==false){
								d=num[j];
								flag=true;
							}else{
								if(num[j]<d) d=num[j];
							}
						}else{
							int addr=lower_bound(vp.begin(),vp.end(),make_pair(-dif,0),cmp)-vp.begin()+1;
							for(;vp[addr].first==-dif;addr++){
								if((vp[addr].second&((1<<i)+(1<<j)))==0){
									if(flag==false){
										d=num[j];
										flag=true;
									}else{
										if(num[j]<d) d=num[j];
									}
									break;
								}
							}
						}
					}
				}
			}
		}
		if(flag){
			printf("%d\n",d);
		}else{
			printf("no solution\n");
		}
	}
	return 0;
}
