// 练习：栈的应用：括号匹配
// 参考答案：保留原练习契约和测试，可与 main 分支对照学习。
// 失败操作不得改变原结构或输出参数；动态申请的空间需在销毁时释放。
#include "common.h"

// --- 数据结构定义 ---


// --- 函数声明与行为契约 ---
/** 匹配 ()、[]、{}，忽略其他字符；空串匹配，nullptr 不匹配；用手写栈。 */
bool BracketMatch(const char *s);

// --- 参考实现 ---
bool BracketMatch(const char *s) {
    if (!s) return false;
    // 按输入长度分配顺序栈，避免固定栈容量限制合法输入长度。
    char *stack = static_cast<char *>(malloc(strlen(s)+1));
    if (!stack) return false;
    size_t top = 0;
    bool matched = true;
    for (size_t i = 0; s[i]; ++i) {
        char c = s[i];
        if (c == '(' || c == '[' || c == '{') stack[top++] = c;
        else if (c == ')' || c == ']' || c == '}') {
            char expected = c == ')' ? '(' : (c == ']' ? '[' : '{');
            if (top == 0 || stack[--top] != expected) { matched = false; break; }
        }
    }
    matched = matched && top == 0;
    free(stack);
    return matched;
}

// --- 测试入口 ---
int main() {
    printf("--- 栈的应用：括号匹配 ---\n");

    test(BracketMatch("")); test(BracketMatch("a{b[c+(d)]}"));
    test(!BracketMatch("([)]")); test(!BracketMatch("(()"));
    test(!BracketMatch(")(")); test(!BracketMatch(nullptr));
    return 0;
}
