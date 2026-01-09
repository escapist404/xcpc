#include <bits/stdc++.h>
#define maxn 600010
using i64 = long long;
using namespace std;
int vis[maxn];
void solve() {
    int n;
    std::cin >> n;
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        int x;
        cin>>x;
        if(vis[x])
            vis[x-1]=1;
        else
            ans++,vis[x-1]=1;
    }
    for(int i=0;i<=n;i++)
        vis[i]=0;
    std::cout << ans << "\n";
}

int main() {
#ifndef ONLINE_JUDGE
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}