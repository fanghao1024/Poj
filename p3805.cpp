#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=11e6+10;

char a[max_n];
char b[max_n<<1];
int p[max_n<<1];
int n;
void change(){
	n=strlen(a);
	int k=0;
	b[k++]='$';b[k++]='#';
	for(int i=0;i<n;i++) b[k++]=a[i],b[k++]='#';
	b[k++]='&';
	n=k;
}
void manacher(){
	int R=0,c;
	for(int i=1;i<n;i++){
		if(i<R) p[i]=min(p[(c<<1)-i],c+p[c]-i);
		else p[i]=1;
		while(b[i+p[i]]==b[i-p[i]]) p[i]++;
		if(i+p[i]>R){
			R=i+p[i];
			c=i;
		}
	}
}
int main(){
	scanf("%s",a);
	change();
	manacher();
	int ans=0;
	for(int i=1;i<n;i++) ans=max(ans,p[i]);
	printf("%d\n",ans-1);
	return 0;
}
