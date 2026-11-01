// 练习：冒泡排序
// 参考答案：保留原练习契约和测试，可与 main 分支对照学习。
// 禁止用 STL 排序代替练习；int 用例只检验结果，不检验稳定性，稳定性需结合相等记录的相对次序理解。
#include "common.h"

// --- 数据结构定义 ---


// --- 函数声明与行为契约 ---
/** 相邻逆序元素交换；一趟无交换时提前结束；稳定。 n>=0；升序原地输出；n=0 时允许 a=nullptr。 */
void BubbleSort(int a[], int n);

// --- 参考实现 ---
void BubbleSort(int a[], int n) {
    for (int end = n-1; end > 0; --end) {
        bool swapped = false;
        for (int j = 0; j < end; ++j) if (a[j] > a[j+1]) {
            int t = a[j]; a[j] = a[j+1]; a[j+1] = t; swapped = true;
        }
        if (!swapped) break;
    }
}

// --- 测试入口 ---
int main() {
    printf("--- 冒泡排序 ---\n");

    int cases[][8] = { {5,2,7,2,0,9,1,5}, {0,1,2,3,4,5,6,7},
                        {7,6,5,4,3,2,1,0}, {2,2,2,2,2,2,2,2} };
    int expected[][8] = { {0,1,2,2,5,5,7,9}, {0,1,2,3,4,5,6,7},
                           {0,1,2,3,4,5,6,7}, {2,2,2,2,2,2,2,2} };
    for (int i = 0; i < 4; ++i) {
        BubbleSort(cases[i],8); test(memcmp(cases[i],expected[i],sizeof(cases[i])) == 0);
    }
    BubbleSort(nullptr,0); int one[] = {42}; BubbleSort(one,1); test(one[0] == 42);
    int two[] = {2,1}; BubbleSort(two,2); test(two[0] == 1 && two[1] == 2);
    int negative[] = {0,-5,2,-5,-1}; int want[] = {-5,-5,-1,0,2};
    BubbleSort(negative,5); test(memcmp(negative,want,sizeof(want)) == 0);
    return 0;
}
