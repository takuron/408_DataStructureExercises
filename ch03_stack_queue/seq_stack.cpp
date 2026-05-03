// ==========================================
// 题目：顺序栈的基本操作（静态分配）
// 所属章节：ch03 栈和队列
// ==========================================
#include "common.h"

#define MaxSize 50  // 栈的最大容量

typedef struct {
    int data[MaxSize];  // 存放栈中元素
    int top;            // 栈顶指针（-1 表示空栈）
} SqStack;

// ==========================================
// 栈的基本操作声明
// ==========================================

/** 初始化栈：top 置为 -1 */
void InitStack(SqStack &S);

/** 判空：top == -1 返回 true */
bool StackEmpty(SqStack S);

/** 进栈：先判满，再 data[++top] = x */
bool Push(SqStack &S, int x);

/** 出栈：先判空，再 x = data[top--] */
bool Pop(SqStack &S, int &x);

/** 读栈顶：先判空，再 x = data[top] */
bool GetTop(SqStack S, int &x);


// ==========================================
// [在此处编写你的实现代码]
// ==========================================

void InitStack(SqStack &S) {
    // TODO
    S.top = -1;
}

bool StackEmpty(SqStack S) {
    // TODO
    return S.top == -1;
}

bool Push(SqStack &S, int x) {
    // TODO: 判满、入栈
    return false;
}

bool Pop(SqStack &S, int &x) {
    // TODO: 判空、出栈
    return false;
}

bool GetTop(SqStack S, int &x) {
    // TODO: 判空、读栈顶
    return false;
}


// ==========================================
// 测试用例
// ==========================================
int main() {
    SqStack S;
    int x;

    printf("--- 开始测试顺序栈 ---\n");

    InitStack(S);
    test_msg(StackEmpty(S) == true, "初始化后栈为空");

    // 入栈测试
    test_msg(Push(S, 10), "入栈 10 成功");
    test_msg(Push(S, 20), "入栈 20 成功");
    test_msg(Push(S, 30), "入栈 30 成功");
    test_msg(StackEmpty(S) == false, "入栈后栈非空");

    // 读栈顶
    test_msg(GetTop(S, x) && x == 30, "栈顶元素为 30");

    // 出栈测试
    test_msg(Pop(S, x) && x == 30, "出栈得到 30");
    test_msg(Pop(S, x) && x == 20, "出栈得到 20");
    test_msg(Pop(S, x) && x == 10, "出栈得到 10");
    test_msg(StackEmpty(S) == true, "全部出栈后栈为空");

    // 空栈出栈应失败
    test_msg(Pop(S, x) == false, "空栈出栈返回 false");

    printf("--- 测试结束 ---\n");
    return 0;
}
