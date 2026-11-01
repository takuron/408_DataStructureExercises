// 练习：循环队列（牺牲一个单元）
// 只提供契约、桩函数和测试；请自行完成 TODO。
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

// --- 在此处编写实现 ---
void InitQueue(SqQueue &Q) {
    // TODO: front 和 rear 均置零；rear 指向下一次入队的位置。
    (void)Q;
}

bool QueueEmpty(const SqQueue &Q) {
    // TODO: front == rear 表示空队。
    return false;
}

int Length(const SqQueue &Q) {
    // TODO: 返回队长，范围 [0,MAX_SIZE-1]。
    return -1;
}

bool EnQueue(SqQueue &Q, int x) {
    // TODO: 满队返回 false；否则写入队尾并循环移动 rear。
    return false;
}

bool DeQueue(SqQueue &Q, int &x) {
    // TODO: 空队返回 false；否则带回队头并循环移动 front。
    return false;
}

bool GetHead(const SqQueue &Q, int &x) {
    // TODO: 读队头，不改变队列；空队返回 false。
    return false;
}

// --- 测试入口：未实现时出现 FAIL 是正常现象 ---
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
