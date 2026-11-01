// 练习：堆排序
// 只提供契约、桩函数和测试；请自行完成 TODO。
// 禁止用 STL 排序代替练习；int 用例只检验结果，不检验稳定性，稳定性需结合相等记录的相对次序理解。
#include "common.h"

// --- 数据结构定义 ---


// --- 函数声明与行为契约 ---
/** 在 [0,size) 中向下调整大根堆；root 的左右子树已是堆；孩子下标 2*root+1、2*root+2。 */
void SiftDown(int a[], int root, int size);

/** 0 基数组建大根堆，反复交换堆顶与末尾并向下调整；不稳定，空间 O(1)。 n>=0；升序原地输出；n=0 时允许 a=nullptr。 */
void HeapSort(int a[], int n);

// --- 在此处编写实现 ---
void SiftDown(int a[], int root, int size) {
    // TODO: 在 [0,size) 中向下调整大根堆；root 的左右子树已是堆；孩子下标 2*root+1、2*root+2。
    (void)a; (void)root; (void)size;
}

void HeapSort(int a[], int n) {
    // TODO: 0 基数组建大根堆，反复交换堆顶与末尾并向下调整；不稳定，空间 O(1)。 n>=0；升序原地输出；n=0 时允许 a=nullptr。
    (void)a; (void)n;
}

// --- 测试入口：未实现时出现 FAIL 是正常现象 ---
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
