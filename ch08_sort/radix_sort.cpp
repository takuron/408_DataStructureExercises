// 练习：基数排序（LSD）
// 只提供契约、桩函数和测试；请自行完成 TODO。
// 禁止用 STL 排序代替练习；int 用例只检验结果，不检验稳定性，稳定性需结合相等记录的相对次序理解。
#include "common.h"

// --- 数据结构定义 ---


// --- 函数声明与行为契约 ---
/** 仅处理非负 int；按十进制从低位到高位稳定分配与收集；最大位循环须避免 int 溢出。 n>=0；升序原地输出；n=0 时允许 a=nullptr。 */
void RadixSort(int a[], int n);

// --- 在此处编写实现 ---
void RadixSort(int a[], int n) {
    // TODO: 仅处理非负 int；按十进制从低位到高位稳定分配与收集；最大位循环须避免 int 溢出。 n>=0；升序原地输出；n=0 时允许 a=nullptr。
    (void)a; (void)n;
}

// --- 测试入口：未实现时出现 FAIL 是正常现象 ---
int main() {
    printf("--- 基数排序（LSD） ---\n");

    int cases[][8] = { {5,2,7,2,0,9,1,5}, {0,1,2,3,4,5,6,7},
                        {7,6,5,4,3,2,1,0}, {2,2,2,2,2,2,2,2} };
    int expected[][8] = { {0,1,2,2,5,5,7,9}, {0,1,2,3,4,5,6,7},
                           {0,1,2,3,4,5,6,7}, {2,2,2,2,2,2,2,2} };
    for (int i = 0; i < 4; ++i) {
        RadixSort(cases[i],8); test(memcmp(cases[i],expected[i],sizeof(cases[i])) == 0);
    }
    RadixSort(nullptr,0); int one[] = {42}; RadixSort(one,1); test(one[0] == 42);
    int two[] = {2,1}; RadixSort(two,2); test(two[0] == 1 && two[1] == 2);
    int large[] = {2147483647,0,1000000000,10};
    RadixSort(large,4);
    test(large[0] == 0 && large[1] == 10 && large[2] == 1000000000 && large[3] == 2147483647);
    return 0;
}
