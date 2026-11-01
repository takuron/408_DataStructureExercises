// 练习：不带头结点链栈
// 参考答案：保留原练习契约和测试，可与 main 分支对照学习。
// 失败操作不得改变原结构或输出参数；动态申请的空间需在销毁时释放。
#include "common.h"

// --- 数据结构定义 ---
struct SNode { int data; SNode *next; };
using LinkStack = SNode *;

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

// --- 参考实现 ---
bool StackEmpty(LinkStack S) {
    return S == nullptr;
}

bool Push(LinkStack &S, int x) {
    SNode *p = static_cast<SNode *>(malloc(sizeof(SNode)));
    if (!p) return false;
    *p = {x, S}; S = p;
    return true;
}

bool Pop(LinkStack &S, int &x) {
    if (!S) return false;
    SNode *p = S;
    x = p->data; S = p->next; free(p);
    return true;
}

bool GetTop(LinkStack S, int &x) {
    if (!S) return false;
    x = S->data;
    return true;
}

void DestroyStack(LinkStack &S) {
    while (S) { SNode *p = S; S = S->next; free(p); }
}

// --- 测试入口 ---
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
