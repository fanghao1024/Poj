#include<stdio.h>
#include<algorithm>
using namespace std;

typedef long long ll;
ll absll(ll a){
	if(a<0) a*=-1;
	return a;
}
struct Info{
	ll value;
	int count;
	Info(){};
	Info(ll v,int c){this->value=v;this->count=c;}
	bool operator<(const Info& temp) const{
		if(this->value!=temp.value){
			return this->value<temp.value;
		}else{
			return this->count<temp.count;
		}
	}
};
bool cmp(const Info& a,const Info& b){
	if(a.value!=b.value){
		return a.value<b.value;
	}else{
		return a.count<b.count;
	}
}
ll num[40];

Info record[(1<<18)+10];
int main(){
	int N;
	while(scanf("%d",&N)){
		if(!N) break;
		for(int i=0;i<N;i++) scanf("%lld",&num[i]);
		if(N==1){
			printf("%lld 1\n",num[0]);
			continue;
		}
		int N1=N/2,N2=N-N1;
		for(int i=0;i<(1<<N1);i++){
			ll sums=0;
			int counts=0;
			for(int j=0;j<N1;j++){
				sums+=((i>>j)&1)*num[j];
				counts+=(i>>j)&1;
			}
			record[i]=Info(sums,counts);
		}
		sort(record,record+(1<<N1));
		
		ll min_value;
		int min_counts;
		for(int i=0;i<(1<<N2);i++){
			if(i==0){
				Info temp=*lower_bound(record,record+(1<<N1),Info(0,0),cmp);
				//printf("~~~~%lld %d\n",temp.value,temp.count);
				if(temp.value==0&&temp.count==0){
					temp=*(lower_bound(record,record+(1<<N1),Info(0,0),cmp)+1);
				}
				if(lower_bound(record,record+(1<<N1),Info(0,0),cmp)-record>0){
					Info temp1=*(lower_bound(record,record+(1<<N1),Info(0,0),cmp)-1);
					//printf("%lld %d====%lld %d\n",temp.value,temp.count,temp1.value,temp1.count);
					if(absll(temp.value)>absll(temp1.value)){
						temp=temp1;
					}
				}
				min_value=absll(temp.value);
				min_counts=temp.count;
				continue;
			}
			ll sums=0;
			int counts=0;
			for(int j=0;j<N2;j++){
				sums+=((i>>j)&1)*num[j+N1];
				counts+=(i>>j)&1;
			}
			Info temp=*lower_bound(record,record+(1<<N1),Info(-sums,0),cmp);
			
			if(lower_bound(record,record+(1<<N1),Info(-sums,counts),cmp)-record>0){
				Info temp1=*(lower_bound(record,record+(1<<N1),Info(-sums,0),cmp)-1);
				if(absll(temp.value+sums)>absll(temp1.value+sums)){
					temp=temp1;
				}
			  }
			//printf("===%lld\n",abs(temp.value+sums));
			if(min_value>absll(temp.value+sums)){
				//printf("~~~%d\n",i);
				//printf("-----#%lld %lld\n",temp.value,sums);
				min_value=absll(temp.value+sums);
				min_counts=temp.count+counts;
			}
			if((min_value==absll(temp.value+sums))&&min_counts>temp.count+counts){
				min_value=absll(temp.value+sums);
				min_counts=temp.count+counts;
			}
		}
		printf("%lld %d\n",min_value,min_counts);
	}
	return 0;
}
