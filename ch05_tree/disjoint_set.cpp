// 练习：并查集（路径压缩、按规模合并）
// 参考答案：保留原练习契约和测试，可与 main 分支对照学习。
// 失败操作不得改变原结构或输出参数；动态申请的空间需在销毁时释放。
#include "common.h"

// --- 数据结构定义 ---
// 根的 parent 为负数，绝对值为集合规模；非根保存父下标。
struct DSU { int parent[MAX_SIZE]; int n; };

// --- 函数声明与行为契约 ---
/** 初始化 n 个单元素集合；n 范围 [0,MAX_SIZE]，非法返回 false。 */
bool InitSet(DSU &S, int n);

/** 查找根并压缩路径；非法下标返回 -1。 */
int Find(DSU &S, int x);

/** 按集合规模合并；同集合或非法下标返回 false，成功合并返回 true。 */
bool Union(DSU &S, int a, int b);

// --- 参考实现 ---
bool InitSet(DSU &S, int n) {
    if (n < 0 || n > MAX_SIZE) return false;
    S.n = n;
    for (int i = 0; i < n; ++i) S.parent[i] = -1;
    return true;
}

int Find(DSU &S, int x) {
    if (x < 0 || x >= S.n) return -1;
    if (S.parent[x] < 0) return x;
    return S.parent[x] = Find(S, S.parent[x]);
}

bool Union(DSU &S, int a, int b) {
    if (a < 0 || a >= S.n || b < 0 || b >= S.n) return false;
    // 先只读查根，使“已在同一集合”的失败操作不改变 parent 数组。
    int ra = a, rb = b;
    while (S.parent[ra] >= 0) ra = S.parent[ra];
    while (S.parent[rb] >= 0) rb = S.parent[rb];
    if (ra == rb) return false;
    Find(S,a); Find(S,b);
    // 负数的绝对值越大，集合越大；保证 ra 为较大集合。
    if (S.parent[ra] > S.parent[rb]) { int t = ra; ra = rb; rb = t; }
    S.parent[ra] += S.parent[rb];
    S.parent[rb] = ra;
    return true;
}

// --- 测试入口 ---
int main() {
    printf("--- 并查集（路径压缩、按规模合并） ---\n");

    DSU S{}; test(InitSet(S, 6));
    test(Find(S, 0) == 0); test(Union(S, 0, 1)); test(Union(S, 2, 3));
    test(Union(S, 1, 3)); int r = Find(S, 0);
    test(r >= 0 && r < S.n && Find(S, 3) == r && S.parent[r] == -4);
    test(!Union(S, 0, 3)); test(Find(S, -1) == -1); test(Find(S, 6) == -1);
    test(!Union(S, 0, 9)); test(!InitSet(S, MAX_SIZE + 1));
    return 0;
}
