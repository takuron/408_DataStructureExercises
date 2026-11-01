// 练习：快速排序
// 只提供契约、桩函数和测试；请自行完成 TODO。
// 禁止用 STL 排序代替练习；int 用例只检验结果，不检验稳定性，稳定性需结合相等记录的相对次序理解。
#include "common.h"

// --- 数据结构定义 ---


// --- 函数声明与行为契约 ---
/** 闭区间 [low,high]，以首元素为枢轴，完成划分并返回枢轴最终下标；调用者保证区间非空。 */
int Partition(int a[], int low, int high);

/** 自行编写划分，再递归排序左右区间；注意重复关键字与递归终止；不稳定。 n>=0；升序原地输出；n=0 时允许 a=nullptr。 */
void QuickSort(int a[], int n);

// --- 在此处编写实现 ---
int Partition(int a[], int low, int high) {
    // TODO: 闭区间 [low,high]，以首元素为枢轴，完成划分并返回枢轴最终下标；调用者保证区间非空。
    return low;
}

void QuickSort(int a[], int n) {
    // TODO: 自行编写划分，再递归排序左右区间；注意重复关键字与递归终止；不稳定。 n>=0；升序原地输出；n=0 时允许 a=nullptr。
    (void)a; (void)n;
}

// --- 测试入口：未实现时出现 FAIL 是正常现象 ---
int main() {
    printf("--- 快速排序 ---\n");

    int cases[][8] = { {5,2,7,2,0,9,1,5}, {0,1,2,3,4,5,6,7},
                        {7,6,5,4,3,2,1,0}, {2,2,2,2,2,2,2,2} };
    int expected[][8] = { {0,1,2,2,5,5,7,9}, {0,1,2,3,4,5,6,7},
                           {0,1,2,3,4,5,6,7}, {2,2,2,2,2,2,2,2} };
    for (int i = 0; i < 4; ++i) {
        QuickSort(cases[i],8); test(memcmp(cases[i],expected[i],sizeof(cases[i])) == 0);
    }
    QuickSort(nullptr,0); int one[] = {42}; QuickSort(one,1); test(one[0] == 42);
    int two[] = {2,1}; QuickSort(two,2); test(two[0] == 1 && two[1] == 2);
    int negative[] = {0,-5,2,-5,-1}; int want[] = {-5,-5,-1,0,2};
    QuickSort(negative,5); test(memcmp(negative,want,sizeof(want)) == 0);
    return 0;
}
