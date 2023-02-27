#include<cstdio>
#include<algorithm>
using namespace std;

const int max_n=1e6+10;

int heap[max_n],len;

void push(int x){
	heap[++len]=x;
	int i=len;
	while(i>1&&heap[i]<heap[i/2]){
		swap(heap[i],heap[i/2]);
		i=i/2;
	}
}
void pop(){
	heap[1]=heap[len--];
	int i=1;
	while(2*i<=len){
		int son=i*2;
		if(son<len&&heap[son+1]<heap[son])
			son+=1;
		if(heap[son]<heap[i]) swap(heap[son],heap[i]),i=son;
		else break;
	}
}
int main(){
	int n,ops,x;
	len=0;
	scanf("%d",&n);
	while(n--){
		scanf("%d",&ops);
		switch (ops) {
		case 1:
			scanf("%d",&x);
			push(x);
			break;
		case 2:
			printf("%d\n",heap[1]);
			break;
		case 3:
			pop();
			break;
		}
	}
	return 0;
}
