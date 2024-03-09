#include<cstdio>
#include<cstring>
const int max_n=2e5+10;
int n,m,a[max_n];
int c[max_n];//c为树状数组
char ch;
inline int max(int a,int b){return a>b?a:b;}//题目要求取大
inline int lowbit(int x){return x&-x;}//lowbit函数：求某一个数的二进制下最低的一位1

void add(int pos,int x){//修改学生的成绩
	a[pos]=x;
	while(pos<=n){
		c[pos]=a[pos];
		int t=lowbit(pos);
		for(int j=1;j<t;j<<=1){
			c[pos]=max(c[pos],c[pos-j]);
		}
		pos+=lowbit(pos);
	}
}
int getmax(int l,int r){//找区间最大值
	int res=0;
	if(!r) return res;
	int i=r;
	while(i>=l){
		int j=i-lowbit(i)+1;
		if(j>=l){
			res=max(res,c[i]);
			i=j-1;
		}
		else{
			res=max(res,a[i]);
			--i;
		}
	}
	return res;
}
int main(){
	scanf("%d%d",&n,&m);
	memset(c,0,sizeof(c));

	for(int i=1;i<=n;i++){
		int l=i-lowbit(i)+1,r=i-1;
		scanf("%d",&a[i]);
		c[i]=max(a[i],getmax(l,r));
	}
	for(int x,y;m;m--){
		ch=getchar();
		while(ch<'A'||ch>'Z') ch=getchar();//小技巧：一个一个地读，读到字母为止
		scanf("%d%d",&x,&y);
		switch(ch){//此处你也可以写成if的形式，应该都差不多
			case 'Q':{
				printf("%d\n",getmax(x,y));
				break;
			}
			case 'U':{
				if(y<=a[x]){
					break;//太高了就不改了
				}
				add(x,y);//改分
				break;
			}
		}
	}
}
