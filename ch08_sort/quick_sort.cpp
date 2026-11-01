// 练习：快速排序
// 参考答案：保留原练习契约和测试，可与 main 分支对照学习。
// 禁止用 STL 排序代替练习；int 用例只检验结果，不检验稳定性，稳定性需结合相等记录的相对次序理解。
#include "common.h"

// --- 数据结构定义 ---


// --- 函数声明与行为契约 ---
/** 闭区间 [low,high]，以首元素为枢轴，完成划分并返回枢轴最终下标；调用者保证区间非空。 */
int Partition(int a[], int low, int high);

/** 自行编写划分，再递归排序左右区间；注意重复关键字与递归终止；不稳定。 n>=0；升序原地输出；n=0 时允许 a=nullptr。 */
void QuickSort(int a[], int n);

static void QuickRange(int a[], int low, int high) {
    // 只递归较短区间，较长区间循环处理，使递归栈保持 O(log n)。
    // 首元素枢轴仍可能造成 O(n^2) 时间，属于此基础划分策略的特性。
    while (low < high) {
        int pivot = Partition(a,low,high);
        if (pivot-low < high-pivot) {
            QuickRange(a,low,pivot-1); low = pivot+1;
        } else {
            QuickRange(a,pivot+1,high); high = pivot-1;
        }
    }
}

// --- 参考实现 ---
int Partition(int a[], int low, int high) {
    int pivot = a[low];
    while (low < high) {
        while (low < high && a[high] >= pivot) --high;
        a[low] = a[high];
        while (low < high && a[low] <= pivot) ++low;
        a[high] = a[low];
    }
    a[low] = pivot;
    return low;
}

void QuickSort(int a[], int n) {
    QuickRange(a,0,n-1);
}

// --- 测试入口 ---
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
