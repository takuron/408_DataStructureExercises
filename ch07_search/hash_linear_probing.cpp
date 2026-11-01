// 练习：散列表：线性探测
// 参考答案：保留原练习契约和测试，可与 main 分支对照学习。
// 失败操作不得改变原结构或输出参数；动态申请的空间需在销毁时释放。
#include "common.h"

// --- 数据结构定义 ---
constexpr int TABLE_SIZE = 11;
enum SlotState { EMPTY, OCCUPIED, DELETED };
struct HashTable { int key[TABLE_SIZE]; SlotState state[TABLE_SIZE]; };

// --- 函数声明与行为契约 ---
/** 把所有槽标记为 EMPTY；关键字数组无需清零。 */
void InitHash(HashTable &H);

/** 散列地址 ((key%11)+11)%11；线性探测，越过 DELETED；匹配返回槽下标，否则 -1。 */
int Search(const HashTable &H, int key);

/** 重复键或满表返回 false；可复用 DELETED 槽，但须先确定没有重复键；最多探测 TABLE_SIZE 次。 */
bool Insert(HashTable &H, int key);

/** 找到后标记 DELETED，不可直接置 EMPTY；不存在返回 false。 */
bool Delete(HashTable &H, int key);

// --- 参考实现 ---
void InitHash(HashTable &H) {
    for (int i = 0; i < TABLE_SIZE; ++i) H.state[i] = EMPTY;
}

int Search(const HashTable &H, int key) {
    int start = ((key % TABLE_SIZE) + TABLE_SIZE) % TABLE_SIZE;
    for (int i = 0; i < TABLE_SIZE; ++i) {
        int p = (start+i) % TABLE_SIZE;
        if (H.state[p] == EMPTY) return -1;
        if (H.state[p] == OCCUPIED && H.key[p] == key) return p;
    }
    return -1;
}

bool Insert(HashTable &H, int key) {
    if (Search(H,key) != -1) return false;
    int start = ((key % TABLE_SIZE) + TABLE_SIZE) % TABLE_SIZE;
    for (int i = 0; i < TABLE_SIZE; ++i) {
        int p = (start+i) % TABLE_SIZE;
        if (H.state[p] != OCCUPIED) {
            H.key[p] = key; H.state[p] = OCCUPIED; return true;
        }
    }
    return false;
}

bool Delete(HashTable &H, int key) {
    int p = Search(H,key);
    if (p == -1) return false;
    H.state[p] = DELETED;
    return true;
}

// --- 测试入口 ---
int main() {
    printf("--- 散列表：线性探测 ---\n");

    HashTable H{}; InitHash(H);
    test(Insert(H,1)); test(Insert(H,12)); test(Insert(H,23));
    test(!Insert(H,12)); test(Delete(H,1)); test(Search(H,23) >= 0);
    test(!Insert(H,23)); test(Insert(H,-10)); test(Search(H,-10) >= 0);
    test(!Delete(H,99)); InitHash(H);
    for (int i = 0; i < TABLE_SIZE; ++i) test(Insert(H,i*TABLE_SIZE));
    test(!Insert(H,999)); test(Search(H,999) == -1);
    test(Delete(H,0)); test(Insert(H,999));
    return 0;
}
