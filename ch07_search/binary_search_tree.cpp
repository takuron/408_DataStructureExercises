// 练习：二叉排序树 BST
// 参考答案：保留原练习契约和测试，可与 main 分支对照学习。
// 失败操作不得改变原结构或输出参数；动态申请的空间需在销毁时释放。
#include "common.h"

// --- 数据结构定义 ---
struct BSTNode { int key; BSTNode *left, *right; };
using BSTree = BSTNode *;

// --- 函数声明与行为契约 ---
/** 返回匹配结点，找不到返回 nullptr。 */
BSTNode *Search(BSTree T, int key);

/** 插入不同关键字；重复值或分配失败返回 false。 */
bool Insert(BSTree &T, int key);

/** 删除关键字结点并释放；处理叶子、单孩子和双孩子三种情况；不存在返回 false。 */
bool Delete(BSTree &T, int key);

/** 中序遍历写入 out，返回元素个数；out 容量由调用者保证。 */
int InOrder(BSTree T, int out[]);

/** 后序释放全部结点并置空。 */
void DestroyTree(BSTree &T);

// --- 参考实现 ---
BSTNode *Search(BSTree T, int key) {
    while (T && T->key != key) T = key < T->key ? T->left : T->right;
    return T;
}

bool Insert(BSTree &T, int key) {
    if (!T) {
        BSTNode *p = static_cast<BSTNode *>(malloc(sizeof(BSTNode)));
        if (!p) return false;
        *p = {key, nullptr, nullptr}; T = p;
        return true;
    }
    if (key == T->key) return false;
    return key < T->key ? Insert(T->left,key) : Insert(T->right,key);
}

bool Delete(BSTree &T, int key) {
    if (!T) return false;
    if (key < T->key) return Delete(T->left,key);
    if (key > T->key) return Delete(T->right,key);
    if (T->left && T->right) {
        // 双孩子：用中序后继替换，再删除后继结点。
        BSTNode *p = T->right;
        while (p->left) p = p->left;
        T->key = p->key;
        return Delete(T->right,p->key);
    }
    BSTNode *old = T;
    T = T->left ? T->left : T->right;
    free(old);
    return true;
}

int InOrder(BSTree T, int out[]) {
    if (!T) return 0;
    int n = InOrder(T->left,out);
    out[n++] = T->key;
    return n + InOrder(T->right,out+n);
}

void DestroyTree(BSTree &T) {
    if (!T) return;
    DestroyTree(T->left); DestroyTree(T->right); free(T); T = nullptr;
}

// --- 测试入口 ---
int main() {
    printf("--- 二叉排序树 BST ---\n");

    BSTree T = nullptr; int keys[] = {50,30,70,20,40,60,80};
    for (int k : keys) test(Insert(T,k));
    test(!Insert(T,30)); BSTNode *p = Search(T,60); test(p && p->key == 60);
    test(Search(T,99) == nullptr); test(Delete(T,20)); test(Delete(T,30));
    test(Delete(T,50)); test(!Delete(T,99));
    int out[7] = {}, expected[] = {40,60,70,80};
    test(InOrder(T,out) == 4 && memcmp(out,expected,sizeof(expected)) == 0);
    DestroyTree(T); test(T == nullptr); test(!Delete(T,1));
    test(Insert(T,1)); test(Delete(T,1)); test(T == nullptr);
    return 0;
}
