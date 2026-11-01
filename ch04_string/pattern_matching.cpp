// 练习：朴素匹配与 KMP
// 只提供契约、桩函数和测试；请自行完成 TODO。
// 本文件统一使用 0 基下标，勿混用教材 1 基 next 表；不要求 nextval 优化。
#include "common.h"

// --- 数据结构定义 ---


// --- 函数声明与行为契约 ---
/** 返回首次匹配的 0 基下标，未找到/空指针返回 -1；空模式返回 0。 */
int IndexNaive(const char *text, const char *pattern);

/** 使用 0 基约定：next[0]=-1；next[j] 是模式 j 失配后回退的模式下标；长度 m，数组至少 m 格。 */
void BuildNext(const char *pattern, int next[]);

/** 行为与朴素匹配一致；使用 BuildNext，时间 O(n+m)；正确处理空模式。 */
int IndexKMP(const char *text, const char *pattern);

// --- 在此处编写实现 ---
int IndexNaive(const char *text, const char *pattern) {
    // TODO: 返回首次匹配的 0 基下标，未找到/空指针返回 -1；空模式返回 0。
    return -1;
}

void BuildNext(const char *pattern, int next[]) {
    // TODO: 使用 0 基约定：next[0]=-1；next[j] 是模式 j 失配后回退的模式下标；长度 m，数组至少 m 格。
    (void)pattern; (void)next;
}

int IndexKMP(const char *text, const char *pattern) {
    // TODO: 行为与朴素匹配一致；使用 BuildNext，时间 O(n+m)；正确处理空模式。
    return -1;
}

// --- 测试入口：未实现时出现 FAIL 是正常现象 ---
int main() {
    printf("--- 朴素匹配与 KMP ---\n");

    const char *texts[] = {"ababcabcacbab", "aaaaab", "abc", "", "abc", "abc"};
    const char *patterns[] = {"abcac", "aaab", "z", "a", "", "abc"};
    int expected[] = {5, 2, -1, -1, 0, 0};
    for (int i = 0; i < 6; ++i) {
        test(IndexNaive(texts[i], patterns[i]) == expected[i]);
        test(IndexKMP(texts[i], patterns[i]) == expected[i]);
    }
    int next[7] = {}; BuildNext("ababaca", next);
    int expectedNext[] = {-1, 0, 0, 1, 2, 3, 0};
    test(memcmp(next, expectedNext, sizeof(next)) == 0);
    test(IndexKMP(nullptr, "a") == -1);
    return 0;
}
