import sys
s=''
stack = []
ans = -1
n = 0
def dfs(dep, summ, t, k, lst):
    global ans
    if (dep == 0):
        if summ != n:
            return
        sum = 0
        sum1 = 0
        for i in range(k):
            sum += int(s[sum1 : sum1 + stack[i]])
            sum1 += stack[i]
        if(ans == -1):
            ans = sum
        elif ans > sum:
            ans = sum  
        return
    for i in range(max(t - 1, 1), t + 2):
        summ+=i
        if abs(i-lst)>1:
            summ-=i
            continue
        if(summ+(dep-1)*(max(t-1,1))>n):
            summ-=i
            break
        if(summ+(dep-1)*(t+1)<n):
            summ-=i
            continue
        stack.append(i)
        dfs(dep-1,summ,t,k,i)
        stack.pop()
        summ-=i
    return
if __name__=='__main__':
    sys.set_int_max_str_digits(0)
    T=int(sys.stdin.readline())
    for id in range(T):
        n, k = [int(_) for _ in sys.stdin.readline().split()]
        k=k+1
        ans=-1
        stack=[]
        s = sys.stdin.readline()
        t=n//k
        t1=n%k
        dfs(k,0,t,k,t)
        dfs(k,0,t+1,k,t+1)
        sys.stdout.write(f"{ans}\n")

