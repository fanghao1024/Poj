#include<cstdio>
#include<algorithm>
using namespace std;

const int max_n=330;

struct Stu{
    int id;
    int a,b,c;
    int sum;
}stu[max_n];

bool cmp(const Stu& m,const Stu& n){
    if(m.sum!=n.sum) return m.sum>n.sum;
    else if(m.a!=n.a) return m.a>n.a;
    else return m.id<n.id;
}
int N;
int main(){
    scanf("%d",&N);
    for(int i=1;i<=N;i++){
        scanf("%d %d %d",&stu[i].a,&stu[i].b,&stu[i].c);
        stu[i].id=i;
        stu[i].sum=stu[i].a+stu[i].b+stu[i].c;
    }
    sort(stu+1,stu+1+N,cmp);
    for(int i=1;i<=5;i++) printf("%d %d\n",stu[i].id,stu[i].sum);
    return 0;
}