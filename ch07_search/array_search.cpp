// 练习：顺序查找与折半查找
// 参考答案：保留原练习契约和测试，可与 main 分支对照学习。
// 数组长度由调用者保证；n=0 时允许 a=nullptr；所有返回值均为 0 基下标。
#include "common.h"

// --- 数据结构定义 ---


// --- 函数声明与行为契约 ---
/** 返回首个匹配值的 0 基下标；未找到返回 -1；n>=0。 */
int SequentialSearch(const int a[], int n, int key);

/** a 非递减有序，迭代折半查找；重复值返回任一匹配下标，未找到返回 -1。 */
int BinarySearch(const int a[], int n, int key);

/** 非递减数组中首个 >=key 的下标；全小于 key 返回 n；用折半查找。 */
int LowerBound(const int a[], int n, int key);

// --- 参考实现 ---
int SequentialSearch(const int a[], int n, int key) {
    for (int i = 0; i < n; ++i) if (a[i] == key) return i;
    return -1;
}

int BinarySearch(const int a[], int n, int key) {
    int low = 0, high = n-1;
    while (low <= high) {
        int mid = low + (high-low)/2;
        if (a[mid] == key) return mid;
        if (a[mid] < key) low = mid+1;
        else high = mid-1;
    }
    return -1;
}

int LowerBound(const int a[], int n, int key) {
    // 左闭右开区间 [low,high)，始终保留第一个 >= key 的位置。
    int low = 0, high = n;
    while (low < high) {
        int mid = low + (high-low)/2;
        if (a[mid] < key) low = mid+1;
        else high = mid;
    }
    return low;
}

// --- 测试入口 ---
int main() {
    printf("--- 顺序查找与折半查找 ---\n");

    int a[] = {-3,0,2,2,8};
    test(SequentialSearch(a,5,2) == 2); test(SequentialSearch(a,5,9) == -1);
    int p = BinarySearch(a,5,2); test(p >= 0 && p < 5 && a[p] == 2);
    test(BinarySearch(a,5,-3) == 0); test(BinarySearch(a,5,8) == 4);
    test(BinarySearch(a,5,1) == -1); test(BinarySearch(nullptr,0,1) == -1);
    test(LowerBound(a,5,2) == 2); test(LowerBound(a,5,9) == 5);
    test(LowerBound(a,5,-4) == 0); test(LowerBound(nullptr,0,7) == 0);
    return 0;
}
