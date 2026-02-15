[Link](https://leetcode.cn/problems/champagne-tower/description/)

我们把玻璃杯摆成金字塔的形状，其中第一层有 $1$ 个玻璃杯，第二层有 $2$ 个，依次类推到第 $100$ 层，每个玻璃杯将盛有香槟。

从顶层的第一个玻璃杯开始倾倒一些香槟，当顶层的杯子满了，任何溢出的香槟都会立刻等流量的流向左右两侧的玻璃杯。当左右两边的杯子也满了，就会等流量的流向它们左右两边的杯子，依次类推。（当最底层的玻璃杯满了，香槟会流到地板上）

现在当倾倒了非负整数杯香槟后，返回第 $i$ 行 $j$ 个玻璃杯所盛放的香槟占玻璃杯容积的比例（ $i$ 和 $j$ 都从 $0$ 开始）。

实现 `double champagneTower(int poured, int query_row, int query_glass);`，其中 `poured` 代表倾倒的香槟杯数，`query_row` 代表询问的玻璃杯行的编号，`query_glass` 代表询问的玻璃杯处于该行的编号。

保证倾倒香槟杯数不超过 $10^9$，询问杯子的行编号不超过 $100$。

---

我们可以假定所有的杯子都是无限大的。由于行与行之间的杯子只会从高到低影响，我们可以先把所有的香槟装到 $0$ 行的杯子，之后逐行恢复杯子的容量限制，模拟香槟向左右的杯子流动的过程。

时间复杂度 $O(n^2)$。利用行之间的影响是相邻的这一性质，求第 $i$ 行的情况时，只需要知道 $i - 1$ 行的情况，我们用滚动数组优化空间。空间复杂度 $O(n)$，$n$ 为行数。

[AC Link](https://leetcode.cn/problems/champagne-tower/submissions/698671225/)

```cpp
class Solution {
public:
    double champagneTower(int poured, int query_row, int query_glass) {
        vector<double> glass(1);
        glass[0] = poured;
        for (int i = 0; i < query_row; ++i) {
            vector<double> next_glass(i + 2);
            for (int j = 0; j <= i; ++j) {
                double r = glass[j] - 1.0;
                if (r > 0) {
                    next_glass[j] += r / 2;
                    next_glass[j + 1] += r / 2;
                }
            }
            glass = move(next_glass);
        }
        return min(1.0, glass[query_glass]);
    }
};

```
