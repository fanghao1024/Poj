#include<cstdio>
#include<cstring>

char ch[20000];

int main(){
    int n;
    scanf("%d",&n);
    while(n--){
        scanf("%s",ch);
        int i=0;
        int j=strlen(ch)-1;
        bool flag=true;
        while(i<=j){
            if(ch[i]!=ch[j]){
                flag=false;
                break;
            }
            i++,j--;
        }
        if(flag) printf("yes\n");
        else printf("no\n");
    }
    return 0;
}
