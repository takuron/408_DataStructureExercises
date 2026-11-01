// 练习：带头结点链队列
// 只提供契约、桩函数和测试；请自行完成 TODO。
// 失败操作不得改变原结构或输出参数；动态申请的空间需在销毁时释放。
#include "common.h"

// --- 数据结构定义 ---
struct QNode { int data; QNode *next; };
struct LinkQueue { QNode *front, *rear; };

// --- 函数声明与行为契约 ---
/** 申请头结点，front=rear，next=nullptr；分配失败返回 false。 */
bool InitQueue(LinkQueue &Q);

/** 已初始化队列的 front==rear 表示空队。 */
bool QueueEmpty(const LinkQueue &Q);

/** 尾插新结点；未初始化或分配失败返回 false。 */
bool EnQueue(LinkQueue &Q, int x);

/** 删除首个数据结点；删除最后元素后 rear 回到头结点；空队返回 false。 */
bool DeQueue(LinkQueue &Q, int &x);

/** 释放全部结点，front、rear 置空；允许重复调用。 */
void DestroyQueue(LinkQueue &Q);

// --- 在此处编写实现 ---
bool InitQueue(LinkQueue &Q) {
    // TODO: 申请头结点，front=rear，next=nullptr；分配失败返回 false。
    return false;
}

bool QueueEmpty(const LinkQueue &Q) {
    // TODO: 已初始化队列的 front==rear 表示空队。
    return false;
}

bool EnQueue(LinkQueue &Q, int x) {
    // TODO: 尾插新结点；未初始化或分配失败返回 false。
    return false;
}

bool DeQueue(LinkQueue &Q, int &x) {
    // TODO: 删除首个数据结点；删除最后元素后 rear 回到头结点；空队返回 false。
    return false;
}

void DestroyQueue(LinkQueue &Q) {
    // TODO: 释放全部结点，front、rear 置空；允许重复调用。
    (void)Q;
}

// --- 测试入口：未实现时出现 FAIL 是正常现象 ---
int main() {
    printf("--- 带头结点链队列 ---\n");

    LinkQueue Q{}; int x = -1;
    test(InitQueue(Q)); test(QueueEmpty(Q)); test(!DeQueue(Q, x));
    test(EnQueue(Q, 10)); test(EnQueue(Q, 20));
    test(DeQueue(Q, x) && x == 10); test(DeQueue(Q, x) && x == 20);
    test(Q.front && Q.rear == Q.front); test(QueueEmpty(Q));
    test(EnQueue(Q, 30)); test(DeQueue(Q, x) && x == 30);
    DestroyQueue(Q); test(!Q.front && !Q.rear);
    return 0;
}
