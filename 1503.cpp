#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;

const int limit=1e8;
struct BigNum{
    int num[1260];
    int top;
    BigNum(){
        memset(num,0,sizeof(num));
        top=0;
    }
};

void setV(BigNum& x,char* s){
    int len=strlen(s);
    int p;
    int ten=1;
    memset(x.num,0,sizeof(x.num));
    for(int i=len-1;i>=0;i--){
        p=(len-1-i)/8;
        x.num[p]+=(s[i]-'0')*ten;
        ten*=10;
        if(ten>=limit) ten=1;
    }
    x.top=p;
}
void Print(BigNum x){
    for(int i=x.top;i>=0;i--){
        if(i==x.top) printf("%d",x.num[i]);
        else{
            printf("%08d",x.num[i]);
        }
    }
}
void copyV(BigNum a,BigNum& b){
    b.top=a.top;
    memset(b.num,0,sizeof(b.num));
    for(int i=0;i<=a.top;i++) b.num[i]=a.num[i];
}
void addV(BigNum a,BigNum b,BigNum& c){
    int l1=a.top,l2=b.top;
    int l=max(l1,l2);
    memset(c.num,0,sizeof(c.num));
    int jinwei=0;
    int sum;
    for(int i=0;i<=l;i++){
        sum=a.num[i]+b.num[i]+jinwei;
        c.num[i]=sum%limit;
        jinwei=sum/limit;
    }
    if(jinwei>0){
        l++;
        c.num[l]=jinwei;
    }
    c.top=l;
}

int main(){
    BigNum a,b,c;
    char ch[120];
    while (scanf("%s", ch) != EOF && strcmp(ch, "0") != 0)
    {
        setV(a,ch);
        addV(a,b,c);
        copyV(c,b);
    }
    Print(c);
    printf("\n");
    return 0;
}
