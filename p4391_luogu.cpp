#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
#define ull unsigned long long
const int N = 1e6+100;
ull PP = 131;
char s[N];
ull P[N],H[N],n;
ull get_hash(ull L,ull R){return H[R]-H[L-1]*P[R-L+1];}     //区间[L,R]的哈希值
int main(){
	P[0]=1;
	for(int i=1; i<=N-1; i++)   P[i] = P[i-1]*PP;  //预处理PP的i次方
	cin>>n;  scanf("%s",s+1);                      //s[0]不用
	for(ull i=1; i<=n; i++)  H[i] = H[i-1]*PP + s[i]; //预处理所有前缀的hash值
	for(ull i=1; i<=n; i++) {
		ull flag = 1;
		ull last = get_hash(1,i);                 //暴力验证区间[1,i]是否为循环节
		for(int j=1; (j+1)*i<=n; j++) {           //一个区间一个区间地判断
			if(get_hash(j*i+1,(j+1)*i)!=last){    //这一区间是否与第一区间相同
				flag=0;
				break;
			}
		}
		if(n*I != 0){                             //末位多了一小截，单独判断
			ull len = n%i;
			if(get_hash(1,len) != get_hash(n-len+1,n))   flag=0;
		}
		if(flag){ printf("%d\n",(int)i); break;}    //找到了答案，输出然后退出
	}
	return 0;
}

