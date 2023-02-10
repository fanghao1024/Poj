#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=2*1024*1024+10;
char s[max_n],ops[20];
int cnt;
struct Tr{
	int ls,rs;
	int size;
	char val;
	int num;
}tr[max_n<<1];
int T,pos;
int main(){
	scanf("%d",&T);
	pos=1;
	cnt=1;
	while(T--){
		scanf("%s",ops);
		switch (ops[0]) {
		case 'M':
			//TODO
			break;
		case 'I':
			//TODO
			break;
		case 'D':
			//TODO
			break;
		case 'G':
			break;
		case 'P':
			break;
		case 'N':
			break;
		}
	}
	return 0;
}
