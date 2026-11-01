// 练习：定长顺序串的基本操作
// 参考答案：保留原练习契约和测试，可与 main 分支对照学习。
// 失败操作不得改变原结构或输出参数；动态申请的空间需在销毁时释放。
#include "common.h"

// --- 数据结构定义 ---
// 下标从 0 开始；length 不包含终止符；保留一位存放 \0。
struct SString { char ch[MAX_SIZE + 1]; int length; };

// --- 函数声明与行为契约 ---
/** 从 C 字符串赋值；空指针或长度超过 MAX_SIZE 返回 false。 */
bool StrAssign(SString &s, const char *text);

/** 按字符字典序比较，返回负数/0/正数。 */
int StrCompare(const SString &a, const SString &b);

/** 连接两串；超容量返回 false；要求支持 out 与输入为同一对象。 */
bool Concat(SString &out, const SString &a, const SString &b);

/** pos 为 0 基下标；0<=pos<=length、0<=len<=length-pos；支持别名；失败返回 false。 */
bool SubString(SString &out, const SString &s, int pos, int len);

// --- 参考实现 ---
bool StrAssign(SString &s, const char *text) {
    if (!text) return false;
    size_t n = strlen(text);
    if (n > MAX_SIZE) return false;
    // memmove 允许 text 来自 s.ch 的重叠区域。
    memmove(s.ch, text, n+1);
    s.length = static_cast<int>(n);
    return true;
}

int StrCompare(const SString &a, const SString &b) {
    int n = a.length < b.length ? a.length : b.length;
    for (int i = 0; i < n; ++i) {
        unsigned char x = static_cast<unsigned char>(a.ch[i]);
        unsigned char y = static_cast<unsigned char>(b.ch[i]);
        if (x != y) return x < y ? -1 : 1;
    }
    return (a.length > b.length) - (a.length < b.length);
}

bool Concat(SString &out, const SString &a, const SString &b) {
    if (a.length + b.length > MAX_SIZE) return false;
    SString temp{};
    temp.length = a.length + b.length;
    memcpy(temp.ch, a.ch, a.length);
    memcpy(temp.ch+a.length, b.ch, b.length);
    temp.ch[temp.length] = '\0';
    out = temp;
    return true;
}

bool SubString(SString &out, const SString &s, int pos, int len) {
    if (pos < 0 || pos > s.length || len < 0 || len > s.length-pos) return false;
    SString temp{};
    memcpy(temp.ch, s.ch+pos, len);
    temp.length = len; temp.ch[len] = '\0';
    out = temp;
    return true;
}

// --- 测试入口 ---
int main() {
    printf("--- 定长顺序串的基本操作 ---\n");

    SString a{}, b{}, out{};
    test(StrAssign(a, "abc")); test(StrAssign(b, "abd"));
    test(StrCompare(a, b) < 0); test(StrCompare(a, a) == 0);
    test(Concat(out, a, b) && out.length == 6 && strcmp(out.ch, "abcabd") == 0);
    test(SubString(out, a, 1, 2) && strcmp(out.ch, "bc") == 0);
    test(SubString(out, a, 3, 0) && out.length == 0);
    test(!SubString(out, a, -1, 2)); test(!SubString(out, a, 2, 2));
    test(Concat(a, a, b) && strcmp(a.ch, "abcabd") == 0);
    test(!StrAssign(a, nullptr));
    return 0;
}
