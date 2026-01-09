// what is matter? never mind. 
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
//#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,avx2")
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(int i=(a);i>=(b);--i)
#define ll long long
#define ull unsigned long long
#define int long long
#define SZ(x) ((int)((x).size()))
#define ALL(x) (x).begin(),(x).end()
using namespace std;
inline int read()
{
	char c=getchar();int x=0;bool f=0;
	for(;!isdigit(c);c=getchar())f^=!(c^45);
	for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
	return f?-x:x;
}

#define fi first
#define se second
#define pb push_back
#define mkp make_pair
typedef pair<int,ll>pii;
typedef vector<int>vi;

#define maxn 2000005
#define inf 0x3f3f3f3f

typedef double db;
const db eps=1e-8,pi=3.14159265358979323846;

int a,b;
int res;
int calc(int a,int b){
    int res=0;
    while(a>0 && b>0){
        while(a%2==0 && b%2==0) a/=2,b/=2;
        if(a%2) a-=__gcd(a,b);
        else b-=__gcd(a,b);
        ++res;
    }
    if(a>0 || b>0) ++res;
    return res;
}

void dfs(int a,int b,int u){
    if(u>=res) return;
    if(!a && !b){
        res=min(res,u);
        return;
    }
    dfs(a-__gcd(a,b),b,u+1);
    dfs(a,b-__gcd(a,b),u+1);
}

void work()
{
    cin>>a>>b;
    res=calc(a,b);
    dfs(a,b,0);
    cout<<res<<"\n";
}

signed main()
{
    
    int T;
    cin>>T;
    while(T--)work();
	return 0;
}
/*
[li,ri]
*/