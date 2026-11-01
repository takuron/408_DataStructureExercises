// 练习：拓扑排序与关键路径
// 只提供契约、桩函数和测试；请自行完成 TODO。
// 失败操作不得改变原结构或输出参数；动态申请的空间需在销毁时释放。
#include "common.h"

// --- 数据结构定义 ---
constexpr int VMAX = 20;
// AOE 网：-1 无边，>=0 表示活动持续时间（允许零）；对角线 -1。
typedef struct DAG {
    int weight[VMAX][VMAX];
    int n;
} DAG;

// --- 函数声明与行为契约 ---
/** Kahn 算法；每轮选最小的零入度顶点；返回输出数，有环时小于 n；不修改 G。 */
int TopologicalSort(const DAG &G, int order[]);

/** DAG 中计算事件最早/最迟时间和总工期；允许多源多汇，以所有汇的最大最早时间为总工期；有环返回 false。 */
bool CriticalPath(const DAG &G, int earliest[], int latest[], int &duration);

// --- 在此处编写实现 ---
int TopologicalSort(const DAG &G, int order[]) {
    // TODO: Kahn 算法；每轮选最小的零入度顶点；返回输出数，有环时小于 n；不修改 G。
    return 0;
}

bool CriticalPath(const DAG &G, int earliest[], int latest[], int &duration) {
    // TODO: DAG 中计算事件最早/最迟时间和总工期；允许多源多汇，以所有汇的最大最早时间为总工期；有环返回 false。
    return false;
}

// --- 测试入口：未实现时出现 FAIL 是正常现象 ---
int main() {
    printf("--- 拓扑排序与关键路径 ---\n");

    DAG G{}; G.n = 4;
    for (auto &row : G.weight) for (int &w : row) w = -1;
    G.weight[0][1] = 3; G.weight[0][2] = 2;
    G.weight[1][3] = 2; G.weight[2][3] = 4;
    int order[VMAX] = {}, expected[] = {0,1,2,3};
    test(TopologicalSort(G,order) == 4 && memcmp(order,expected,sizeof(expected)) == 0);
    int ve[VMAX] = {}, vl[VMAX] = {}, duration = -1;
    test(CriticalPath(G,ve,vl,duration) && duration == 6);
    test(ve[1] == 3 && ve[2] == 2 && vl[1] == 4 && vl[2] == 2);
    // 活动 u->v 关键当且仅当 ve[u] == vl[v]-weight[u][v]。
    test(ve[0] == vl[2]-G.weight[0][2]);
    G.weight[3][0] = 1; test(TopologicalSort(G,order) < G.n);
    test(!CriticalPath(G,ve,vl,duration));
    return 0;
}
