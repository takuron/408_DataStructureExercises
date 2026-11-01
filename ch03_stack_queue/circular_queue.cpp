// 练习：循环队列（牺牲一个单元）
// 参考答案：保留原练习契约和测试，可与 main 分支对照学习。
// 失败操作不得改变原结构或输出参数；动态申请的空间需在销毁时释放。
#include "common.h"

// --- 数据结构定义 ---
typedef struct SqQueue {
    int data[MAX_SIZE];
    int front, rear;
} SqQueue;

// --- 函数声明与行为契约 ---
/** front 和 rear 均置零；rear 指向下一次入队的位置。 */
void InitQueue(SqQueue &Q);

/** front == rear 表示空队。 */
bool QueueEmpty(const SqQueue &Q);

/** 返回队长，范围 [0,MAX_SIZE-1]。 */
int Length(const SqQueue &Q);

/** 满队返回 false；否则写入队尾并循环移动 rear。 */
bool EnQueue(SqQueue &Q, int x);

/** 空队返回 false；否则带回队头并循环移动 front。 */
bool DeQueue(SqQueue &Q, int &x);

/** 读队头，不改变队列；空队返回 false。 */
bool GetHead(const SqQueue &Q, int &x);

// --- 参考实现 ---
void InitQueue(SqQueue &Q) {
    Q.front = Q.rear = 0;
}

bool QueueEmpty(const SqQueue &Q) {
    return Q.front == Q.rear;
}

int Length(const SqQueue &Q) {
    return (Q.rear - Q.front + MAX_SIZE) % MAX_SIZE;
}

bool EnQueue(SqQueue &Q, int x) {
    if ((Q.rear+1) % MAX_SIZE == Q.front) return false;
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear+1) % MAX_SIZE;
    return true;
}

bool DeQueue(SqQueue &Q, int &x) {
    if (QueueEmpty(Q)) return false;
    x = Q.data[Q.front];
    Q.front = (Q.front+1) % MAX_SIZE;
    return true;
}

bool GetHead(const SqQueue &Q, int &x) {
    if (QueueEmpty(Q)) return false;
    x = Q.data[Q.front];
    return true;
}

// --- 测试入口 ---
int main() {
    printf("--- 循环队列（牺牲一个单元） ---\n");

    SqQueue Q{}; int x = -1; InitQueue(Q);
    test(QueueEmpty(Q)); test(Length(Q) == 0); test(!DeQueue(Q, x));
    for (int i = 0; i < MAX_SIZE - 1; ++i) test(EnQueue(Q, i));
    test(!EnQueue(Q, 999)); test(Length(Q) == MAX_SIZE - 1);
    test(DeQueue(Q, x) && x == 0); test(EnQueue(Q, 100));
    for (int i = 1; i < MAX_SIZE - 1; ++i) test(DeQueue(Q, x) && x == i);
    test(GetHead(Q, x) && x == 100); test(DeQueue(Q, x) && x == 100);
    test(QueueEmpty(Q)); test(!GetHead(Q, x));
    return 0;
}
