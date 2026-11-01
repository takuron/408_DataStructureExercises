// 练习：基数排序（LSD）
// 参考答案：保留原练习契约和测试，可与 main 分支对照学习。
// 禁止用 STL 排序代替练习；int 用例只检验结果，不检验稳定性，稳定性需结合相等记录的相对次序理解。
#include "common.h"

// --- 数据结构定义 ---


// --- 函数声明与行为契约 ---
/** 仅处理非负 int；按十进制从低位到高位稳定分配与收集；最大位循环须避免 int 溢出。 n>=0；升序原地输出；n=0 时允许 a=nullptr。 */
void RadixSort(int a[], int n);

// --- 参考实现 ---
void RadixSort(int a[], int n) {
    if (n < 2) return;
    int maximum = 0;
    for (int i = 0; i < n; ++i) if (a[i] > maximum) maximum = a[i];
    int *temp = new int[n];
    for (int place = 1; maximum / place > 0; ) {
        int count[10] = {};
        for (int i = 0; i < n; ++i) ++count[(a[i]/place)%10];
        for (int d = 1; d < 10; ++d) count[d] += count[d-1];
        // 反向扫描，按前缀和放置，保证每一趟稳定。
        for (int i = n-1; i >= 0; --i) temp[--count[(a[i]/place)%10]] = a[i];
        for (int i = 0; i < n; ++i) a[i] = temp[i];
        if (place > maximum / 10) break; // 先判断再乘 10，防止溢出。
        place *= 10;
    }
    delete[] temp;
}

// --- 测试入口 ---
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
