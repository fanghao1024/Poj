#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
#include<iostream>
using namespace std;

char s[8010];
int cal(string str){
	if(str.size()<=1) return 0;
	if(str.size()==2){
		if(str[0]==str[1]) return 0;
		else return -1;
	}
	if(str[0]==str[str.size()-1]) return cal(str.substr(1,str.size()-2));
	int k=str.size()-1;
	while(k>0&&str[0]!=str[k]) k--;
	if(k<=0) return -1;
	//cout<<"1~k-1:"<<str.substr(1,k-1)<<endl;
	//cout<<"k+1~end:"<<str.substr(k+1,str.size()-1-k)<<endl;
	int temp=cal(str.substr(1,k-1)+str.substr(k+1,str.size()-1-k));
	if(temp==-1) return -1;
	else return temp+str.size()-1-k;
}
int main(){
	int n;
	scanf("%d",&n);
	while(n--){
		scanf("%s",s);
		int cnt[30]={0};
		int odd=0,len=strlen(s);
		for(int i=0;i<len;i++) cnt[s[i]-'a']++;
		for(int i=0;i<26;i++) if(cnt[i]&1) odd++;
		if(odd>1) printf("Impossible\n");
		else{
			int ans=0;
			for(int i=0,j=len-1;i<j;i++,j--){
				int l=i,r=j;
				while(l<j&&s[l]!=s[j]) l++;
				while(r>i&&s[r]!=s[i]) r--;
				if(l-i>j-r){
					ans+=j-r;
					for(int k=r;k<j;k++)
						swap(s[k],s[k+1]);
				}else{
					ans+=l-i;
					for(int k=l;k>i;k--)
						swap(s[k],s[k-1]);
				}
			}
			printf("%d\n",ans);
		}
		
	}
	return 0;
}

