// 练习：Prim 与 Kruskal 最小生成树
// 只提供契约、桩函数和测试；请自行完成 TODO。
// 失败操作不得改变原结构或输出参数；动态申请的空间需在销毁时释放。
#include "common.h"

// --- 数据结构定义 ---
constexpr int VMAX = 20;
constexpr int INF = 0x3f3f3f3f;
// 对角线 0；无边 INF；0 权边合法。测试用权值总和小于 INF。
struct Graph { int w[VMAX][VMAX]; int n; };

// --- 函数声明与行为契约 ---
/** 无向非负权图，从顶点 0 开始；连通则 total 带回 MST 权值并返回 true；空图权值 0；不连通返回 false。 */
bool Prim(const Graph &G, int &total);

/** 提取无向边，按权递增，用并查集判环；返回约定同 Prim。 */
bool Kruskal(const Graph &G, int &total);

// --- 在此处编写实现 ---
bool Prim(const Graph &G, int &total) {
    // TODO: 无向非负权图，从顶点 0 开始；连通则 total 带回 MST 权值并返回 true；空图权值 0；不连通返回 false。
    return false;
}

bool Kruskal(const Graph &G, int &total) {
    // TODO: 提取无向边，按权递增，用并查集判环；返回约定同 Prim。
    return false;
}

// --- 测试入口：未实现时出现 FAIL 是正常现象 ---
int main() {
    printf("--- Prim 与 Kruskal 最小生成树 ---\n");
    Graph G{}; G.n = 4;
    for (int i = 0; i < G.n; ++i)
        for (int j = 0; j < G.n; ++j) G.w[i][j] = i == j ? 0 : INF;

    int edges[][3] = {{0,1,1},{0,2,4},{1,2,2},{1,3,5},{2,3,3}};
    for (auto &e : edges) G.w[e[0]][e[1]] = G.w[e[1]][e[0]] = e[2];
    int total = -1; test(Prim(G,total) && total == 6);
    test(Kruskal(G,total) && total == 6);
    G.w[1][3] = G.w[3][1] = G.w[2][3] = G.w[3][2] = INF;
    test(!Prim(G,total)); test(!Kruskal(G,total));
    Graph empty{}; test(Prim(empty,total) && total == 0);
    test(Kruskal(empty,total) && total == 0);
    return 0;
}
