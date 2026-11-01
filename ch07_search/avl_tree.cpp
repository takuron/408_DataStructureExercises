// 练习：AVL 树插入与旋转（进阶）
// 参考答案：保留原练习契约和测试，可与 main 分支对照学习。
// 失败操作不得改变原结构或输出参数；动态申请的空间需在销毁时释放。
#include "common.h"

// --- 数据结构定义 ---
// height：空树为 0，叶子为 1；本练习不要求 AVL 删除。
typedef struct AVLNode {
    int key, height;
    struct AVLNode *left, *right;
} AVLNode;

// --- 函数声明与行为契约 ---
/** root 的右孩子非空；左旋并更新高度，返回新根。 */
AVLNode *RotateLeft(AVLNode *root);

/** root 的左孩子非空；右旋并更新高度，返回新根。 */
AVLNode *RotateRight(AVLNode *root);

/** 插入并处理 LL/RR/LR/RL 失衡；重复值或分配失败返回 false。 */
bool InsertAVL(AVLNode *&root, int key);

/** 后序释放结点并置空。 */
void DestroyAVL(AVLNode *&root);

static int Height(AVLNode *p) { return p ? p->height : 0; }
static void UpdateHeight(AVLNode *p) {
    int left = Height(p->left), right = Height(p->right);
    p->height = 1 + (left > right ? left : right);
}

// --- 参考实现 ---
AVLNode *RotateLeft(AVLNode *root) {
    AVLNode *p = root->right;
    root->right = p->left; p->left = root;
    UpdateHeight(root); UpdateHeight(p);
    return p;
}

AVLNode *RotateRight(AVLNode *root) {
    AVLNode *p = root->left;
    root->left = p->right; p->right = root;
    UpdateHeight(root); UpdateHeight(p);
    return p;
}

bool InsertAVL(AVLNode *&root, int key) {
    if (!root) {
        AVLNode *p = static_cast<AVLNode *>(malloc(sizeof(AVLNode)));
        if (!p) return false;
        *p = {key, 1, nullptr, nullptr}; root = p;
        return true;
    }
    if (key == root->key) return false;
    bool inserted = key < root->key ? InsertAVL(root->left,key) : InsertAVL(root->right,key);
    if (!inserted) return false;
    UpdateHeight(root);
    int balance = Height(root->left) - Height(root->right);
    if (balance > 1) {
        if (key > root->left->key) root->left = RotateLeft(root->left); // LR
        root = RotateRight(root); // LL
    } else if (balance < -1) {
        if (key < root->right->key) root->right = RotateRight(root->right); // RL
        root = RotateLeft(root); // RR
    }
    return true;
}

void DestroyAVL(AVLNode *&root) {
    if (!root) return;
    DestroyAVL(root->left); DestroyAVL(root->right); free(root); root = nullptr;
}

// --- 测试入口 ---
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
