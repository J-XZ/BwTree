cmake_minimum_required(VERSION 3.10)
project(BwTree)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall -mcx16 -Wno-invalid-offsetof")

set(CMAKE_CXX_FLAGS_DEBUG "-g -Og -fno-inline -fno-omit-frame-pointer -DBTREE_DEBUG")
# -DBTREE_DEBUG 用于开启 BwTree 内部的调试信息输出

set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -frename-registers -funroll-loops -flto -march=native -DNDEBUG -DBWTREE_NODEBUG")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -latomic")

# 源文件列表
set(SRC
    test/main.cpp
    src/bwtree.cpp
    test/test_suite.cpp
    test/random_pattern_test.cpp
    test/basic_test.cpp
    test/mixed_test.cpp
    test/performance_test.cpp
    test/stress_test.cpp
    test/iterator_test.cpp
    test/misc_test.cpp
    test/benchmark_bwtree_full.cpp
    benchmark/spinlock/spinlock.cpp
    test/benchmark_btree_full.cpp
    test/benchmark_art_full.cpp
    benchmark/art/art.c
)

# 头文件（仅用于 IDE 提示，不参与编译）
set(HEADERS
    src/bwtree.h
    src/bloom_filter.h
    src/atomic_stack.h
    src/sorted_small_set.h
    test/test_suite.h
)

# main 可执行文件
add_executable(main ${SRC})

# xz_test 可执行文件
add_executable(xz_test test/xz_test.cpp src/bwtree.cpp test/test_suite.cpp test/random_pattern_test.cpp test/basic_test.cpp test/mixed_test.cpp test/performance_test.cpp test/stress_test.cpp test/iterator_test.cpp test/misc_test.cpp test/benchmark_bwtree_full.cpp benchmark/spinlock/spinlock.cpp test/benchmark_btree_full.cpp test/benchmark_art_full.cpp benchmark/art/art.c)

target_link_libraries(main atomic)
target_link_libraries(xz_test atomic)

# jemalloc 预加载（运行时用 LD_PRELOAD）
set(JEMALLOC_PRELOAD "LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libjemalloc.so")

# 方便的自定义命令（等价于 make 的目标）
add_custom_target(benchmark-all
    COMMAND ${JEMALLOC_PRELOAD} $<TARGET_FILE:main> --benchmark-all
    DEPENDS main
)

add_custom_target(benchmark-bwtree
    COMMAND ${JEMALLOC_PRELOAD} $<TARGET_FILE:main> --benchmark-bwtree
    DEPENDS main
)

add_custom_target(benchmark-bwtree-full
    COMMAND ${JEMALLOC_PRELOAD} $<TARGET_FILE:main> --benchmark-bwtree-full
    DEPENDS main
)

add_custom_target(benchmark-btree-full
    COMMAND ${JEMALLOC_PRELOAD} $<TARGET_FILE:main> --benchmark-btree-full
    DEPENDS main
)

add_custom_target(benchmark-art-full
    COMMAND ${JEMALLOC_PRELOAD} $<TARGET_FILE:main> --benchmark-art-full
    DEPENDS main
)

add_custom_target(test
    COMMAND ${JEMALLOC_PRELOAD} $<TARGET_FILE:main> --test
    DEPENDS main
)

add_custom_target(stress-test
    COMMAND ${JEMALLOC_PRELOAD} $<TARGET_FILE:main> --stress-test
    DEPENDS main
)

add_custom_target(epoch-test
    COMMAND ${JEMALLOC_PRELOAD} $<TARGET_FILE:main> --epoch-test
    DEPENDS main
)

add_custom_target(infinite-insert-test
    COMMAND ${JEMALLOC_PRELOAD} $<TARGET_FILE:main> --infinite-insert-test
    DEPENDS main
)

add_custom_target(email-test
    COMMAND ${JEMALLOC_PRELOAD} $<TARGET_FILE:main> --email-test
    DEPENDS main
)

add_custom_target(mixed-test
    COMMAND ${JEMALLOC_PRELOAD} $<TARGET_FILE:main> --mixed-test
    DEPENDS main
)

# 目录准备
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/build)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/stl_test/bin)

# 清理目标
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}/build/*
    COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_BINARY_DIR}/*.log
    COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_BINARY_DIR}/main
)

# 编译方法：
# mkdir build && cd build
# cmake ..
# make -j
# make test         # 运行测试
# make benchmark-all # 运行 benchmark