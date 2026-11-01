// 练习：哈夫曼树与带权路径长度
// 只提供契约、桩函数和测试；请自行完成 TODO。
// tree 容量至少 2*n-1；同权结点可任选，但 WPL 必须最小；测试权值总和保证不溢出 int。
#include "common.h"

// --- 数据结构定义 ---
// 0 基：前 n 项是叶子，后 n-1 项是内部结点；-1 表示无父/孩子。
typedef struct HNode {
    int weight, parent, left, right;
} HNode;

// --- 函数声明与行为契约 ---
/** n 范围 [1,MAX_SIZE]，权值为正；构造 2*n-1 个结点，根下标 2*n-2；非法输入返回 false。 */
bool BuildHuffman(const int weights[], int n, HNode tree[]);

/** 求叶子的权值乘根到叶子的边数之和；单叶树为 0。 */
int WeightedPathLength(const HNode tree[], int n);

// --- 在此处编写实现 ---
bool BuildHuffman(const int weights[], int n, HNode tree[]) {
    // TODO: n 范围 [1,MAX_SIZE]，权值为正；构造 2*n-1 个结点，根下标 2*n-2；非法输入返回 false。
    return false;
}

int WeightedPathLength(const HNode tree[], int n) {
    // TODO: 求叶子的权值乘根到叶子的边数之和；单叶树为 0。
    return -1;
}

// --- 测试入口：未实现时出现 FAIL 是正常现象 ---
int main() {
    printf("--- 哈夫曼树与带权路径长度 ---\n");

    int weights[] = {5,7,2,13}; HNode tree[2*MAX_SIZE-1] = {};
    test(BuildHuffman(weights,4,tree)); test(WeightedPathLength(tree,4) == 48);
    test(tree[6].weight == 27 && tree[6].parent == -1);
    int one[] = {9}; test(BuildHuffman(one,1,tree)); test(WeightedPathLength(tree,1) == 0);
    test(!BuildHuffman(one,0,tree)); int bad[] = {-1,2}; test(!BuildHuffman(bad,2,tree));
    return 0;
}
