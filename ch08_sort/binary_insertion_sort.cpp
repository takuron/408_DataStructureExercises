// 练习：折半插入排序
// 参考答案：保留原练习契约和测试，可与 main 分支对照学习。
// 禁止用 STL 排序代替练习；int 用例只检验结果，不检验稳定性，稳定性需结合相等记录的相对次序理解。
#include "common.h"

// --- 数据结构定义 ---


// --- 函数声明与行为契约 ---
/** 用折半查找确定插入位置，整体后移；相等元素插在已有等值元素之后以保持稳定。 n>=0；升序原地输出；n=0 时允许 a=nullptr。 */
void BinaryInsertSort(int a[], int n);

// --- 参考实现 ---
void BinaryInsertSort(int a[], int n) {
    for (int i = 1; i < n; ++i) {
        int value = a[i], low = 0, high = i;
        // 找首个 > value 的位置，相等时插在后面以保持稳定。
        while (low < high) {
            int mid = low + (high-low)/2;
            if (a[mid] <= value) low = mid+1;
            else high = mid;
        }
        for (int j = i; j > low; --j) a[j] = a[j-1];
        a[low] = value;
    }
}

// --- 测试入口 ---
int main() {
    printf("--- 折半插入排序 ---\n");

    int cases[][8] = { {5,2,7,2,0,9,1,5}, {0,1,2,3,4,5,6,7},
                        {7,6,5,4,3,2,1,0}, {2,2,2,2,2,2,2,2} };
    int expected[][8] = { {0,1,2,2,5,5,7,9}, {0,1,2,3,4,5,6,7},
                           {0,1,2,3,4,5,6,7}, {2,2,2,2,2,2,2,2} };
    for (int i = 0; i < 4; ++i) {
        BinaryInsertSort(cases[i],8); test(memcmp(cases[i],expected[i],sizeof(cases[i])) == 0);
    }
    BinaryInsertSort(nullptr,0); int one[] = {42}; BinaryInsertSort(one,1); test(one[0] == 42);
    int two[] = {2,1}; BinaryInsertSort(two,2); test(two[0] == 1 && two[1] == 2);
    int negative[] = {0,-5,2,-5,-1}; int want[] = {-5,-5,-1,0,2};
    BinaryInsertSort(negative,5); test(memcmp(negative,want,sizeof(want)) == 0);
    return 0;
}
