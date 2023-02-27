class Node:
    def __init__(self,val):
        self.val=val
        self.nxt=None
    
def main():
    n,m=map(int,input().split())
    head=Node(1)
    now=head
    for i in range(2,n+1):
        newnode=Node(i)
        now.nxt=newnode
        now=now.nxt
    now.nxt=head
    now=head
    for i in range(n-1):
        for j in range(m-1):
            pre=now
            now=now.nxt
        print(now.val,end=' ')
        pre.nxt=now.nxt
        del now
        now=pre.nxt
    print(now.val)
    
if __name__=='__main__':
    main()