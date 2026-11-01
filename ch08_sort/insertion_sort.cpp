// 练习：直接插入排序
// 只提供契约、桩函数和测试；请自行完成 TODO。
// 禁止用 STL 排序代替练习；int 用例只检验结果，不检验稳定性，稳定性需结合相等记录的相对次序理解。
#include "common.h"

// --- 数据结构定义 ---


// --- 函数声明与行为契约 ---
/** 将当前元素插入前方有序区；时间 O(n^2)，空间 O(1)，稳定。 n>=0；升序原地输出；n=0 时允许 a=nullptr。 */
void InsertSort(int a[], int n);

// --- 在此处编写实现 ---
void InsertSort(int a[], int n) {
    // TODO: 将当前元素插入前方有序区；时间 O(n^2)，空间 O(1)，稳定。 n>=0；升序原地输出；n=0 时允许 a=nullptr。
    (void)a; (void)n;
}

// --- 测试入口：未实现时出现 FAIL 是正常现象 ---
int main() {
    printf("--- 直接插入排序 ---\n");

    int cases[][8] = { {5,2,7,2,0,9,1,5}, {0,1,2,3,4,5,6,7},
                        {7,6,5,4,3,2,1,0}, {2,2,2,2,2,2,2,2} };
    int expected[][8] = { {0,1,2,2,5,5,7,9}, {0,1,2,3,4,5,6,7},
                           {0,1,2,3,4,5,6,7}, {2,2,2,2,2,2,2,2} };
    for (int i = 0; i < 4; ++i) {
        InsertSort(cases[i],8); test(memcmp(cases[i],expected[i],sizeof(cases[i])) == 0);
    }
    InsertSort(nullptr,0); int one[] = {42}; InsertSort(one,1); test(one[0] == 42);
    int two[] = {2,1}; InsertSort(two,2); test(two[0] == 1 && two[1] == 2);
    int negative[] = {0,-5,2,-5,-1}; int want[] = {-5,-5,-1,0,2};
    InsertSort(negative,5); test(memcmp(negative,want,sizeof(want)) == 0);
    return 0;
}
