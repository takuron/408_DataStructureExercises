// 练习：拓扑排序与关键路径
// 参考答案：保留原练习契约和测试，可与 main 分支对照学习。
// 失败操作不得改变原结构或输出参数；动态申请的空间需在销毁时释放。
#include "common.h"

// --- 数据结构定义 ---
constexpr int VMAX = 20;
// AOE 网：-1 无边，>=0 表示活动持续时间（允许零）；对角线 -1。
struct DAG { int weight[VMAX][VMAX]; int n; };

// --- 函数声明与行为契约 ---
/** Kahn 算法；每轮选最小的零入度顶点；返回输出数，有环时小于 n；不修改 G。 */
int TopologicalSort(const DAG &G, int order[]);

/** DAG 中计算事件最早/最迟时间和总工期；允许多源多汇，以所有汇的最大最早时间为总工期；有环返回 false。 */
bool CriticalPath(const DAG &G, int earliest[], int latest[], int &duration);

// --- 参考实现 ---
int TopologicalSort(const DAG &G, int order[]) {
    int indegree[VMAX] = {}; bool emitted[VMAX] = {};
    for (int u = 0; u < G.n; ++u)
        for (int v = 0; v < G.n; ++v) if (G.weight[u][v] >= 0) ++indegree[v];
    int n = 0;
    while (n < G.n) {
        int u = -1;
        for (int v = 0; v < G.n; ++v)
            if (!emitted[v] && indegree[v] == 0) { u = v; break; }
        if (u == -1) break;
        order[n++] = u; emitted[u] = true;
        for (int v = 0; v < G.n; ++v) if (G.weight[u][v] >= 0) --indegree[v];
    }
    return n;
}

bool CriticalPath(const DAG &G, int earliest[], int latest[], int &duration) {
    int order[VMAX];
    if (TopologicalSort(G,order) != G.n) return false;
    int ve[VMAX] = {}, vl[VMAX]; int finish = 0;
    for (int i = 0; i < G.n; ++i) {
        int u = order[i];
        for (int v = 0; v < G.n; ++v) if (G.weight[u][v] >= 0) {
            int candidate = ve[u]+G.weight[u][v];
            if (candidate > ve[v]) ve[v] = candidate;
        }
        if (ve[u] > finish) finish = ve[u];
    }
    // 等价于所有汇点接到一个零权超级汇点，故均以总工期初始化。
    for (int u = 0; u < G.n; ++u) vl[u] = finish;
    for (int i = G.n-1; i >= 0; --i) {
        int u = order[i];
        for (int v = 0; v < G.n; ++v) if (G.weight[u][v] >= 0) {
            int candidate = vl[v]-G.weight[u][v];
            if (candidate < vl[u]) vl[u] = candidate;
        }
    }
    for (int u = 0; u < G.n; ++u) { earliest[u] = ve[u]; latest[u] = vl[u]; }
    duration = finish;
    return true;
}

// --- 测试入口 ---
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
