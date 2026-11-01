// 练习：不带头结点链栈
// 只提供契约、桩函数和测试；请自行完成 TODO。
// 失败操作不得改变原结构或输出参数；动态申请的空间需在销毁时释放。
#include "common.h"

// --- 数据结构定义 ---
typedef struct SNode {
    int data;
    struct SNode *next;
} SNode;
typedef SNode *LinkStack;

// --- 函数声明与行为契约 ---
/** 空指针表示空栈。 */
bool StackEmpty(LinkStack S);

/** 头插新结点；分配失败返回 false。 */
bool Push(LinkStack &S, int x);

/** 删除栈顶并释放，通过 x 返回值；空栈返回 false。 */
bool Pop(LinkStack &S, int &x);

/** 读取栈顶但不删除；空栈返回 false。 */
bool GetTop(LinkStack S, int &x);

/** 释放所有结点并置空；可重复调用。 */
void DestroyStack(LinkStack &S);

// --- 在此处编写实现 ---
bool StackEmpty(LinkStack S) {
    // TODO: 空指针表示空栈。
    return false;
}

bool Push(LinkStack &S, int x) {
    // TODO: 头插新结点；分配失败返回 false。
    return false;
}

bool Pop(LinkStack &S, int &x) {
    // TODO: 删除栈顶并释放，通过 x 返回值；空栈返回 false。
    return false;
}

bool GetTop(LinkStack S, int &x) {
    // TODO: 读取栈顶但不删除；空栈返回 false。
    return false;
}

void DestroyStack(LinkStack &S) {
    // TODO: 释放所有结点并置空；可重复调用。
    (void)S;
}

// --- 测试入口：未实现时出现 FAIL 是正常现象 ---
int main() {
    printf("--- 不带头结点链栈 ---\n");

    LinkStack S = nullptr; int x = -1;
    test(StackEmpty(S)); test(!Pop(S, x) && x == -1);
    test(Push(S, 10)); test(Push(S, 20));
    test(GetTop(S, x) && x == 20);
    test(Pop(S, x) && x == 20); test(Pop(S, x) && x == 10);
    test(StackEmpty(S)); test(!GetTop(S, x));
    test(Push(S, 30)); DestroyStack(S); test(S == nullptr);
    return 0;
}
