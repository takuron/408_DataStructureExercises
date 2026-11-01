// 练习：Prim 与 Kruskal 最小生成树
// 参考答案：保留原练习契约和测试，可与 main 分支对照学习。
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

static int SetRoot(int parent[], int x) {
    if (parent[x] < 0) return x;
    return parent[x] = SetRoot(parent,parent[x]);
}

// --- 参考实现 ---
bool Prim(const Graph &G, int &total) {
    if (G.n == 0) { total = 0; return true; }
    int low[VMAX]; bool selected[VMAX] = {}; int sum = 0;
    for (int v = 0; v < G.n; ++v) low[v] = INF;
    low[0] = 0;
    for (int i = 0; i < G.n; ++i) {
        int u = -1;
        for (int v = 0; v < G.n; ++v)
            if (!selected[v] && (u == -1 || low[v] < low[u])) u = v;
        if (u == -1 || low[u] == INF) return false;
        selected[u] = true; sum += low[u];
        for (int v = 0; v < G.n; ++v)
            if (!selected[v] && G.w[u][v] < low[v]) low[v] = G.w[u][v];
    }
    total = sum;
    return true;
}

bool Kruskal(const Graph &G, int &total) {
    struct Edge { int u, v, w; } edges[VMAX*(VMAX-1)/2];
    int count = 0;
    for (int u = 0; u < G.n; ++u)
        for (int v = u+1; v < G.n; ++v)
            if (G.w[u][v] != INF) edges[count++] = {u,v,G.w[u][v]};
    // 手写插入排序，避免依赖 STL 算法。
    for (int i = 1; i < count; ++i) {
        Edge e = edges[i]; int j = i-1;
        while (j >= 0 && edges[j].w > e.w) { edges[j+1] = edges[j]; --j; }
        edges[j+1] = e;
    }
    int parent[VMAX];
    for (int i = 0; i < G.n; ++i) parent[i] = -1;
    int selected = 0, sum = 0;
    for (int i = 0; i < count && selected < G.n-1; ++i) {
        int a = SetRoot(parent,edges[i].u), b = SetRoot(parent,edges[i].v);
        if (a == b) continue;
        if (parent[a] > parent[b]) { int t = a; a = b; b = t; }
        parent[a] += parent[b]; parent[b] = a;
        sum += edges[i].w; ++selected;
    }
    if (G.n > 0 && selected != G.n-1) return false;
    total = sum;
    return true;
}

// --- 测试入口 ---
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
