#include<bits/stdc++.h>
using namespace std;

const int maxn = 1e6+10;
const int inf = 1e9;

int n,m,k,w,ans;
int vis[maxn];
int a[maxn];
int f[maxn];

int calc(int n){
    // for(int i=1;i<=n;i++)
    //     cout<<a[i]<<' ';cout<<endl;
    int flag = 0;
    for(int i=1;i<k;i++){
        flag|=a[i];
        if(!flag)
            f[i] = 0;
        else f[i] = inf;
    }
    for(int i=k;i<=n;i++){
        flag = 0;
        for(int j=i-k+1;j<=i;j++)
            flag|=a[j];
        f[i] = f[i-k]+flag;
    }
    // cout<<f[n]<<endl;
    return f[n];
}

void solve(){
    ans = 0;
    cin>>n>>m>>k>>w;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        vis[x] = 1;
    }
    for(int i=1;i<=m;i++){
        int x;
        cin>>x;
        vis[x] = 2;
    }
    vis[0] = 2,vis[w+1] = 2;
    int lst = 0;
    for(int i=1;i<=w+1;i++){
        if(vis[i]==2){
            // cout<<lst<<' '<<i<<endl;
            for(int j=lst+1;j<i;j++)
                a[j-lst] = vis[j];
            ans+=calc(i-lst-1);
            lst = i;
        }
    }
    if(ans>inf)
        cout<<"-1\n"; 
    else
        cout<<ans<<'\n';
    for(int i=1;i<=w;i++)
        vis[i] = a[i] = f[i] = 0;
}

signed main(){
    #ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
    #endif
    int T;
    cin>>T;
    while(T--)solve();
}