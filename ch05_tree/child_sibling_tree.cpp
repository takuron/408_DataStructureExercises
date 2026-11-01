// 练习：树的孩子兄弟表示
// 参考答案：保留原练习契约和测试，可与 main 分支对照学习。
// 测试结点是栈上对象；out 容量由调用者保证；树高按原树的层数计算，不是二叉链表高度。
#include "common.h"

// --- 数据结构定义 ---
// firstChild 指向第一个孩子，nextSibling 指向下一个兄弟。
struct CSNode { char data; CSNode *firstChild, *nextSibling; };

// --- 函数声明与行为契约 ---
/** 树/森林先根遍历（等价于对应二叉树先序）；写入 out，返回元素数。 */
int PreOrderForest(CSNode *root, char out[]);

/** 树/森林后根遍历（等价于对应二叉树中序）；返回元素数。 */
int PostOrderForest(CSNode *root, char out[]);

/** 返回森林中各棵树高度的最大值；空森林为 0；兄弟关系不增加深度。 */
int ForestHeight(CSNode *root);

/** 没有 firstChild 的结点是原树叶子；统计森林中叶子总数。 */
int LeafCount(CSNode *root);

static void WritePre(CSNode *p, char out[], int &n) {
    if (!p) return;
    out[n++] = p->data;
    WritePre(p->firstChild, out, n);
    WritePre(p->nextSibling, out, n);
}
static void WritePost(CSNode *p, char out[], int &n) {
    if (!p) return;
    WritePost(p->firstChild, out, n);
    out[n++] = p->data;
    WritePost(p->nextSibling, out, n);
}

// --- 参考实现 ---
int PreOrderForest(CSNode *root, char out[]) {
    int n = 0;
    WritePre(root, out, n);
    return n;
}

int PostOrderForest(CSNode *root, char out[]) {
    int n = 0;
    WritePost(root, out, n);
    return n;
}

int ForestHeight(CSNode *root) {
    int height = 0;
    for (CSNode *p = root; p; p = p->nextSibling) {
        int h = 1 + ForestHeight(p->firstChild);
        if (h > height) height = h;
    }
    return height;
}

int LeafCount(CSNode *root) {
    int n = 0;
    for (CSNode *p = root; p; p = p->nextSibling)
        n += p->firstChild ? LeafCount(p->firstChild) : 1;
    return n;
}

// --- 测试入口 ---
int main() {
    printf("--- 树的孩子兄弟表示 ---\n");

    // A 的孩子为 B、C；B 的孩子为 D；独立的树 E 与 A 构成森林。
    CSNode d{'D',nullptr,nullptr}, c{'C',nullptr,nullptr};
    CSNode b{'B',&d,&c}, e{'E',nullptr,nullptr}, a{'A',&b,&e};
    char out[5] = {}, pre[] = {'A','B','D','C','E'}, post[] = {'D','B','C','A','E'};
    test(PreOrderForest(&a,out) == 5 && memcmp(out,pre,5) == 0);
    test(PostOrderForest(&a,out) == 5 && memcmp(out,post,5) == 0);
    test(ForestHeight(&a) == 3); test(LeafCount(&a) == 3);
    test(ForestHeight(nullptr) == 0); test(LeafCount(nullptr) == 0);
    return 0;
}
