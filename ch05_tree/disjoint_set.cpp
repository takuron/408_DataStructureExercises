// 练习：并查集（路径压缩、按规模合并）
// 只提供契约、桩函数和测试；请自行完成 TODO。
// 失败操作不得改变原结构或输出参数；动态申请的空间需在销毁时释放。
#include "common.h"

// --- 数据结构定义 ---
// 根的 parent 为负数，绝对值为集合规模；非根保存父下标。
typedef struct DSU {
    int parent[MAX_SIZE];
    int n;
} DSU;

// --- 函数声明与行为契约 ---
/** 初始化 n 个单元素集合；n 范围 [0,MAX_SIZE]，非法返回 false。 */
bool InitSet(DSU &S, int n);

/** 查找根并压缩路径；非法下标返回 -1。 */
int Find(DSU &S, int x);

/** 按集合规模合并；同集合或非法下标返回 false，成功合并返回 true。 */
bool Union(DSU &S, int a, int b);

// --- 在此处编写实现 ---
bool InitSet(DSU &S, int n) {
    // TODO: 初始化 n 个单元素集合；n 范围 [0,MAX_SIZE]，非法返回 false。
    return false;
}

int Find(DSU &S, int x) {
    // TODO: 查找根并压缩路径；非法下标返回 -1。
    return -1;
}

bool Union(DSU &S, int a, int b) {
    // TODO: 按集合规模合并；同集合或非法下标返回 false，成功合并返回 true。
    return false;
}

// --- 测试入口：未实现时出现 FAIL 是正常现象 ---
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
