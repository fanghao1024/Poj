N=105

num=[[0]*N for _ in range(N)]

for i in range(1,101):
    num[i][i]=num[i][1]=1
    for j in range(2,101):
        num[i][j]=num[i-1][j-1]+j*num[i-1][j]

while True:
    try:
        n,k=map(int,input().split())
        print(num[n][k])
    except EOFError:
        break