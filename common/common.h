#ifndef COMMON_COMMON_H
#define COMMON_COMMON_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

// ==========================================
// 408 考研数据结构 —— 公共定义
// ==========================================

// 状态码
#define OK    1
#define ERROR 0
#define TRUE  1
#define FALSE 0

// 一些常用的最大容量
#define MAX_SIZE 100
#define MAX_VERTEX_NUM 100

// 简单的断言宏（用于自测）
#define test(expr) \
    do { \
        if (expr) { \
            printf("[PASS] %s\n", #expr); \
        } else { \
            printf("[FAIL] %s  (line %d)\n", #expr, __LINE__); \
        } \
    } while(0)

// 带消息的测试宏
#define test_msg(expr, msg) \
    do { \
        if (expr) { \
            printf("[PASS] %s\n", msg); \
        } else { \
            printf("[FAIL] %s  (line %d)\n", msg, __LINE__); \
        } \
    } while(0)

// 分隔线
#define hr() printf("──────────────────────────────────\n")

#endif // COMMON_COMMON_H
