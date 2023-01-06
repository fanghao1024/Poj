#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<iostream>
using namespace std;
		
struct Stick{
	int l;
	int w;
}stick[5010];
bool used[5010];
bool cmp(const Stick& a,const Stick &b){
	if(a.l!=b.l){
		return a.l<b.l;
	}else{
		return a.w<b.w;
	}
}
int main(){
	int n,T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=0;i<n;i++){
			cin>>stick[i].l>>stick[i].w;
			
		}
		sort(stick,stick+n,cmp);
		
		memset(used,0,sizeof(used));
		int ans=0;
		int sl,sw;
		sl=stick[0].l;
		sw=stick[0].w;
		used[0]=1;
		int i,j;
		ans=1;
		for(i=1;i<n;i++){
			for(j=i;j<n;j++){
				if(!used[j]&&stick[j].l>=sl&&stick[j].w>=sw){
					used[j]=1;
					sl=stick[j].l;
					sw=stick[j].w;
				}
			}
			
			j=1;
		
			while(used[j]){
				j++;
			}
			if(j==n){
				break;
			}
			i=j;
			sl=stick[i].l;
			sw=stick[i].w;
			used[i]=1;
			ans++;
		}
		cout<<ans<<endl;
	}
	return 0;
}
