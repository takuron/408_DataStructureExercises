// 练习：定长顺序串的基本操作
// 只提供契约、桩函数和测试；请自行完成 TODO。
// 失败操作不得改变原结构或输出参数；动态申请的空间需在销毁时释放。
#include "common.h"

// --- 数据结构定义 ---
// 下标从 0 开始；length 不包含终止符；保留一位存放 \0。
typedef struct SString {
    char ch[MAX_SIZE + 1];
    int length;
} SString;

// --- 函数声明与行为契约 ---
/** 从 C 字符串赋值；空指针或长度超过 MAX_SIZE 返回 false。 */
bool StrAssign(SString &s, const char *text);

/** 按字符字典序比较，返回负数/0/正数。 */
int StrCompare(const SString &a, const SString &b);

/** 连接两串；超容量返回 false；要求支持 out 与输入为同一对象。 */
bool Concat(SString &out, const SString &a, const SString &b);

/** pos 为 0 基下标；0<=pos<=length、0<=len<=length-pos；支持别名；失败返回 false。 */
bool SubString(SString &out, const SString &s, int pos, int len);

// --- 在此处编写实现 ---
bool StrAssign(SString &s, const char *text) {
    // TODO: 从 C 字符串赋值；空指针或长度超过 MAX_SIZE 返回 false。
    return false;
}

int StrCompare(const SString &a, const SString &b) {
    // TODO: 按字符字典序比较，返回负数/0/正数。
    return 0;
}

bool Concat(SString &out, const SString &a, const SString &b) {
    // TODO: 连接两串；超容量返回 false；要求支持 out 与输入为同一对象。
    return false;
}

bool SubString(SString &out, const SString &s, int pos, int len) {
    // TODO: pos 为 0 基下标；0<=pos<=length、0<=len<=length-pos；支持别名；失败返回 false。
    return false;
}

// --- 测试入口：未实现时出现 FAIL 是正常现象 ---
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
