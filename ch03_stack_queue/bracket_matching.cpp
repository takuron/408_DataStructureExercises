// 练习：栈的应用：括号匹配
// 只提供契约、桩函数和测试；请自行完成 TODO。
// 失败操作不得改变原结构或输出参数；动态申请的空间需在销毁时释放。
#include "common.h"

// --- 数据结构定义 ---


// --- 函数声明与行为契约 ---
/** 匹配 ()、[]、{}，忽略其他字符；空串匹配，nullptr 不匹配；用手写栈。 */
bool BracketMatch(const char *s);

// --- 在此处编写实现 ---
bool BracketMatch(const char *s) {
    // TODO: 匹配 ()、[]、{}，忽略其他字符；空串匹配，nullptr 不匹配；用手写栈。
    return false;
}

// --- 测试入口：未实现时出现 FAIL 是正常现象 ---
int main() {
    printf("--- 栈的应用：括号匹配 ---\n");

    test(BracketMatch("")); test(BracketMatch("a{b[c+(d)]}"));
    test(!BracketMatch("([)]")); test(!BracketMatch("(()"));
    test(!BracketMatch(")(")); test(!BracketMatch(nullptr));
    return 0;
}
