#include<cstdio>

const int max_n=1e5+100;

int num[max_n],st[max_n],ans[max_n];
int N;
int main(){
    scanf("%d",&N);
    for(int i=1;i<=N;i++) scanf("%d",&num[i]);
    int f=-1;
    for(int i=1;i<=N;i++){
        while(f>=0&&num[i]>num[st[f]]){
            ans[st[f]]=i;
            f--;
        }
        st[++f]=i;
    }
    while(f>=0) ans[st[f--]]=0;
    for(int i=1;i<=N;i++) printf("%d\n",ans[i]);
    return 0;
}