// 练习：带头结点链队列
// 参考答案：保留原练习契约和测试，可与 main 分支对照学习。
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

// --- 参考实现 ---
bool InitQueue(LinkQueue &Q) {
    QNode *p = static_cast<QNode *>(malloc(sizeof(QNode)));
    if (!p) return false;
    p->next = nullptr;
    Q.front = Q.rear = p;
    return true;
}

bool QueueEmpty(const LinkQueue &Q) {
    return Q.front == Q.rear;
}

bool EnQueue(LinkQueue &Q, int x) {
    if (!Q.rear) return false;
    QNode *p = static_cast<QNode *>(malloc(sizeof(QNode)));
    if (!p) return false;
    *p = {x, nullptr};
    Q.rear->next = p; Q.rear = p;
    return true;
}

bool DeQueue(LinkQueue &Q, int &x) {
    if (!Q.front || QueueEmpty(Q)) return false;
    QNode *p = Q.front->next;
    x = p->data;
    Q.front->next = p->next;
    if (Q.rear == p) Q.rear = Q.front;
    free(p);
    return true;
}

void DestroyQueue(LinkQueue &Q) {
    while (Q.front) { QNode *p = Q.front; Q.front = p->next; free(p); }
    Q.rear = nullptr;
}

// --- 测试入口 ---
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
