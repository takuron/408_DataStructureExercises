// 练习：堆排序
// 参考答案：保留原练习契约和测试，可与 main 分支对照学习。
// 禁止用 STL 排序代替练习；int 用例只检验结果，不检验稳定性，稳定性需结合相等记录的相对次序理解。
#include "common.h"

// --- 数据结构定义 ---


// --- 函数声明与行为契约 ---
/** 在 [0,size) 中向下调整大根堆；root 的左右子树已是堆；孩子下标 2*root+1、2*root+2。 */
void SiftDown(int a[], int root, int size);

/** 0 基数组建大根堆，反复交换堆顶与末尾并向下调整；不稳定，空间 O(1)。 n>=0；升序原地输出；n=0 时允许 a=nullptr。 */
void HeapSort(int a[], int n);

// --- 参考实现 ---
void SiftDown(int a[], int root, int size) {
    int value = a[root];
    for (int child = 2*root+1; child < size; child = 2*root+1) {
        if (child+1 < size && a[child+1] > a[child]) ++child;
        if (value >= a[child]) break;
        a[root] = a[child]; root = child;
    }
    a[root] = value;
}

void HeapSort(int a[], int n) {
    for (int i = n/2-1; i >= 0; --i) SiftDown(a,i,n);
    for (int end = n-1; end > 0; --end) {
        int t = a[0]; a[0] = a[end]; a[end] = t;
        SiftDown(a,0,end);
    }
}

// --- 测试入口 ---
int main() {
    printf("--- 堆排序 ---\n");

    int cases[][8] = { {5,2,7,2,0,9,1,5}, {0,1,2,3,4,5,6,7},
                        {7,6,5,4,3,2,1,0}, {2,2,2,2,2,2,2,2} };
    int expected[][8] = { {0,1,2,2,5,5,7,9}, {0,1,2,3,4,5,6,7},
                           {0,1,2,3,4,5,6,7}, {2,2,2,2,2,2,2,2} };
    for (int i = 0; i < 4; ++i) {
        HeapSort(cases[i],8); test(memcmp(cases[i],expected[i],sizeof(cases[i])) == 0);
    }
    HeapSort(nullptr,0); int one[] = {42}; HeapSort(one,1); test(one[0] == 42);
    int two[] = {2,1}; HeapSort(two,2); test(two[0] == 1 && two[1] == 2);
    int negative[] = {0,-5,2,-5,-1}; int want[] = {-5,-5,-1,0,2};
    HeapSort(negative,5); test(memcmp(negative,want,sizeof(want)) == 0);
    return 0;
}
