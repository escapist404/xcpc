二进制手表顶部有 4 个 LED 代表 小时（0-11），底部的 6 个 LED 代表 分钟（0-59）。每个 LED 代表一个 0 或 1，最低位在右侧。

给你一个整数 `turnedOn` ，表示当前亮着的 LED 的数量，返回二进制手表可以表示的所有可能时间。你可以按任意顺序返回答案。

* 小时不会以零开头：例如，`01:00` 是无效的时间，正确的写法应该是 `1:00`。
* 分钟必须由两位数组成，可能会以零开头：例如，`10:2` 是无效的时间，正确的写法应该是 `10:02`。

---

由于可能的时刻组合非常少（只有 $12 \times 60$），我们可以枚举每种时刻并计算其对应二进制位为 1 的个数。

计算二进制位为 1 的个数，对于 GCC 编译器可考虑使用 `__builtin_popcount()` 函数。

储存答案，对于不需要前缀零的情况，可直接使用 `std::to_string()`；对于需要前缀零的情况，可补齐零，后使用 `std::to_string`，或参见代码。

```cpp
class Solution {
public:
    vector<string> readBinaryWatch(int turnedOn) {
        std::vector<std::string> ret;
        for (int h = 0; h < 12; ++h) {
            for (int m = 0; m < 60; ++m) {
                if (__builtin_popcount(h) + __builtin_popcount(m) == turnedOn) {
                    ret.push_back(std::to_string(h) + ":" + "0123456789"[m / 10] + "0123456789"[m % 10]);
                }
            }
        }
        return ret;
    }
};
```
