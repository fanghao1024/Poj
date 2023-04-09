#include<cstdio>
#include<cstring>

char s1[20],s2[20];

struct Tree{
    char ch;
    int l,r;
}tree[20];
void build(int p,int l1,int r1,int l2,int r2){
    char c=s2[r2];
    tree[p].ch=c;
    tree[p].l = tree[p].r = 0;
    if(l1==r1){
        return ;
    }
    int pos;
    for(int i=l1;i<=r1;i++){
        if(s1[i]==c){
            pos=i;
            break;
        }
    }
    if(pos>l1){
        tree[p].l=2*p;
        build(2*p,l1,pos-1,l2,l2+pos-l1-1);
    }
    if(r1>pos){
        tree[p].r=2*p+1;
        build(2 * p + 1, pos + 1, r1, l2 + pos - l1,r2-1);
    }
}
void Print(int p){
    printf("%c",tree[p].ch);
    if(tree[p].l) Print(tree[p].l);
    if(tree[p].r) Print(tree[p].r);
}
int main(){
    scanf("%s",s1);
    scanf("%s",s2);
    int len=strlen(s1);
    build(1,0,len-1,0,len-1);
    Print(1);
    printf("\n");
    return 0;
}