#include<cstdio>
#include<algorithm>
using namespace std;

const int max_n=5e6+10;
int num[max_n];
int find(int l,int r,int k){
	int mid=num[(l+r)>>1];
	int i=l,j=r-1;
	while(i<=j){
		while(num[i]<mid) i++;
		while(num[j]>mid) j--;
		if(i<=j) swap(num[i],num[j]),i++,j--;
	}
	if(k>=i&&i<r) return find(i,r,k);
	if(k<=j&&j>=l) return find(l,j+1,k);
	return num[k];
}
int main(){
	int n,k;
	scanf("%d %d",&n,&k);
	for(int i=0;i<n;i++) scanf("%d",&num[i]);
	printf("%d\n",find(0,n,k));
	return 0;
}
