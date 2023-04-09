#include<cstdio>
#include<cstring>

char s1[250],s2[250];

int main(){
    scanf("%s",s1);
    scanf("%s",s2);
    int ans=0;
    for(int i=0;i<strlen(s1);i++){
        for(int j=1;j<strlen(s2);j++){
            if(s1[i]==s2[j]&&s1[i+1]==s2[j-1]) ans++;
        }
    }
    printf("%d\n",1<<ans);
    return 0;
}