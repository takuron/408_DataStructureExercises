// 练习：图的邻接矩阵与邻接表
// 只提供契约、桩函数和测试；请自行完成 TODO。
// 失败操作不得改变原结构或输出参数；动态申请的空间需在销毁时释放。
#include "common.h"

// --- 数据结构定义 ---
constexpr int VMAX = 20;
// 本文件为无权无向简单图；矩阵 0 表示无边，1 表示有边。
struct MGraph { int edge[VMAX][VMAX]; int n, m; };
struct ArcNode { int adjvex; ArcNode *next; };
struct ALGraph { ArcNode *head[VMAX]; int n, m; };

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

// --- 在此处编写实现 ---
bool InitGraph(MGraph &G, int n) {
    // TODO: n 范围 [0,VMAX]；清空矩阵，设置顶点数，边数置零。
    return false;
}

bool AddEdge(MGraph &G, int u, int v) {
    // TODO: 顶点为 0 基下标；插入无向边并更新边数；越界、自环、重边返回 false。
    return false;
}

bool ToAdjList(const MGraph &G, ALGraph &A) {
    // TODO: 向空邻接表 A 转换；每条无向边存两条弧；分配失败清理部分结果并返回 false。
    return false;
}

int Degree(const ALGraph &G, int v) {
    // TODO: 返回顶点度数；非法下标返回 -1。
    return -1;
}

void DestroyGraph(ALGraph &G) {
    // TODO: 释放所有弧结点，清空 head，n 和 m 置零。
    (void)G;
}

// --- 测试入口：未实现时出现 FAIL 是正常现象 ---
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
