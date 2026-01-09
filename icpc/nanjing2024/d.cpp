#include <bits/stdc++.h>

int encode(const std::string &s)
{
    int t = 0;
    for (auto i : s)
    {
        t *= 3;
        if (i == 'x')
        {
            t += 1;
        }
        else if (i == 'o')
        {
            t += 2;
        }
    }
    return t;
}

std::string decode(int s)
{
    std::string t = ".........";
    for (int i = 8; i >= 0; --i)
    {
        int v = s % 3;
        s /= 3;
        if (v == 1)
        {
            t[i] = 'x';
        }
        else if (v == 2)
        {
            t[i] = 'o';
        }
    }
    return t;
}
char fu[] = {'x', 'o'};

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
#endif
    std::map<std::pair<int, char>, int> map;

    auto check = [](const std::string &s)
    {
        for (char side : {'x', 'o'})
        {
            if (s[0] == s[3] && s[3] == s[6] && s[0] == side)
            {
                return 1 + (side == 'o');
            }
            if (s[1] == s[4] && s[4] == s[7] && s[1] == side)
            {
                return 1 + (side == 'o');
            }
            if (s[2] == s[5] && s[5] == s[8] && s[2] == side)
            {
                return 1 + (side == 'o');
            }
            if (s[0] == s[1] && s[1] == s[2] && s[0] == side)
            {
                return 1 + (side == 'o');
            }
            if (s[3] == s[4] && s[4] == s[5] && s[3] == side)
            {
                return 1 + (side == 'o');
            }
            if (s[6] == s[7] && s[7] == s[8] && s[6] == side)
            {
                return 1 + (side == 'o');
            }
            if (s[0] == s[4] && s[4] == s[8] && s[0] == side)
            {
                return 1 + (side == 'o');
            }
            if (s[2] == s[4] && s[4] == s[6] && s[2] == side)
            {
                return 1 + (side == 'o');
            }
        }
        return 0;
    };

    std::function<int(std::pair<int, int>)> find = [&](std::pair<int, int> cur_state)
    {
        if (map.count(cur_state))
        {
            return map[cur_state];
        }
        std::string now = decode(cur_state.first);
        int num = check(now);
        if (num)
        {
            // for (int i = 0; i <= 8; i++)
            // {
            //     std::cout << now[i];
            //     if (i % 3 == 2)
            //         std::cout << '\n';
            // }
            // std::cout <<fu[cur_state.second]<<' '<< 1 << '\n';
            return map[cur_state] = 1;
        }
        std::vector<int> e;
        e.push_back(-1);
        for (int i = 0; i <= 8; i++)
        {
            if (now[i] == '.')
            {
                now[i] = fu[cur_state.second];
                e.push_back(find(std::make_pair(encode(now), cur_state.second ^ 1)));
                now[i] = '.';
            }
        }
        sort(e.begin(), e.end());
        int shu = e[e.size() - 1] + 1;
        for (int i = 0; i < e.size() - 1; i++)
            if (e[i] + 1 != e[i + 1])
            {
                shu = e[i] + 1;
                break;
            }
        // for (int i = 0; i <= 8; i++)
        // {
        //     std::cout << now[i];
        //     if (i % 3 == 2)
        //         std::cout << '\n';
        // }
        // std::cout << fu[cur_state.second] << ' ' << shu << std::endl;
        return map[cur_state] = shu;
    };

    int tt;
    std::cin >> tt;

    auto solve = [&]()
    {
        int n;
        std::cin >> n;

        std::vector<int> b(n);
        std::string c1, c2, c3;
        int ans = 0;
        for (int i = 0; i < n; ++i)
        {
            std::cin >> c1 >> c2 >> c3;
            c1 += c2, c1 += c3;
            b[i] = encode(c1);
            int shu =  find(std::make_pair(b[i], 0));
            std::cout<<shu<<' ';
            ans ^= shu;
        }
        // std::cout<<ans<<' ';
        if (!ans)
            puts("Bob");
        else
            puts("Alice");
    };

    while (tt--)
    {
        solve();
    }

    return 0;
}