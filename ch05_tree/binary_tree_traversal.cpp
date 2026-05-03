// ==========================================
// 题目：二叉树遍历（递归实现）
// 所属章节：ch05 树与二叉树
// ==========================================
#include "common.h"

// 二叉链表结点定义
typedef struct BiNode {
    char data;
    BiNode *lchild, *rchild;
} BiNode, *BiTree;

// ==========================================
// 函数声明
// ==========================================

/** 先序遍历：根 → 左 → 右 */
void PreOrder(BiTree T);

/** 中序遍历：左 → 根 → 右 */
void InOrder(BiTree T);

/** 后序遍历：左 → 右 → 根 */
void PostOrder(BiTree T);


// ==========================================
// [在此处编写你的实现代码]
// ==========================================

void visit(BiNode *p) {
    printf("%c ", p->data);
}

void PreOrder(BiTree T) {
    // TODO
    if (T == nullptr) return;
    visit(T);
    PreOrder(T->lchild);
    PreOrder(T->rchild);
}

void InOrder(BiTree T) {
    // TODO
    if (T == nullptr) return;
    InOrder(T->lchild);
    visit(T);
    InOrder(T->rchild);
}

void PostOrder(BiTree T) {
    // TODO
    if (T == nullptr) return;
    PostOrder(T->lchild);
    PostOrder(T->rchild);
    visit(T);
}


// ==========================================
// 辅助函数：手动构造测试树
//     A
//    / \
//   B   C
//  / \
// D   E
// ==========================================
BiTree BuildTestTree() {
    BiNode *A = (BiNode*)malloc(sizeof(BiNode));
    BiNode *B = (BiNode*)malloc(sizeof(BiNode));
    BiNode *C = (BiNode*)malloc(sizeof(BiNode));
    BiNode *D = (BiNode*)malloc(sizeof(BiNode));
    BiNode *E = (BiNode*)malloc(sizeof(BiNode));
    A->data = 'A'; B->data = 'B'; C->data = 'C';
    D->data = 'D'; E->data = 'E';
    A->lchild = B; A->rchild = C;
    B->lchild = D; B->rchild = E;
    C->lchild = C->rchild = nullptr;
    D->lchild = D->rchild = nullptr;
    E->lchild = E->rchild = nullptr;
    return A;
}

void FreeTree(BiTree T) {
    if (T == nullptr) return;
    FreeTree(T->lchild);
    FreeTree(T->rchild);
    free(T);
}


// ==========================================
// 测试入口
// ==========================================
int main() {
    BiTree T = BuildTestTree();

    printf("--- 测试二叉树遍历 ---\n");

    printf("先序遍历: ");
    PreOrder(T);
    printf("\n期望输出: A B D E C\n\n");

    printf("中序遍历: ");
    InOrder(T);
    printf("\n期望输出: D B E A C\n\n");

    printf("后序遍历: ");
    PostOrder(T);
    printf("\n期望输出: D E B C A\n\n");

    FreeTree(T);
    printf("--- 测试结束 ---\n");
    return 0;
}
