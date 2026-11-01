#!/usr/bin/env python3
"""运行全部示例并用固定随机种子补充性质测试；仅用于 reference-answers 分支。"""
import argparse
import os
from pathlib import Path
import shlex
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]


def run(command):
    result = subprocess.run(command, text=True, capture_output=True, timeout=120)
    if result.returncode or '[FAIL]' in result.stdout:
        raise RuntimeError(f'{shlex.join(map(str, command))}\n{result.stdout}\n{result.stderr}')
    return result.stdout


def cases():
    sorts = {
        'insertion_sort': 'InsertSort', 'binary_insertion_sort': 'BinaryInsertSort',
        'shell_sort': 'ShellSort', 'bubble_sort': 'BubbleSort', 'quick_sort': 'QuickSort',
        'selection_sort': 'SelectSort', 'heap_sort': 'HeapSort', 'merge_sort': 'MergeSort',
        'radix_sort': 'RadixSort',
    }
    for name, function in sorts.items():
        value = 'static_cast<int>(rng() % 100000)' if name == 'radix_sort' else 'static_cast<int>(rng() % 101)-50'
        yield f'ch08_sort/{name}.cpp', f'''
            for (int trial = 0; trial < 400; ++trial) {{
                int n = rng()%101; std::vector<int> a(n);
                for (int &x : a) x = {value};
                auto expected = a; std::sort(expected.begin(),expected.end());
                {function}(a.data(),n); assert(a == expected);
            }}
        '''
    yield 'ch04_string/pattern_matching.cpp', r'''
        for (int trial = 0; trial < 2000; ++trial) {
            std::string a(rng()%60,'a'), b(rng()%12,'a');
            for (char &c : a) c += rng()%3;
            for (char &c : b) c += rng()%3;
            auto p = a.find(b);
            int expected = p == std::string::npos ? -1 : static_cast<int>(p);
            assert(IndexNaive(a.c_str(),b.c_str()) == expected);
            assert(IndexKMP(a.c_str(),b.c_str()) == expected);
        }
    '''
    yield 'ch07_search/array_search.cpp', r'''
        for (int trial = 0; trial < 1000; ++trial) {
            std::vector<int> a(rng()%100);
            for (int &x : a) x = static_cast<int>(rng()%40)-20;
            std::sort(a.begin(),a.end());
            for (int k = -22; k <= 22; ++k) {
                auto p = std::find(a.begin(),a.end(),k);
                int expected = p == a.end() ? -1 : p-a.begin();
                assert(SequentialSearch(a.data(),a.size(),k) == expected);
                int found = BinarySearch(a.data(),a.size(),k);
                if (expected == -1) assert(found == -1);
                else assert(found >= 0 && found < static_cast<int>(a.size()) && a[found] == k);
                assert(LowerBound(a.data(),a.size(),k) == std::lower_bound(a.begin(),a.end(),k)-a.begin());
            }
        }
    '''
    yield 'ch07_search/binary_search_tree.cpp', r'''
        BSTree root = nullptr; std::set<int> expected;
        for (int i = 0; i < 2000; ++i) {
            int key = rng()%100;
            if (rng()%2) assert(Insert(root,key) == expected.insert(key).second);
            else assert(Delete(root,key) == (expected.erase(key) != 0));
            int out[100] = {}, n = InOrder(root,out);
            assert(n == static_cast<int>(expected.size()));
            assert(std::equal(expected.begin(),expected.end(),out));
            auto p = Search(root,key); assert((p != nullptr) == (expected.count(key) != 0));
        }
        DestroyTree(root); assert(!root);
    '''
    yield 'ch07_search/avl_tree.cpp', r'''
        AVLNode *root = nullptr; std::set<int> expected;
        std::function<int(AVLNode*,long long,long long)> check = [&](AVLNode *p, long long lo, long long hi) {
            if (!p) return 0;
            assert(lo < p->key && p->key < hi);
            int left = check(p->left,lo,p->key), right = check(p->right,p->key,hi);
            assert(std::abs(left-right) <= 1); assert(p->height == 1+std::max(left,right));
            return p->height;
        };
        for (int i = 0; i < 1000; ++i) {
            int key = rng()%500;
            assert(InsertAVL(root,key) == expected.insert(key).second);
            check(root,LLONG_MIN,LLONG_MAX);
        }
        DestroyAVL(root); assert(!root);
    '''
    for name in ('hash_linear_probing', 'hash_chaining'):
        init = 'InitHash(H);' if name == 'hash_linear_probing' else ''
        insertion = '(expected.count(key) == 0 && expected.size() < TABLE_SIZE)' if name == 'hash_linear_probing' else '(expected.count(key) == 0)'
        search = '(Search(H,k) >= 0)' if name == 'hash_linear_probing' else 'Search(H,k)'
        cleanup = '' if name == 'hash_linear_probing' else 'DestroyHash(H);'
        yield f'ch07_search/{name}.cpp', f'''
            HashTable H{{}}; {init} std::set<int> expected;
            for (int i = 0; i < 4000; ++i) {{
                int key = static_cast<int>(rng()%81)-40;
                if (rng()%2) {{
                    bool ok = {insertion}; assert(Insert(H,key) == ok);
                    if (ok) expected.insert(key);
                }} else assert(Delete(H,key) == (expected.erase(key) != 0));
                for (int k = -40; k <= 40; ++k)
                    assert({search} == (expected.count(k) != 0));
            }}
            {cleanup}
        '''
    for name in ('singly_linked_list', 'doubly_linked_list', 'circular_singly_linked_list', 'circular_doubly_linked_list'):
        circular = name.startswith('circular')
        doubly = 'doubly' in name
        typename = 'DLinkList' if doubly else ('CList' if circular else 'LinkList')
        checkprior = 'assert(p->prior == prev); prev = p;' if doubly else ''
        checktail = 'assert(p == L);' if circular else 'assert(p == nullptr);'
        if circular and doubly:
            checktail += 'assert(L->prior == prev);'
        yield f'ch02_linear_list/{name}.cpp', f'''
            {typename} L = nullptr; assert(InitList(L)); std::vector<int> expected;
            for (int i = 0; i < 1000; ++i) {{
                int size = expected.size(), pos = rng()%(size+4)-1, value = rng()%1000;
                if (rng()%2) {{
                    bool ok = pos >= 1 && pos <= size+1;
                    assert(ListInsert(L,pos,value) == ok);
                    if (ok) expected.insert(expected.begin()+pos-1,value);
                }} else {{
                    int removed = -1; bool ok = pos >= 1 && pos <= size;
                    assert(ListDelete(L,pos,removed) == ok);
                    if (ok) {{ assert(removed == expected[pos-1]); expected.erase(expected.begin()+pos-1); }}
                    else assert(removed == -1);
                }}
                auto p = L->next;
                {'auto prev = L;' if doubly else ''}
                for (int x : expected) {{ assert(p && p != L && p->data == x); {checkprior} p = p->next; }}
                {checktail}
            }}
            DestroyList(L); assert(!L);
        '''
    yield 'ch05_tree/disjoint_set.cpp', r'''
        DSU S{}; assert(InitSet(S,50)); int group[50];
        for (int i = 0; i < 50; ++i) group[i] = i;
        for (int t = 0; t < 1000; ++t) {
            int a = rng()%50, b = rng()%50, old = group[b], target = group[a];
            assert(Union(S,a,b) == (old != target));
            for (int i = 0; i < 50; ++i) if (group[i] == old) group[i] = target;
            for (int i = 0; i < 50; ++i) {
                int size = 0;
                for (int j = 0; j < 50; ++j) {
                    assert((Find(S,i) == Find(S,j)) == (group[i] == group[j]));
                    if (group[i] == group[j]) ++size;
                }
                assert(S.parent[Find(S,i)] == -size);
            }
        }
    '''
    yield 'ch06_graph/shortest_paths.cpp', r'''
        for (int trial = 0; trial < 200; ++trial) {
            Graph G{}; G.n = 1+rng()%10;
            for (int i = 0; i < G.n; ++i)
                for (int j = 0; j < G.n; ++j)
                    G.w[i][j] = i == j ? 0 : (rng()%3 ? static_cast<int>(rng()%20) : INF);
            int floyd[VMAX][VMAX] = {}; Floyd(G,floyd);
            for (int s = 0; s < G.n; ++s) {
                int expected[VMAX], dist[VMAX], parent[VMAX];
                for (int i = 0; i < G.n; ++i) expected[i] = i == s ? 0 : INF;
                // 独立的 Bellman-Ford 松弛作为预期结果。
                for (int pass = 1; pass < G.n; ++pass)
                    for (int u = 0; u < G.n; ++u)
                        for (int v = 0; v < G.n; ++v)
                            if (expected[u] != INF && G.w[u][v] != INF)
                                expected[v] = std::min(expected[v],expected[u]+G.w[u][v]);
                assert(Dijkstra(G,s,dist,parent));
                for (int v = 0; v < G.n; ++v) {
                    assert(dist[v] == expected[v]); assert(floyd[s][v] == expected[v]);
                    if (v == s || dist[v] == INF) assert(parent[v] == -1);
                    else { assert(parent[v] >= 0 && parent[v] < G.n);
                           assert(dist[parent[v]]+G.w[parent[v]][v] == dist[v]); }
                }
            }
        }
    '''
    yield 'ch06_graph/minimum_spanning_tree.cpp', r'''
        for (int trial = 0; trial < 100; ++trial) {
            Graph G{}; G.n = 4;
            struct E { int u,v,w; }; std::vector<E> edges;
            for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) G.w[i][j] = i == j ? 0 : INF;
            for (int i = 0; i < 4; ++i) for (int j = i+1; j < 4; ++j) if (rng()%3) {
                int w = rng()%15; G.w[i][j] = G.w[j][i] = w; edges.push_back({i,j,w});
            }
            int best = INF;
            // 枚举全部三边子集，独立检查连通性并求最小权值。
            for (unsigned mask = 0; mask < (1u<<edges.size()); ++mask) {
                int count = 0, total = 0; bool connected[4][4] = {};
                for (unsigned i = 0; i < edges.size(); ++i) if (mask & (1u<<i)) {
                    ++count; total += edges[i].w; connected[edges[i].u][edges[i].v] = connected[edges[i].v][edges[i].u] = true;
                }
                if (count != 3) continue;
                for (int k = 0; k < 4; ++k) for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j)
                    connected[i][j] = connected[i][j] || (connected[i][k] && connected[k][j]);
                if (connected[0][1] && connected[0][2] && connected[0][3]) best = std::min(best,total);
            }
            int a = -1, b = -1;
            assert(Prim(G,a) == (best != INF)); assert(Kruskal(G,b) == (best != INF));
            if (best != INF) assert(a == best && b == best);
            else assert(a == -1 && b == -1);
        }
    '''


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('build_dir', type=Path, help='已编译参考答案的 CMake 构建目录')
    parser.add_argument('--sanitize', action='store_true', help='补充用例启用 AddressSanitizer/UBSan')
    args = parser.parse_args()
    sources = sorted(ROOT.glob('ch*/*.cpp'))
    for source in sources:
        binary = args.build_dir.resolve() / 'bin' / f'{source.parent.name}_{source.stem}'
        output = run([str(binary)])
        if source.stem == 'binary_tree_traversal':
            for label, expected in [('先序遍历:', 'A B D E C'), ('中序遍历:', 'D B E A C'), ('后序遍历:', 'D E B C A')]:
                actual = next(line.split(':', 1)[1].strip() for line in output.splitlines() if line.startswith(label))
                if actual != expected:
                    raise AssertionError(f'{source.name}: {actual} != {expected}')
    print(f'{len(sources)} 个示例全部通过（检查退出码和 FAIL 输出）。', flush=True)
    prelude = '''#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <functional>
#include <random>
#include <set>
#include <string>
#include <vector>
'''
    count = 0
    with tempfile.TemporaryDirectory(prefix='408-check-') as temp:
        for index, (source, body) in enumerate(cases()):
            harness = Path(temp) / f'check_{index}.cpp'
            harness.write_text(prelude + f'#define main exercise_example_main\n#include "{source}"\n#undef main\n'
                               + 'int main() { std::mt19937 rng(408);\n' + body + '\n}\n')
            binary = Path(temp) / f'check_{index}'
            command = shlex.split(os.environ.get('CXX', 'c++')) + ['-std=c++14', '-g', '-I', str(ROOT), '-I', str(ROOT/'common')]
            if args.sanitize:
                command += ['-fsanitize=address,undefined', '-fno-omit-frame-pointer']
            run(command + [str(harness), '-o', str(binary)])
            run([str(binary)])
            count += 1
    print(f'{count} 组补充性质测试通过（种子 408）。')


if __name__ == '__main__':
    main()
