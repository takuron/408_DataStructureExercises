// 练习：图的邻接矩阵与邻接表
// 参考答案：保留原练习契约和测试，可与 main 分支对照学习。
// 失败操作不得改变原结构或输出参数；动态申请的空间需在销毁时释放。
#include "common.h"

// --- 数据结构定义 ---
constexpr int VMAX = 20;
// 本文件为无权无向简单图；矩阵 0 表示无边，1 表示有边。
typedef struct MGraph {
    int edge[VMAX][VMAX];
    int n, m;
} MGraph;
typedef struct ArcNode {
    int adjvex;
    struct ArcNode *next;
} ArcNode;
typedef struct ALGraph {
    ArcNode *head[VMAX];
    int n, m;
} ALGraph;

// --- 函数声明与行为契约 ---
/** n 范围 [0,VMAX]；清空矩阵，设置顶点数，边数置零。 */
bool InitGraph(MGraph &G, int n);

/** 顶点为 0 基下标；插入无向边并更新边数；越界、自环、重边返回 false。 */
bool AddEdge(MGraph &G, int u, int v);

/** 向空邻接表 A 转换；每条无向边存两条弧；分配失败清理部分结果并返回 false。 */
bool ToAdjList(const MGraph &G, ALGraph &A);

/** 返回顶点度数；非法下标返回 -1。 */
int Degree(const ALGraph &G, int v);

/** 释放所有弧结点，清空 head，n 和 m 置零。 */
void DestroyGraph(ALGraph &G);

// --- 参考实现 ---
bool InitGraph(MGraph &G, int n) {
    if (n < 0 || n > VMAX) return false;
    G = {}; G.n = n;
    return true;
}

bool AddEdge(MGraph &G, int u, int v) {
    if (u < 0 || u >= G.n || v < 0 || v >= G.n || u == v || G.edge[u][v]) return false;
    G.edge[u][v] = G.edge[v][u] = 1; ++G.m;
    return true;
}

bool ToAdjList(const MGraph &G, ALGraph &A) {
    ALGraph temp{}; temp.n = G.n; temp.m = G.m;
    for (int u = 0; u < G.n; ++u) {
        // 头插时按下标降序扫描，使最终链表按下标递增。
        for (int v = G.n-1; v >= 0; --v) if (G.edge[u][v]) {
            ArcNode *p = static_cast<ArcNode *>(malloc(sizeof(ArcNode)));
            if (!p) { DestroyGraph(temp); return false; }
            *p = {v, temp.head[u]}; temp.head[u] = p;
        }
    }
    A = temp;
    return true;
}

int Degree(const ALGraph &G, int v) {
    if (v < 0 || v >= G.n) return -1;
    int degree = 0;
    for (ArcNode *p = G.head[v]; p; p = p->next) ++degree;
    return degree;
}

void DestroyGraph(ALGraph &G) {
    for (int u = 0; u < G.n; ++u)
        while (G.head[u]) { ArcNode *p = G.head[u]; G.head[u] = p->next; free(p); }
    G = {};
}

// --- 测试入口 ---
int main() {
    printf("--- 图的邻接矩阵与邻接表 ---\n");

    MGraph G{}; ALGraph A{}; test(InitGraph(G,4));
    test(AddEdge(G,0,1)); test(AddEdge(G,0,2));
    test(G.m == 2 && G.edge[1][0] == 1); test(!AddEdge(G,0,1));
    test(!AddEdge(G,0,0)); test(!AddEdge(G,-1,2));
    test(ToAdjList(G,A)); test(A.n == 4 && A.m == 2);
    test(Degree(A,0) == 2); test(Degree(A,3) == 0); test(Degree(A,4) == -1);
    DestroyGraph(A); test(A.n == 0 && A.m == 0);
    for (auto p : A.head) test(p == nullptr);
    return 0;
}
