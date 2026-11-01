// 练习：Dijkstra 与 Floyd 最短路径
// 参考答案：保留原练习契约和测试，可与 main 分支对照学习。
// 失败操作不得改变原结构或输出参数；动态申请的空间需在销毁时释放。
#include "common.h"

// --- 数据结构定义 ---
constexpr int VMAX = 20;
constexpr int INF = 0x3f3f3f3f;
// 对角线 0；无边 INF；0 权边合法。测试用权值总和小于 INF。
struct Graph { int w[VMAX][VMAX]; int n; };

// --- 函数声明与行为契约 ---
/** 有向非负权图；输出距离及前驱，源前驱/不可达前驱 -1，不可达距离 INF；非法源返回 false。 */
bool Dijkstra(const Graph &G, int source, int dist[], int parent[]);

/** 输出所有顶点对距离；允许负边但约定无负环；INF 不可直接参与相加。 */
void Floyd(const Graph &G, int dist[][VMAX]);

// --- 参考实现 ---
bool Dijkstra(const Graph &G, int source, int dist[], int parent[]) {
    if (source < 0 || source >= G.n) return false;
    bool selected[VMAX] = {};
    for (int v = 0; v < G.n; ++v) { dist[v] = INF; parent[v] = -1; }
    dist[source] = 0;
    for (int i = 0; i < G.n; ++i) {
        int u = -1;
        for (int v = 0; v < G.n; ++v)
            if (!selected[v] && (u == -1 || dist[v] < dist[u])) u = v;
        if (u == -1 || dist[u] == INF) break;
        selected[u] = true;
        for (int v = 0; v < G.n; ++v) {
            if (selected[v] || G.w[u][v] == INF) continue;
            if (dist[u] + G.w[u][v] < dist[v]) {
                dist[v] = dist[u] + G.w[u][v]; parent[v] = u;
            }
        }
    }
    return true;
}

void Floyd(const Graph &G, int dist[][VMAX]) {
    for (int i = 0; i < G.n; ++i)
        for (int j = 0; j < G.n; ++j) dist[i][j] = G.w[i][j];
    // 中转点 k 必须放在最外层。
    for (int k = 0; k < G.n; ++k)
        for (int i = 0; i < G.n; ++i)
            for (int j = 0; j < G.n; ++j)
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
}

// --- 测试入口 ---
int main() {
    printf("--- Dijkstra 与 Floyd 最短路径 ---\n");
    Graph G{}; G.n = 4;
    for (int i = 0; i < G.n; ++i)
        for (int j = 0; j < G.n; ++j) G.w[i][j] = i == j ? 0 : INF;

    G.w[0][1] = 2; G.w[0][2] = 9; G.w[1][2] = 3;
    int dist[VMAX] = {}, parent[VMAX] = {}, all[VMAX][VMAX] = {};
    test(Dijkstra(G,0,dist,parent));
    test(dist[0] == 0 && dist[1] == 2 && dist[2] == 5 && dist[3] == INF);
    test(parent[0] == -1 && parent[2] == 1 && parent[3] == -1);
    test(!Dijkstra(G,-1,dist,parent)); Floyd(G,all);
    test(all[0][2] == 5 && all[2][0] == INF && all[3][3] == 0);
    G.w[1][2] = -1; Floyd(G,all); test(all[0][2] == 1);
    return 0;
}
