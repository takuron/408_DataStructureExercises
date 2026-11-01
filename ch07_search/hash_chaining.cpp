// 练习：散列表：拉链法
// 只提供契约、桩函数和测试；请自行完成 TODO。
// 失败操作不得改变原结构或输出参数；动态申请的空间需在销毁时释放。
#include "common.h"

// --- 数据结构定义 ---
constexpr int BUCKETS = 11;
struct HashNode { int key; HashNode *next; };
struct HashTable { HashNode *bucket[BUCKETS]; };

// --- 函数声明与行为契约 ---
/** 桶号 ((key%BUCKETS)+BUCKETS)%BUCKETS；重复键或分配失败返回 false；头插结点。 */
bool Insert(HashTable &H, int key);

/** 在对应桶中查找；存在返回 true。 */
bool Search(const HashTable &H, int key);

/** 删除并释放匹配结点；不存在返回 false。 */
bool Delete(HashTable &H, int key);

/** 释放所有桶链并将桶头置空。 */
void DestroyHash(HashTable &H);

// --- 在此处编写实现 ---
bool Insert(HashTable &H, int key) {
    // TODO: 桶号 ((key%BUCKETS)+BUCKETS)%BUCKETS；重复键或分配失败返回 false；头插结点。
    return false;
}

bool Search(const HashTable &H, int key) {
    // TODO: 在对应桶中查找；存在返回 true。
    return false;
}

bool Delete(HashTable &H, int key) {
    // TODO: 删除并释放匹配结点；不存在返回 false。
    return false;
}

void DestroyHash(HashTable &H) {
    // TODO: 释放所有桶链并将桶头置空。
    (void)H;
}

// --- 测试入口：未实现时出现 FAIL 是正常现象 ---
int main() {
    printf("--- 散列表：拉链法 ---\n");

    HashTable H{}; test(Insert(H,1)); test(Insert(H,12)); test(Insert(H,-10));
    test(Search(H,12)); test(!Search(H,99)); test(!Insert(H,12));
    test(Delete(H,12)); test(!Search(H,12)); test(Search(H,1));
    test(Delete(H,-10)); test(!Delete(H,99)); DestroyHash(H);
    for (auto p : H.bucket) test(p == nullptr);
    return 0;
}
