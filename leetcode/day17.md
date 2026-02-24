给出一棵二叉树，其上每个结点的值都是 $0$ 或 $1$ 。每一条从根到叶的路径都代表一个从最高有效位开始的二进制数。

例如，如果路径为 $0 \to 1 \to 1 \to 0 \to 1$，那么它表示二进制数 $01101$，也就是 $13$。

对树上的每一片叶子，我们都要找出从根到该叶子的路径所表示的数字。

返回这些数字之和。题目数据保证答案是一个 32 位整数。

---

在二叉树上进行深度优先遍历，维护当前结点和从根到当前结点的路径代表的二进制数。

仅当当前结点无儿子结点时，当前结点是叶子结点，应当把当前路径代表的数加进答案里，随后遍历左右子树（若存在）。

时间复杂度和空间复杂度均为 $O(n)$。

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
    void findValue(TreeNode* root, int value, int& ans) {
        value = value << 1 ^ root->val;
        if (root->left == nullptr && root->right == nullptr) {
            ans += value;
        }
        if (root->left != nullptr) {
            findValue(root->left, value, ans);
        }
        if (root->right != nullptr) {
            findValue(root->right, value, ans);
        }
    }
    int sumRootToLeaf(TreeNode* root) {
        int ans = 0;
        findValue(root, 0, ans);
        return ans;
    }
};
```
