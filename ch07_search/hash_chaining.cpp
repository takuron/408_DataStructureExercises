// 练习：散列表：拉链法
// 参考答案：保留原练习契约和测试，可与 main 分支对照学习。
// 失败操作不得改变原结构或输出参数；动态申请的空间需在销毁时释放。
#include "common.h"

// --- 数据结构定义 ---
constexpr int BUCKETS = 11;
typedef struct HashNode {
    int key;
    struct HashNode *next;
} HashNode;
typedef struct HashTable {
    HashNode *bucket[BUCKETS];
} HashTable;

// --- 函数声明与行为契约 ---
/** 桶号 ((key%BUCKETS)+BUCKETS)%BUCKETS；重复键或分配失败返回 false；头插结点。 */
bool Insert(HashTable &H, int key);

/** 在对应桶中查找；存在返回 true。 */
bool Search(const HashTable &H, int key);

/** 删除并释放匹配结点；不存在返回 false。 */
bool Delete(HashTable &H, int key);

/** 释放所有桶链并将桶头置空。 */
void DestroyHash(HashTable &H);

// --- 参考实现 ---
bool Insert(HashTable &H, int key) {
    if (Search(H,key)) return false;
    int b = ((key % BUCKETS) + BUCKETS) % BUCKETS;
    HashNode *p = static_cast<HashNode *>(malloc(sizeof(HashNode)));
    if (!p) return false;
    *p = {key, H.bucket[b]}; H.bucket[b] = p;
    return true;
}

bool Search(const HashTable &H, int key) {
    int b = ((key % BUCKETS) + BUCKETS) % BUCKETS;
    for (HashNode *p = H.bucket[b]; p; p = p->next) if (p->key == key) return true;
    return false;
}

bool Delete(HashTable &H, int key) {
    int b = ((key % BUCKETS) + BUCKETS) % BUCKETS;
    // 指向链接的指针统一处理删除桶头和中间结点。
    HashNode **link = &H.bucket[b];
    while (*link && (*link)->key != key) link = &(*link)->next;
    if (!*link) return false;
    HashNode *p = *link; *link = p->next; free(p);
    return true;
}

void DestroyHash(HashTable &H) {
    for (int b = 0; b < BUCKETS; ++b)
        while (H.bucket[b]) {
            HashNode *p = H.bucket[b]; H.bucket[b] = p->next; free(p);
        }
}

// --- 测试入口 ---
int main() {
    printf("--- 散列表：拉链法 ---\n");

    HashTable H{}; test(Insert(H,1)); test(Insert(H,12)); test(Insert(H,-10));
    test(Search(H,12)); test(!Search(H,99)); test(!Insert(H,12));
    test(Delete(H,12)); test(!Search(H,12)); test(Search(H,1));
    test(Delete(H,-10)); test(!Delete(H,99)); DestroyHash(H);
    for (auto p : H.bucket) test(p == nullptr);
    return 0;
}
