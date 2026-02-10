给定一个二叉树，判断它是否是*平衡二叉树*。

平衡二叉树：所有结点的左右子树高度差不超过 $1$。

结点数 $n$ 满足 $0 \le n \le 5000$。

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool isBalanced(TreeNode* root) {

    }
};
```

### 解答

#### 思路

树结构有良好的递归性质。我们可以递归地进行判断：一棵树是平衡二叉树，仅当其左右子树都是平衡二叉树，且左右子树的高度差不超过 $1$。

预置变量 `height` 保存子树高度。每次调用 `isBalanced(root)` 后，变量 `height` 保存 `root` 子树高度。

调用 `isBalanced(root)` 时：

* 递归调用 `isBalanced(root->left)`。
* 保存左子树高度 `left_height = height`。
* 递归调用 `isBalanced(root->right)`。
* 保存右子树高度 `right_height = height`。
* 判断当前结点子树是否平衡 `abs(left_height - right_leight) <= 1`。
* 计算子树高度 `height = std::max(left_height, right_height) + 1`。
* 返回结果，要求左右子树内所有结点都平衡，且当前子树平衡。

若调用 `isBalanced(nullptr)`，则结果为 `true`，并置 `height = 0`。

#### 代码

```cpp
class Solution {
public:
    int height;
    bool isBalanced(TreeNode* root) {
        if (root == nullptr) {
            height = 0;
            return true;
        }
        bool ok = true;
        ok &= isBalanced(root->left);
        int left_height = height;
        ok &= isBalanced(root->right);
        int right_height = height;
        ok &= abs(left_height - right_height) <= 1;
        height = std::max(left_height, right_height) + 1;
        return ok;
    }
    Solution() : height(0) {}
};
```

[AC Link](https://leetcode.cn/problems/balanced-binary-tree/submissions/697217968/)

#### 复杂度分析

* 时间复杂度为 $O(n)$，每个结点只需访问 $1$ 次。
* 空间复杂度为 $O(n)$，只需保存树结构。

#### 短路优化

上述代码耗时约为 3ms，可以些微优化代码常数。

我们对多个表达式进行 AND 运算时，会采用短路原则：发现有一个表达式为 `false` 时，不再看剩余表达式，直接返回 `false`。

若变量 `ok` 的值已经为 `false`，则无需继续访问剩下的结点，直接返回 `false` 即可。

此时代码耗时约为 0ms，空间消耗也些微减小。

[AC Link](https://leetcode.cn/problems/balanced-binary-tree/submissions/697219168/)
