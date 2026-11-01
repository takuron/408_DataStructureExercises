// 练习：二叉树非递归遍历、层序遍历与性质
// 参考答案：保留原练习契约和测试，可与 main 分支对照学习。
// 测试树为栈上对象，不要释放；约定树无环且结点数不超过 MAX_SIZE，out 至少 MAX_SIZE 格。
#include "common.h"

// --- 数据结构定义 ---
typedef struct BiNode {
    int data;
    struct BiNode *lchild, *rchild;
} BiNode;
typedef BiNode *BiTree;

// --- 函数声明与行为契约 ---
/** 非递归先序遍历，把值依次写入 out，返回结点数；空树返回 0。 */
int PreOrderIterative(BiTree T, int out[]);

/** 非递归中序遍历，写入 out，返回结点数。 */
int InOrderIterative(BiTree T, int out[]);

/** 非递归后序遍历，写入 out，返回结点数。 */
int PostOrderIterative(BiTree T, int out[]);

/** 使用手写队列层序遍历，写入 out，返回结点数。 */
int LevelOrder(BiTree T, int out[]);

/** 递归求高度；空树高度 0，单结点树高度 1。 */
int TreeHeight(BiTree T);

/** 求叶结点数；空树为 0。 */
int LeafCount(BiTree T);

// --- 参考实现 ---
int PreOrderIterative(BiTree T, int out[]) {
    BiNode *stack[MAX_SIZE]; int top = 0, n = 0;
    if (T) stack[top++] = T;
    while (top) {
        BiNode *p = stack[--top]; out[n++] = p->data;
        if (p->rchild) stack[top++] = p->rchild;
        if (p->lchild) stack[top++] = p->lchild;
    }
    return n;
}

int InOrderIterative(BiTree T, int out[]) {
    BiNode *stack[MAX_SIZE]; int top = 0, n = 0;
    BiNode *p = T;
    while (p || top) {
        while (p) { stack[top++] = p; p = p->lchild; }
        p = stack[--top]; out[n++] = p->data; p = p->rchild;
    }
    return n;
}

int PostOrderIterative(BiTree T, int out[]) {
    BiNode *stack[MAX_SIZE]; int top = 0, n = 0;
    BiNode *p = T, *last = nullptr;
    while (p || top) {
        if (p) { stack[top++] = p; p = p->lchild; }
        else {
            BiNode *peek = stack[top-1];
            // 右子树不存在或刚访问过，才访问根。
            if (peek->rchild && peek->rchild != last) p = peek->rchild;
            else { out[n++] = peek->data; last = peek; --top; }
        }
    }
    return n;
}

int LevelOrder(BiTree T, int out[]) {
    if (!T) return 0;
    BiNode *queue[MAX_SIZE]; int front = 0, rear = 0, n = 0;
    queue[rear++] = T;
    while (front < rear) {
        BiNode *p = queue[front++]; out[n++] = p->data;
        if (p->lchild) queue[rear++] = p->lchild;
        if (p->rchild) queue[rear++] = p->rchild;
    }
    return n;
}

int TreeHeight(BiTree T) {
    if (!T) return 0;
    int left = TreeHeight(T->lchild), right = TreeHeight(T->rchild);
    return 1 + (left > right ? left : right);
}

int LeafCount(BiTree T) {
    if (!T) return 0;
    if (!T->lchild && !T->rchild) return 1;
    return LeafCount(T->lchild) + LeafCount(T->rchild);
}

// --- 测试入口 ---
int main() {
    printf("--- 二叉树非递归遍历、层序遍历与性质 ---\n");

    BiNode d{4,nullptr,nullptr}, e{5,nullptr,nullptr};
    BiNode b{2,&d,&e}, c{3,nullptr,nullptr}, a{1,&b,&c};
    int out[MAX_SIZE] = {};
    int pre[] = {1,2,4,5,3}, in[] = {4,2,5,1,3};
    int post[] = {4,5,2,3,1}, level[] = {1,2,3,4,5};
    test(PreOrderIterative(&a,out) == 5 && memcmp(out,pre,sizeof(pre)) == 0);
    test(InOrderIterative(&a,out) == 5 && memcmp(out,in,sizeof(in)) == 0);
    test(PostOrderIterative(&a,out) == 5 && memcmp(out,post,sizeof(post)) == 0);
    test(LevelOrder(&a,out) == 5 && memcmp(out,level,sizeof(level)) == 0);
    test(TreeHeight(&a) == 3); test(LeafCount(&a) == 3);
    test(TreeHeight(nullptr) == 0); test(LeafCount(nullptr) == 0);
    test(PostOrderIterative(nullptr,out) == 0);
    return 0;
}
