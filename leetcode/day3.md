给你一个整数数组 `nums`。

如果子数组中不同偶数的数量等于不同奇数的数量，则称该子数组是平衡的。

返回最长平衡子数组的长度。

子数组是数组中连续且非空的一段元素序列。

保证 `nums.size()` 不超过 $1500$，数组中元素都是不超过 $100000$ 的正整数。

---

考虑到数组长度很小，记 $n$ 为 `nums.size()`，直接枚举 $O(n^2)$ 个区间，用 $O(n)$ 的时间判断单个区间是否合法，时间复杂度为 $O(n^3)$，不可接受。

发现如果固定左端点，扩展右端点时，可以利用先前的区间快速得到当前区间的合法性：维护哪些数已经出现，加入一个数，如果这个数是第一次出现，则记录其奇偶性。当奇数和偶数个数相同时，更新答案。

维护哪些数已经出现，可以使用哈希表或桶。使用桶时不能反复 `assign(V + 1, 0)`，而应遍历刚刚加入的数进行删除。

时间复杂度 $O(n^2)$，空间复杂度 $O(n + V)$，$V$ 为值域。

```cpp
class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        std::vector<int> cnt(100001);
        int ans = 0;
        int n = nums.size();
        for (int l = 0; l < n; ++l) {
            int par[] = {0, 0};
            for (int r = l; r < n; ++r) {
                if (cnt[nums[r]] == 0) {
                    par[nums[r] & 1]++;
                }
                cnt[nums[r]]++;
                if (par[0] == par[1]) {
                    ans = std::max(ans, r - l + 1);
                }
            }
            for (int r = l; r < n; ++r) {
                --cnt[nums[r]];
            }
        }
        return ans;
    }
};
```

