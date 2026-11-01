// 练习：中序线索二叉树
// 只提供契约、桩函数和测试；请自行完成 TODO。
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

// --- 在此处编写实现 ---
void CreateInThread(ThreadNode *root) {
    // TODO: 将普通二叉树中序线索化；初始 tag 均为 0；首结点前驱、末结点后继置空且 tag=1。
    (void)root;
}

ThreadNode *FirstNode(ThreadNode *p) {
    // TODO: 返回以 p 为根子树的中序首结点；空树返回 nullptr。
    return nullptr;
}

ThreadNode *NextNode(ThreadNode *p) {
    // TODO: 在线索化树中求中序后继；末结点或空指针返回 nullptr。
    return nullptr;
}

int InOrderThread(ThreadNode *root, int out[]) {
    // TODO: 不使用递归和栈，利用线索中序遍历；返回写入 out 的元素数。
    return 0;
}

// --- 测试入口：未实现时出现 FAIL 是正常现象 ---
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
