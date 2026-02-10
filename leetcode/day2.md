给你一棵二叉搜索树，请你返回一棵**平衡后**的二叉搜索树，新生成的树应该与原来的树有着相同的节点值。如果有多种构造方法，请你返回任意一种。

如果一棵二叉搜索树中，每个节点的两棵子树高度差不超过 $1$，我们就称这棵二叉搜索树是**平衡的**。

结点数 $n$ 满足 $1 \le n \le 10^4$。

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
    TreeNode* balanceBST(TreeNode* root) {
        
    }
};
```

---

我们知道二叉搜索树的性质是：任意结点左子树上的所有节点值均小于该结点值，右子树上的所有结点值均大于该结点值。

考虑到这一点，不难想到用中序遍历（左子树 - 根结点 - 右子树）的顺序遍历二叉搜索树，并保存依次访问到的权值到一个临时数组。这样得到的临时数组一定是升序的。

得到升序的数组后，利用其构造平衡二叉树。平衡二叉树的高度差不超过 $1$，因此我们希望每个结点的左右子树大小相差不大。

考虑这样分配左右子树：当前数组为 $\left[a_0, a_1, \cdots, a_{n-1}\right]$，将 $a_{\lfloor n / 2 \rfloor}$ 作为根结点，较小的数构成的数组 $\left[a_0, a_1, \cdots, a_{\lfloor n / 2 \rfloor - 1}\right]$ 作为左子树对应权值，较大的数构成的数组 $\left[a_{\lfloor n / 2 \rfloor + 1}, a_{\lfloor n / 2 \rfloor + 2}, \cdots, a_{n - 1}\right]$ 作为右子树对应权值。上述数组若不存在，则对应子树为空。

这样的方式比较符合直觉，接下来证明其正确性。

先证明这样的二叉树是二叉搜索树。从上述的构造方式来看，这是显然的。

再证明，这棵二叉搜索树是平衡的。只考虑剩下的数的个数，记 $h_{i}$ 为有 $i$ 个数时树的高度。

显然，$h_{0} = 0$，且 $n \ge 1$ 有递推式：

$$
h_{n} = \max \left( h_{\lfloor n / 2 \rfloor}, h_{n - 1 - \lfloor n / 2 \rfloor} \right) + 1
$$

考虑到 $\lceil \left(n - 1\right) / 2 \rceil = \lfloor n / 2 \rfloor$，则上式可改写为：

$$
h_{n} = \max \left( h_{\lceil \left(n - 1\right) / 2 \rceil}, h_{\lfloor \left(n - 1\right) / 2 \rfloor} \right) + 1
$$

对此我们指出，$h_{n} = \lceil \log_2{\left(n + 1\right)} \rceil$，下面用归纳法证明这一点。

先验证 $n = 0$ 时，$h_0 = \lceil \log_2 \left(0 + 1 \right) \rceil = 0$，成立；$n = 1$ 时，$h_1 = \lceil \log_2 \left(1 + 1 \right) \rceil = 1$，成立。

假定 $n \le k - 1$ 时 $h_{n} = \lceil \log_2{\left(n + 1\right)} \rceil$，下证明 $n = k \ge 2$ 时也成立。

由于 $\lfloor \left(n - 1\right) / 2 \rfloor \le \lceil \left(n - 1\right) / 2 \rceil \le \lfloor \left(n - 1\right) / 2 \rfloor + 1 \le k - 1$，且 $\lceil \log_2 \left(n + 1\right) \rceil$ 在 $n$ 变化 $1$ 时至多变化 $1$，则必然有：

$$
\log_2 \lfloor \left(n - 1\right) / 2 \rfloor \le \log_2 \lceil \left(n - 1\right) / 2 \rceil \le \log_2 \lfloor \left(n - 1\right) / 2 \rfloor + 1
$$

即：

$$
| \log_2 \lfloor \left(n - 1\right) / 2 \rfloor - \log_2 \lceil \left(n - 1\right) / 2 \rceil | \le 1
$$

回忆 $h_{\lfloor \left(n - 1\right) / 2 \rfloor} = \lceil \log_2 \left[ \lfloor \left(n - 1\right) / 2 \rfloor + 1 \right] \rceil$ 和 $h_{\lceil \left(n - 1\right) / 2 \rceil} = \lceil \log_2 \left[ \lceil \left(n - 1\right) / 2 \rceil + 1 \right] \rceil$，可得到：

$$
| h_{\lceil \left(n - 1\right) / 2 \rceil} - h_{\lfloor \left(n - 1\right) / 2 \rfloor} | \le 1
$$

则其是平衡的。

又：

$$
\begin{aligned}
h_{n} &= \max \left( h_{\lceil \left(n - 1\right) / 2 \rceil}, h_{\lfloor \left(n - 1\right) / 2 \rfloor} \right) + 1 = h_{\lceil \left(n - 1\right) / 2 \rceil} + 1 \\
&= \lceil \log_2 \left[ \lceil \left(n - 1\right) / 2 \rceil + 1 \right] \rceil + 1 = \lceil \log_2  \lceil \left(n + 1\right) / 2 \rceil  \rceil + 1 \\
&= \lceil \log_2 \lceil \left(n  + 1\right) / 2 \rceil + 1\rceil = \lceil \log_2 \left[2\lceil \left(n + 1\right) / 2 \rceil \right]\rceil \\
&= \lceil \log_2 \left(n + 1\right)\rceil
\end{aligned}
$$

证毕。

于是正确性得到保证，代码见下。注意判断子树是否为空。

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
    void constructArray(TreeNode* root, std::vector<int>& arr) {
        if (root == nullptr) {
            return;
        }
        constructArray(root->left, arr);
        arr.push_back(root->val);
        constructArray(root->right, arr);
    }
    void constructTree(TreeNode* altRoot, const std::vector<int>& arr, const int l, const int r) {
        if (l + 1 == r) {
            altRoot->val = arr[l];
            return;
        }
        int m = l + (r - l) / 2;
        altRoot->val = arr[m];
        if (m > l) {
            altRoot->left = new TreeNode();
            constructTree(altRoot->left, arr, l, m);
        }
        if (r > m + 1) {
            altRoot->right = new TreeNode();
            constructTree(altRoot->right, arr, m + 1, r);
        }
    }
    TreeNode* balanceBST(TreeNode* root) {
        std::vector<int> arr;
        constructArray(root, arr);
        TreeNode *altRoot = new TreeNode();
        constructTree(altRoot, arr, 0, (int)arr.size());
        return altRoot;
    }
};
```

时间复杂度和空间复杂度均为 $O(n)$。
