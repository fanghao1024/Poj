#include<string>
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
char s1[16],s2[1000010];
void tolower(char *a){//全部大写转小写
	for(int i=0;a[i];i++)
		if(a[i]>='A'&&a[i]<='Z')
			a[i]+=32;
}

int bf(char* a,char* b,int s){
	int i=s;
	int j=0;
	while(a[i]!='\0'&&b[j]!='\0'){
		if(a[i]==b[j]){
			i++;
			j++;
		}
		else{
			j=0;
			i=i-j+1;
		}
	}
	if(b[j]=='\0') return i-j+1;
	return -1;
	
}
int main(){
	cin.getline(s1+1,15);
	cin.getline(s2+1,1000009);
	s1[0]=' ';
	int ls1=strlen(s1);
	s1[ls1]=' ';
	s1[ls1+1]='\0';
	s2[0]=' ';
	int ls2=strlen(s2);
	s2[ls2]=' ';
	s2[ls2+1]='\0';
	tolower(s1);
	tolower(s2);
	int ans1,ans2;
	ans1=bf(s2,s1,0);
	if(ans1==-1){
		printf("-1\n");
	}else{
		ans2=0;
		int index=ans1+1;
		while(index!=-1){
			ans2++;
			index=bf(s2,s1,index);
		}
		printf("%d %d\n",ans2,ans1-1);
	}
	
	return 0;
}
