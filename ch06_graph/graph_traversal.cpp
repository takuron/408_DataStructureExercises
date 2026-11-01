// 练习：图的 DFS、BFS 与无权最短路径
// 只提供契约、桩函数和测试；请自行完成 TODO。
// 合法图：n<=VMAX，edge 为 0/1；允许非连通图；输出数组至少 VMAX 格；每次遍历重置访问标记。
#include "common.h"

// --- 数据结构定义 ---
constexpr int VMAX = 20;
typedef struct Graph {
    int edge[VMAX][VMAX];
    int n;
} Graph;

// --- 函数声明与行为契约 ---
/** 递归 DFS 遍历整个图；起点和邻接点均按下标递增选择；返回输出顶点数。 */
int DFSTraverse(const Graph &G, int out[]);

/** 用手写队列 BFS 遍历整个图；入队时标记；按下标递增选择；返回输出数。 */
int BFSTraverse(const Graph &G, int out[]);

/** 单源 BFS；距离按边数，源距离 0；不可达距离和前驱均为 -1，源前驱 -1；非法源返回 false。 */
bool BFSShortestPath(const Graph &G, int source, int dist[], int parent[]);

// --- 在此处编写实现 ---
int DFSTraverse(const Graph &G, int out[]) {
    // TODO: 递归 DFS 遍历整个图；起点和邻接点均按下标递增选择；返回输出顶点数。
    return 0;
}

int BFSTraverse(const Graph &G, int out[]) {
    // TODO: 用手写队列 BFS 遍历整个图；入队时标记；按下标递增选择；返回输出数。
    return 0;
}

bool BFSShortestPath(const Graph &G, int source, int dist[], int parent[]) {
    // TODO: 单源 BFS；距离按边数，源距离 0；不可达距离和前驱均为 -1，源前驱 -1；非法源返回 false。
    return false;
}

// --- 测试入口：未实现时出现 FAIL 是正常现象 ---
int main() {
    printf("--- 图的 DFS、BFS 与无权最短路径 ---\n");

    Graph G{}; G.n = 6;
    int edges[][2] = {{0,1},{0,2},{1,3},{2,3},{4,5}};
    for (auto &e : edges) G.edge[e[0]][e[1]] = G.edge[e[1]][e[0]] = 1;
    int out[VMAX] = {}, dfs[] = {0,1,3,2,4,5}, bfs[] = {0,1,2,3,4,5};
    test(DFSTraverse(G,out) == 6 && memcmp(out,dfs,sizeof(dfs)) == 0);
    test(BFSTraverse(G,out) == 6 && memcmp(out,bfs,sizeof(bfs)) == 0);
    int dist[VMAX] = {}, parent[VMAX] = {};
    test(BFSShortestPath(G,0,dist,parent));
    test(dist[0] == 0 && dist[3] == 2 && dist[4] == -1);
    test(parent[0] == -1 && parent[3] == 1 && parent[5] == -1);
    test(!BFSShortestPath(G,6,dist,parent)); Graph empty{};
    test(DFSTraverse(empty,out) == 0); test(BFSTraverse(empty,out) == 0);
    return 0;
}
