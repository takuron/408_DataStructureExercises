// 练习：哈夫曼树与带权路径长度
// 参考答案：保留原练习契约和测试，可与 main 分支对照学习。
// tree 容量至少 2*n-1；同权结点可任选，但 WPL 必须最小；约定权值总和及 WPL 均可用 int 表示。
#include "common.h"

// --- 数据结构定义 ---
// 0 基：前 n 项是叶子，后 n-1 项是内部结点；-1 表示无父/孩子。
struct HNode { int weight, parent, left, right; };

// --- 函数声明与行为契约 ---
/** n 范围 [1,MAX_SIZE]，权值为正；构造 2*n-1 个结点，根下标 2*n-2；非法输入返回 false。 */
bool BuildHuffman(const int weights[], int n, HNode tree[]);

/** 求叶子的权值乘根到叶子的边数之和；单叶树为 0。 */
int WeightedPathLength(const HNode tree[], int n);

// --- 参考实现 ---
bool BuildHuffman(const int weights[], int n, HNode tree[]) {
    if (!weights || !tree || n < 1 || n > MAX_SIZE) return false;
    for (int i = 0; i < n; ++i) if (weights[i] <= 0) return false;
    for (int i = 0; i < 2*n-1; ++i) tree[i] = {i < n ? weights[i] : 0, -1, -1, -1};
    for (int i = n; i < 2*n-1; ++i) {
        int a = -1, b = -1;
        // 每轮选择尚无父结点的两个最小权值根；同权按下标优先。
        for (int j = 0; j < i; ++j) if (tree[j].parent == -1) {
            if (a == -1 || tree[j].weight < tree[a].weight) { b = a; a = j; }
            else if (b == -1 || tree[j].weight < tree[b].weight) b = j;
        }
        tree[a].parent = tree[b].parent = i;
        tree[i] = {tree[a].weight + tree[b].weight, -1, a, b};
    }
    return true;
}

int WeightedPathLength(const HNode tree[], int n) {
    int wpl = 0;
    for (int i = 0; i < n; ++i) {
        int depth = 0;
        for (int p = i; tree[p].parent != -1; p = tree[p].parent) ++depth;
        wpl += tree[i].weight * depth;
    }
    return wpl;
}

// --- 测试入口 ---
int main() {
    printf("--- 哈夫曼树与带权路径长度 ---\n");

    int weights[] = {5,7,2,13}; HNode tree[2*MAX_SIZE-1] = {};
    test(BuildHuffman(weights,4,tree)); test(WeightedPathLength(tree,4) == 48);
    test(tree[6].weight == 27 && tree[6].parent == -1);
    int one[] = {9}; test(BuildHuffman(one,1,tree)); test(WeightedPathLength(tree,1) == 0);
    test(!BuildHuffman(one,0,tree)); int bad[] = {-1,2}; test(!BuildHuffman(bad,2,tree));
    return 0;
}
