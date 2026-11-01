// 练习：中序线索二叉树
// 参考答案：保留原练习契约和测试，可与 main 分支对照学习。
// 只对普通树调用一次线索化；测试结点为栈上对象，不要释放；out 容量由调用者保证。
#include "common.h"

// --- 数据结构定义 ---
// tag=0 表示孩子，tag=1 表示线索；无头结点。
typedef struct ThreadNode {
    int data;
    struct ThreadNode *lchild, *rchild;
    int ltag, rtag;
} ThreadNode;

// --- 函数声明与行为契约 ---
/** 将普通二叉树中序线索化；初始 tag 均为 0；首结点前驱、末结点后继置空且 tag=1。 */
void CreateInThread(ThreadNode *root);

/** 返回以 p 为根子树的中序首结点；空树返回 nullptr。 */
ThreadNode *FirstNode(ThreadNode *p);

/** 在线索化树中求中序后继；末结点或空指针返回 nullptr。 */
ThreadNode *NextNode(ThreadNode *p);

/** 不使用递归和栈，利用线索中序遍历；返回写入 out 的元素数。 */
int InOrderThread(ThreadNode *root, int out[]);

// prev 始终保存刚访问的结点；只递归真实孩子，不能沿线索递归。
static void ThreadInOrder(ThreadNode *p, ThreadNode *&prev) {
    if (!p) return;
    ThreadInOrder(p->lchild, prev);
    if (!p->lchild) { p->ltag = 1; p->lchild = prev; }
    if (prev && !prev->rchild) { prev->rtag = 1; prev->rchild = p; }
    prev = p;
    ThreadInOrder(p->rchild, prev);
}

// --- 参考实现 ---
void CreateInThread(ThreadNode *root) {
    ThreadNode *prev = nullptr;
    ThreadInOrder(root, prev);
    if (prev) { prev->rtag = 1; prev->rchild = nullptr; }
}

ThreadNode *FirstNode(ThreadNode *p) {
    while (p && p->ltag == 0 && p->lchild) p = p->lchild;
    return p;
}

ThreadNode *NextNode(ThreadNode *p) {
    if (!p) return nullptr;
    return p->rtag == 1 ? p->rchild : FirstNode(p->rchild);
}

int InOrderThread(ThreadNode *root, int out[]) {
    int n = 0;
    for (ThreadNode *p = FirstNode(root); p; p = NextNode(p)) out[n++] = p->data;
    return n;
}

// --- 测试入口 ---
int main() {
    printf("--- 中序线索二叉树 ---\n");

    ThreadNode b{2,nullptr,nullptr,0,0}, c{3,nullptr,nullptr,0,0};
    ThreadNode a{1,&b,&c,0,0}; CreateInThread(&a);
    test(b.ltag == 1 && b.lchild == nullptr); test(b.rtag == 1 && b.rchild == &a);
    test(c.ltag == 1 && c.lchild == &a); test(c.rtag == 1 && c.rchild == nullptr);
    test(FirstNode(&a) == &b); test(NextNode(&b) == &a); test(NextNode(&c) == nullptr);
    int out[3] = {}, expected[] = {2,1,3};
    test(InOrderThread(&a,out) == 3 && memcmp(out,expected,sizeof(out)) == 0);
    CreateInThread(nullptr); test(FirstNode(nullptr) == nullptr);
    return 0;
}
