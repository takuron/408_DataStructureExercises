# 408 数据结构练习环境

基于 CLion + CMake 的 408 考研数据结构刷题环境。**每个 `.cpp` 文件都是独立可执行单元**，在 CLion 中可以像脚本一样一键运行。

---

## 目录结构

```
408_DataStructureExercises/
├── CMakeLists.txt          # CMake 配置（自动扫描所有 .cpp 并生成运行目标）
├── common/                 # 公共头文件
│   ├── common.h            #   宏定义、测试断言、状态码等
│   └── template.cpp        #   新习题模板（复制到对应章节即可使用）
├── ch02_linear_list/       # 第2章 线性表
├── ch03_stack_queue/       # 第3章 栈和队列
├── ch04_string/            # 第4章 串
├── ch05_tree/              # 第5章 树与二叉树
├── ch06_graph/             # 第6章 图
├── ch07_search/            # 第7章 查找
└── ch08_sort/              # 第8章 排序
```

---

## 使用方式

### 1. 在 CLion 中打开

用 CLion 打开本目录，IDE 会自动识别 `CMakeLists.txt` 并加载项目。首次加载时会自动运行 CMake，扫描所有 `.cpp` 文件并为每个文件生成一个运行目标。

### 2. 运行某个习题

- **方式一**：打开任意 `.cpp` 文件，点击 `main()` 函数左侧的绿色 ▶ 图标，选择 "Run"。
- **方式二**：在顶部运行配置下拉框中，选择对应的目标名（如 `ch02_linear_list_seq_list_static`），然后点击运行。
- **方式三**：在项目树中右键 `.cpp` 文件 → "Run"。

### 3. 添加新习题

```bash
# 复制模板到目标章节
cp common/template.cpp ch02_linear_list/my_exercise.cpp
```

然后在 CLion 中点击 **Tools → CMake → Reload CMake Project**（或按 `Ctrl+Shift+O`），新的运行目标就会自动出现。

### 4. 编写习题

每个习题文件遵循统一的格式：

1. **数据结构定义** —— 定义本题需要的结构体
2. **函数声明** —— 声明需要实现的操作（附行为契约注释）
3. **函数实现** —— 填写你的代码（桩实现仅保证编译通过）
4. **测试入口** —— `main()` 中编写测试用例验证正确性

文件开头的桩实现保证文件可以立即编译运行（虽然测试不通过），方便你先理解题目需求再动手。

---

## 公共宏说明

```cpp
test(expr)           // 断言 expr == true，打印 PASS/FAIL
test_msg(expr, msg)  // 同上，附带自定义消息
hr()                 // 打印分隔线
```

---

## 考研 408 数据结构大纲

| 章节 | 内容 |
|------|------|
| ch02 | 线性表（顺序表、链表） |
| ch03 | 栈、队列（顺序/链式存储、应用） |
| ch04 | 串（模式匹配 KMP 等） |
| ch05 | 树与二叉树（遍历、线索树、哈夫曼树、并查集） |
| ch06 | 图（存储、遍历、最小生成树、最短路径、拓扑排序、关键路径） |
| ch07 | 查找（顺序、折半、BST、AVL、B 树、散列表） |
| ch08 | 排序（插入、交换、选择、归并、基数） |

---

## 练习清单与建议顺序

新增文件均为**练习模板，不含算法答案**：包含结构体、带行为契约的函数声明、TODO 桩函数及固定测试。原有的静态顺序表、顺序栈、递归二叉树遍历文件保留原样。

建议先按“线性表 → 栈队列 → 串 → 树 → 查找 → 排序 → 图”练习。先读声明中的契约，再填写实现，最后运行 `main()` 检查输出。

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

### 统一约定

- 线性表操作通常使用 **1 起始位序**；数组、图顶点、排序和本项目 KMP 使用 **0 起始下标**。具体以每个文件的契约为准，不要混用教材中的另一套下标约定。
- 新模板的标量、指针和数组测试数据均初始化；指针检查使用短路条件，未完成函数时也能运行测试。
- 桩函数默认返回失败值或不修改数据。运行时同时出现 PASS 和 FAIL 是预期情况；PASS 中可能包含空结构等恰好成立的用例，不能仅凭个别 PASS 判断已完成。
- `test` / `test_msg` **只打印结果，不改变退出码**。程序退出码为 0 只表示执行完毕；完成练习后应检查所有 `[FAIL]`，并自行追加用例。编译成功也不代表算法正确。
- 动态结构需自行实现释放操作；失败操作应保持结构和输出参数不变。遍历结果写入数组时，调用者负责提供足够容量。
- 排序用例覆盖空数组、单元素、两元素、重复值、有序与逆序；比较排序另测负数，基数排序限定非负整数并测试大数。整数结果不能检验稳定性，请结合记录的原始次序理解稳定性。

### 命令行编译运行

```bash
cmake -S . -B build
cmake --build build -j 4
# 选择一个模板独立运行
./build/bin/ch07_search_binary_search_tree
./build/bin/ch08_sort_quick_sort
```

CMake 已启用 `CONFIGURE_DEPENDS`，后续新增章节内的 `.cpp` 时，构建阶段会检查并更新目标列表；在 CLion 中也可手动 Reload CMake Project。

### 学习范围说明

本清单覆盖常见的基础手写练习，并补充图算法、AVL 等进阶模板。由于未指定教材版本，它不是某一版本教材的逐页题目目录。B/B+ 树、红黑树、外部排序、多维数组地址计算、特殊矩阵压缩存储等内容仍需结合所用教材学习其性质、推演和复杂度；本轮未提供这些主题的完整实现练习。AVL 模板仅要求插入，不包含删除。所有算法均留待自行填写。
