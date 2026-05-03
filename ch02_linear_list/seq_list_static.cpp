#include "common.h"

// 1. 定义顺序表结构 (静态分配方式)
#define MaxSize 50 // 静态数组的最大容量

typedef struct {
    int data[MaxSize]; // 静态分配的数组，固定大小
    int length;        // 顺序表的当前实际长度
} SeqList;

// ==========================================
// 2. 待实现的方法声明与行为契约 (Contract)
// ==========================================

/**
 * 初始化顺序表
 * @param L 顺序表的引用。
 * @return 始终返回 true。
 * @behavior 需要将顺序表的当前长度 length 初始化为 0。静态数组的元素默认值是未定义的脏数据，无需遍历清零，只需控制 length 即可。
 */
bool InitList(SeqList &L);

/**
 * 插入元素
 * @param L 顺序表的引用。
 * @param i 插入的位置（位序），范围应为 [1, L.length + 1]。
 * @param e 需要插入的元素值。
 * @return 插入成功返回 true；如果 i 越界或表已满，返回 false。
 * @behavior 在第 i 个位置插入元素 e。需要将第 i 个及之后的元素整体向后移动一位，然后将 e 放入指定位置，最后 length + 1。
 */
bool ListInsert(SeqList &L, int i, int e);

/**
 * 删除元素
 * @param L 顺序表的引用。
 * @param i 删除的位置（位序），范围应为 [1, L.length]。
 * @param e 引用参数，用于带回被删除的元素值。
 * @return 删除成功返回 true；如果 i 越界或表为空，返回 false。
 * @behavior 删除第 i 个位置的元素，将其值赋给 e。然后将第 i 个位置之后的元素整体向前移动一位，最后 length - 1。
 */
bool ListDelete(SeqList &L, int i, int &e);

/**
 * 按值查找
 * @param L 顺序表（值传递即可，无需修改）。
 * @param e 需要查找的目标值。
 * @return 查找成功返回元素所在的位序（[1, L.length]）；如果未找到，返回 0。
 * @behavior 从前往后遍历顺序表，返回第一个值等于 e 的元素的位序（非数组下标）。
 */
int LocateElem(SeqList L, int e);

/**
 * 按位查找
 * @param L 顺序表。
 * @param i 查找的位置（位序），范围应为 [1, L.length]。
 * @param e 引用参数，用于带回查找到的元素值。
 * @return 查找成功返回 true；如果 i 越界，返回 false。
 * @behavior 检查 i 是否合法，合法则将第 i 个位置的元素赋值给 e。
 */
bool GetElem(SeqList L, int i, int &e);

/**
 * 获取当前长度
 * @param L 顺序表。
 * @return 返回顺序表当前的元素个数 L.length。
 */
int Length(SeqList L);

/**
 * 打印顺序表
 * @param L 顺序表。
 * @behavior 遍历并按顺序打印表中所有有效元素（0 到 length-1），建议使用 printf("%d ", L.data[x]) 格式。
 */
void PrintList(SeqList L);


// ==========================================
// [在此处编写你的实现代码]
// ==========================================

bool InitList(SeqList &L) {
    L.length = 0;
    return true;
}

bool ListInsert(SeqList &L, int i, int e) {
    // 1. 检查 i 是否合法 [1, L.length+1]
    if (i<1||i>L.length+1) return false;
    // 2. 检查表是否已满
    if (L.length>=MAX_SIZE) return false;
    // 3. 将第 i 位及之后的元素后移
    for (int j=L.length;j>i-1;j--) {
        L.data[j] = L.data[j-1];
    }
    // 4. 放入 e，length++
    L.data[i-1] = e;
    L.length++;
    return true;
}

bool ListDelete(SeqList &L, int i, int &e) {
    // 1. 检查 i 是否合法 [1, L.length]
    if (i<1||i>L.length) return false;
    // 2.赋值
    e =L.data[i-1];
    // 3.将第 i 位之后的元素前移
    for (int j = i-1;j<L.length;j++) {
        L.data[j] = L.data[j+1];
    }
    // 4.修改表长度
    L.length--;
    return true;
}

int LocateElem(SeqList L, int e) {
    //遍历整个表
    for (int k = 0; k < L.length; k++) {
        if (L.data[k] == e) return k+1;
    }
    return 0;
}

bool GetElem(SeqList L, int i, int &e) {
    // 1. 检查 e 是否合法 [1, L.length]
    if (i<0||i>L.length) return false;
    // 2. 返回值
    e = L.data[i-1];
    return true;
}

int Length(SeqList L) {
    return L.length;
}

void PrintList(SeqList L) {
    for (int k = 0; k < L.length; k++) {
        printf("%d ", L.data[k]);
    }
}



// ==========================================
// 3. 测试用例验证框架
// ==========================================
int main() {
    SeqList L;
    int e = -1;

    printf("--- 开始测试顺序表(静态分配) ---\n");

    // 测试1：初始化
    if (InitList(L)) {
        printf("[PASS] InitList: 初始化成功，当前长度=%d, 最大容量=%d\n", Length(L), MaxSize);
    } else {
        printf("[FAIL] InitList: 初始化失败\n");
        return -1;
    }

    // 测试2：插入元素
    // 在第1个位置依次插入 10, 20, 30 -> 结果应为 30, 20, 10
    ListInsert(L, 1, 10);
    ListInsert(L, 1, 20);
    ListInsert(L, 1, 30);
    // 在尾部追加
    ListInsert(L, 4, 40);

    printf("\n插入元素后预期的表为: 30 20 10 40\n");
    printf("实际的表输出为:     ");
    PrintList(L);
    printf("\n");

    // 测试3：按值查找
    int loc = LocateElem(L, 20);
    if (loc == 2) {
        printf("[PASS] LocateElem: 元素20的位序为 %d\n", loc);
    } else {
        printf("[FAIL] LocateElem: 查找元素20失败，返回位序 %d\n", loc);
    }

    // 测试4：按位查找
    if (GetElem(L, 3, e) && e == 10) {
        printf("[PASS] GetElem: 第3个元素为 %d\n", e);
    } else {
        printf("[FAIL] GetElem: 获取第3个元素失败，或值不正确(当前为%d)\n", e);
    }

    // 测试5：删除元素
    if (ListDelete(L, 2, e) && e == 20) {
        printf("[PASS] ListDelete: 成功删除第2个元素，被删除的值为 %d\n", e);
    } else {
        printf("[FAIL] ListDelete: 删除失败\n");
    }

    printf("\n删除后预期的表为: 30 10 40\n");
    printf("实际的表输出为:   ");
    PrintList(L);
    printf("\n");

    // 测试6：边界与异常测试（非法位置插入与删除）
    printf("\n--- 异常边界测试 ---\n");
    if (!ListInsert(L, 99, 100)) {
        printf("[PASS] ListInsert: 成功拦截越界插入 (位序99)\n");
    } else {
        printf("[FAIL] ListInsert: 未能拦截越界插入\n");
    }

    if (!ListDelete(L, 0, e)) {
        printf("[PASS] ListDelete: 成功拦截非法位置删除 (位序0)\n");
    } else {
        printf("[FAIL] ListDelete: 未能拦截非法位置删除\n");
    }

    printf("--- 测试结束 ---\n");
    return 0;
}