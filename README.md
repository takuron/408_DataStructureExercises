# 408 数据结构参考答案

当前分支为 **`reference-answers`**，包含全部 40 个练习文件的参考实现。**`main` 分支保留 TODO 练习模板**。每个 `.cpp` 都有独立 `main()`，可以在 CLion 中单独运行。

## 查看与切换

在没有未保存修改时切换：

```bash
git switch reference-answers  # 查看答案
git switch main               # 返回练习
```

只查看某一道答案而不切换分支：

```bash
git show reference-answers:ch08_sort/quick_sort.cpp
# 比较模板与答案
git diff main..reference-answers -- ch07_search/binary_search_tree.cpp
```

如已在练习分支写了代码，可先提交或暂存改动再切换；也可使用 `git show` 直接查阅。参考实现着重教材算法、边界处理和关键步骤注释，没有用 STL 容器代替需要练习的数据结构，也没有用库排序替代排序算法。

## 编译与验证

```bash
cmake -S . -B build
cmake --build build -j 4
./build/bin/ch07_search_binary_search_tree
python3 tests/check_answers.py build
```

检查脚本会运行全部 40 个示例，检测退出码和 `[FAIL]` 输出，并编译运行固定随机种子的补充测试。补充测试用 STL 或独立算法作为结果对照，覆盖九种排序、KMP、查找、四类链表、BST、AVL、散列表、并查集、最短路径和最小生成树；STL 仅用于测试。

可选的内存及未定义行为检查（GCC/Clang）：

```bash
cmake -S . -B build-sanitize -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_CXX_FLAGS="-fsanitize=address,undefined -fno-omit-frame-pointer"
cmake --build build-sanitize -j 4
python3 tests/check_answers.py build-sanitize --sanitize
```

部分受跟踪的沙箱不支持 LeakSanitizer；此时可在验证命令前加 `ASAN_OPTIONS=detect_leaks=0`，保留地址越界、释放后使用和 UBSan 检查，泄漏检测将关闭。`test` 宏本身只打印结果，批量检查脚本负责在发现失败时返回非零退出码。

## 约定与阅读提示

- 线性表使用 1 起始位序；数组、图顶点、排序与 KMP 使用 0 起始下标。KMP 采用 `next[0]=-1` 的回退表。
- 初始化动态结构前应确保尚未持有已分配资源；需要重新初始化时先销毁。动态结构使用 `malloc/free` 配对；归并和基数排序的辅助数组使用 `new[]/delete[]` 配对。
- 遍历输出数组容量由调用者保证；树和图的最大规模以各文件契约为准。参考代码假设输入结构无环、长度等元数据有效。
- 图中的无边分别用 `0`（无权图）、`INF`（加权图）、`-1`（AOE 网）表示；不要混用。距离及权值总和约定在文件说明的整数范围内。
- 快排按首元素划分，最坏时间仍为 O(n²)；实现通过仅递归较短区间控制栈深度。AVL 只要求插入与旋转；基数排序只处理非负整数。
- 稳定性：直接插入、折半插入、冒泡、归并和本实现的 LSD 基数排序稳定；希尔、快排、简单选择和堆排序不稳定。
- 二叉树递归遍历是已有代码，其余模板已补全；契约、测试树和基本测试保留，便于逐题对照。

## 题目清单

| 章节 | 文件（省略 `.cpp`） | 练习内容 |
|------|--------------------|----------|
| ch02_linear_list | seq_list_static（原有）、seq_list_dynamic | 静态/动态顺序表、扩容、插入、删除、查找 |
| ch02_linear_list | singly_linked_list | 带头结点单链表、插删查找、原地逆置 |
| ch02_linear_list | doubly_linked_list | 双链表，维护前驱和后继 |
| ch02_linear_list | circular_singly_linked_list | 循环单链表，回到头结点判结束 |
| ch02_linear_list | circular_doubly_linked_list | 循环双链表、空表与单元素情况 |
| ch02_linear_list | static_linked_list（选练） | 静态链表、游标、备用链回收 |
| ch03_stack_queue | seq_stack（原有）、linked_stack、shared_stack | 顺序栈、链栈、共享栈 |
| ch03_stack_queue | circular_queue、linked_queue | 循环队列、链队列、队满及队尾回收 |
| ch03_stack_queue | bracket_matching | 手写栈的括号匹配应用 |
| ch04_string | sequential_string | 定长串赋值、比较、连接、子串 |
| ch04_string | pattern_matching | 朴素匹配、KMP、next 数组 |
| ch05_tree | binary_tree_traversal（原有） | 递归先序、中序、后序遍历 |
| ch05_tree | binary_tree_operations | 非递归三种遍历、层序、树高、叶子数 |
| ch05_tree | child_sibling_tree | 孩子兄弟存储、树与森林的遍历和高度 |
| ch05_tree | threaded_binary_tree | 中序线索化、首结点、后继、线索遍历 |
| ch05_tree | disjoint_set | 并查集、路径压缩、按规模合并 |
| ch05_tree | huffman_tree | 哈夫曼树构造、带权路径长度 WPL |
| ch06_graph | graph_storage | 邻接矩阵、邻接表、无向边、度数、销毁 |
| ch06_graph | graph_traversal | DFS、BFS、非连通图、无权最短路径 |
| ch06_graph | minimum_spanning_tree | Prim、Kruskal、非连通图判定 |
| ch06_graph | shortest_paths | Dijkstra、Floyd、不可达与前驱 |
| ch06_graph | topological_critical_path | 拓扑排序、环检测、AOE 网关键路径 |
| ch07_search | array_search | 顺序查找、折半查找、首个不小于目标值的位置 |
| ch07_search | binary_search_tree | BST 查找、插入、三类删除、中序遍历 |
| ch07_search | avl_tree（进阶） | AVL 插入、旋转、LL/RR/LR/RL 失衡 |
| ch07_search | hash_linear_probing、hash_chaining | 线性探测、删除标记、拉链法、冲突处理 |
| ch08_sort | insertion_sort、binary_insertion_sort、shell_sort | 直接插入、折半插入、希尔排序 |
| ch08_sort | bubble_sort、quick_sort | 冒泡、快速排序与划分 |
| ch08_sort | selection_sort、heap_sort | 简单选择、大根堆、堆排序 |
| ch08_sort | merge_sort、radix_sort | 二路归并、十进制 LSD 基数排序 |


本分支仅对应仓库已有练习，未扩展 B/B+ 树、红黑树、AVL 删除或外部排序等题目。建议先在 `main` 独立完成，再按函数查阅参考实现。


## 类型定义风格

所有分支统一采用 C 风格的 `typedef` 定义结构体、枚举和指针类型别名，例如：

```c
typedef struct LNode {
    int data;
    struct LNode *next;
} LNode;
typedef LNode *LinkList;
```

结构体内部使用 `struct LNode *` 自引用，因为末尾的 `LNode` 别名尚未声明。文件仍使用 C++14 编译，函数引用参数等接口保持原样。
