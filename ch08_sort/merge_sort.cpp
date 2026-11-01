// 练习：二路归并排序
// 参考答案：保留原练习契约和测试，可与 main 分支对照学习。
// 禁止用 STL 排序代替练习；int 用例只检验结果，不检验稳定性，稳定性需结合相等记录的相对次序理解。
#include "common.h"

// --- 数据结构定义 ---


// --- 函数声明与行为契约 ---
/** 两个有序闭区间 [low,mid]、[mid+1,high] 合并，借助 temp 并写回 a；temp 至少 n 格。 */
void Merge(int a[], int temp[], int low, int mid, int high);

/** 递归划分后借助辅助数组合并；相等时先取左边保证稳定；空间 O(n)。 n>=0；升序原地输出；n=0 时允许 a=nullptr。 */
void MergeSort(int a[], int n);

static void MergeRange(int a[], int temp[], int low, int high) {
    if (low >= high) return;
    int mid = low + (high-low)/2;
    MergeRange(a,temp,low,mid); MergeRange(a,temp,mid+1,high);
    Merge(a,temp,low,mid,high);
}

// --- 参考实现 ---
void Merge(int a[], int temp[], int low, int mid, int high) {
    int i = low, j = mid+1, k = low;
    while (i <= mid && j <= high) temp[k++] = a[i] <= a[j] ? a[i++] : a[j++];
    while (i <= mid) temp[k++] = a[i++];
    while (j <= high) temp[k++] = a[j++];
    for (k = low; k <= high; ++k) a[k] = temp[k];
}

void MergeSort(int a[], int n) {
    if (n < 2) return;
    int *temp = new int[n];
    MergeRange(a,temp,0,n-1);
    delete[] temp;
}

// --- 测试入口 ---
int main() {
    printf("--- 二路归并排序 ---\n");

    int cases[][8] = { {5,2,7,2,0,9,1,5}, {0,1,2,3,4,5,6,7},
                        {7,6,5,4,3,2,1,0}, {2,2,2,2,2,2,2,2} };
    int expected[][8] = { {0,1,2,2,5,5,7,9}, {0,1,2,3,4,5,6,7},
                           {0,1,2,3,4,5,6,7}, {2,2,2,2,2,2,2,2} };
    for (int i = 0; i < 4; ++i) {
        MergeSort(cases[i],8); test(memcmp(cases[i],expected[i],sizeof(cases[i])) == 0);
    }
    MergeSort(nullptr,0); int one[] = {42}; MergeSort(one,1); test(one[0] == 42);
    int two[] = {2,1}; MergeSort(two,2); test(two[0] == 1 && two[1] == 2);
    int negative[] = {0,-5,2,-5,-1}; int want[] = {-5,-5,-1,0,2};
    MergeSort(negative,5); test(memcmp(negative,want,sizeof(want)) == 0);
    return 0;
}
