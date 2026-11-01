// 练习：共享栈
// 参考答案：保留原练习契约和测试，可与 main 分支对照学习。
// 失败操作不得改变原结构或输出参数；动态申请的空间需在销毁时释放。
#include "common.h"

// --- 数据结构定义 ---
typedef struct SharedStack {
    int data[MAX_SIZE];
    int top0, top1;
} SharedStack;

// --- 函数声明与行为契约 ---
/** 0 号栈从左向右，1 号栈从右向左；top0=-1、top1=MAX_SIZE。 */
void InitStack(SharedStack &S);

/** id 只能为 0 或 1；两栈栈顶相邻则满；失败返回 false。 */
bool Push(SharedStack &S, int id, int x);

/** 从指定栈弹出；非法 id 或该栈为空返回 false。 */
bool Pop(SharedStack &S, int id, int &x);

// --- 参考实现 ---
void InitStack(SharedStack &S) {
    S.top0 = -1; S.top1 = MAX_SIZE;
}

bool Push(SharedStack &S, int id, int x) {
    if ((id != 0 && id != 1) || S.top0+1 == S.top1) return false;
    if (id == 0) S.data[++S.top0] = x;
    else S.data[--S.top1] = x;
    return true;
}

bool Pop(SharedStack &S, int id, int &x) {
    if (id == 0) {
        if (S.top0 == -1) return false;
        x = S.data[S.top0--];
    } else if (id == 1) {
        if (S.top1 == MAX_SIZE) return false;
        x = S.data[S.top1++];
    } else return false;
    return true;
}

// --- 测试入口 ---
int main() {
    printf("--- 共享栈 ---\n");

    SharedStack S{}; int x = -1; InitStack(S);
    test(S.top0 == -1 && S.top1 == MAX_SIZE);
    test(!Push(S, 2, 1)); test(!Pop(S, 0, x)); test(!Pop(S, 1, x));
    test(Push(S, 0, 10)); test(Push(S, 1, 20));
    test(Pop(S, 0, x) && x == 10); test(Pop(S, 1, x) && x == 20);
    for (int i = 0; i < MAX_SIZE; ++i) test(Push(S, i % 2, i));
    test(!Push(S, 0, 999)); test(!Push(S, 1, 999));
    return 0;
}
