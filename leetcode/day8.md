[Link](https://leetcode.cn/problems/add-binary/description/)

求两个二进制数的和，用二进制形式输出。

---

利用 `int(x, base=2)` 可以将字符串 `x` 视为二进制串转为整型。利用字符串格式化 `f"{n:b}"` 可将整型转为二进制串输出。

```py
def addBinary(self, a: str, b: str) -> str:
    return f"{int(a, 2) + int(b, 2) :b}"
```
