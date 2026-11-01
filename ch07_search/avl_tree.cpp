// 练习：AVL 树插入与旋转（进阶）
// 只提供契约、桩函数和测试；请自行完成 TODO。
// 失败操作不得改变原结构或输出参数；动态申请的空间需在销毁时释放。
#include "common.h"

// --- 数据结构定义 ---
// height：空树为 0，叶子为 1；本练习不要求 AVL 删除。
struct AVLNode { int key, height; AVLNode *left, *right; };

// --- 函数声明与行为契约 ---
/** root 的右孩子非空；左旋并更新高度，返回新根。 */
AVLNode *RotateLeft(AVLNode *root);

/** root 的左孩子非空；右旋并更新高度，返回新根。 */
AVLNode *RotateRight(AVLNode *root);

/** 插入并处理 LL/RR/LR/RL 失衡；重复值或分配失败返回 false。 */
bool InsertAVL(AVLNode *&root, int key);

/** 后序释放结点并置空。 */
void DestroyAVL(AVLNode *&root);

// --- 在此处编写实现 ---
AVLNode *RotateLeft(AVLNode *root) {
    // TODO: root 的右孩子非空；左旋并更新高度，返回新根。
    return root;
}

AVLNode *RotateRight(AVLNode *root) {
    // TODO: root 的左孩子非空；右旋并更新高度，返回新根。
    return root;
}

bool InsertAVL(AVLNode *&root, int key) {
    // TODO: 插入并处理 LL/RR/LR/RL 失衡；重复值或分配失败返回 false。
    return false;
}

void DestroyAVL(AVLNode *&root) {
    // TODO: 后序释放结点并置空。
    (void)root;
}

// --- 测试入口：未实现时出现 FAIL 是正常现象 ---
int main() {
    printf("--- AVL 树插入与旋转（进阶） ---\n");

    int cases[4][3] = {{30,20,10},{10,20,30},{30,10,20},{10,30,20}};
    for (auto &keys : cases) {
        AVLNode *root = nullptr;
        for (int k : keys) test(InsertAVL(root,k));
        test(root && root->key == 20 && root->height == 2);
        test(root && root->left && root->left->key == 10 && root->left->height == 1);
        test(root && root->right && root->right->key == 30 && root->right->height == 1);
        test(!InsertAVL(root,20)); DestroyAVL(root); test(!root);
    }
    return 0;
}
