
/*
 * test_suite.cpp
 *
 * This files includes basic testing infrastructure
 *
 * by Ziqi Wang
 */

#include "test_suite.h"

/*
 * GetEmptyTree() - Return an empty BwTree with proper constructor argument
 *                  in order to finish all tests without problem
 *
 * This function will switch print_flag on and off before and after calling
 * the constructor, in order to print tree metadata under debug mode
 */
/**
 * @brief 返回一个使用适当构造函数参数创建的空 BwTree，以确保所有测试能够顺利完成。
 * 这个函数会在调用构造函数之前和之后切换 print_flag，以便在调试模式下打印树的元数据。
 *
 * @param no_print
 * @return TreeType* 返回空的BwTree对象
 */
TreeType *GetEmptyTree(bool no_print) {
  if (no_print == false) {
    print_flag = true;
  }

  TreeType *t1 = new TreeType{true, KeyComparator{1}, KeyEqualityChecker{1}};

  // By default let is serve single thread (i.e. current one)
  // and assign gc_id = 0 to the current thread
  // - 默认情况下，让创建的 BwTree 仅服务于单线程（即当前线程）。
  // - 同时，将垃圾回收器（GC）的线程 ID 设置为0，并分配给当前线程。
  t1->UpdateThreadLocal(1);
  t1->AssignGCID(0);

  print_flag = false;

  return t1;
}

/*
 * GetEmptyBTree() - Returns an empty Btree multimap object created on the heap
 */
BTreeType *GetEmptyBTree() {
  BTreeType *t = new BTreeType{KeyComparator{1}};

  return t;
}

/*
 * DestroyTree() - Deletes a tree and release all resources
 *
 * This function will enable and disable print flag before and after
 * calling the destructor in order to print out the process of
 * tree destruction under debug mode
 */
void DestroyTree(TreeType *t, bool no_print) {
  if (no_print == false) {
    print_flag = true;
  }

  delete t;

  print_flag = false;

  return;
}

/*
 * DestroyBTree() - Destroies the btree multimap instance created on the heap
 */
void DestroyBTree(BTreeType *t) {
  delete t;
}

/*
 * PrintStat() - Print the current statical information on stdout
 */
void PrintStat(TreeType *t) {
  printf("Insert op = %lu; abort = %lu; abort rate = %lf\n", t->insert_op_count.load(),
         t->insert_abort_count.load(),
         (double)t->insert_abort_count.load() / (double)t->insert_op_count.load());

  printf("Delete op = %lu; abort = %lu; abort rate = %lf\n", t->delete_op_count.load(),
         t->delete_abort_count.load(),
         (double)t->delete_abort_count.load() / (double)t->delete_op_count.load());

  return;
}

/*
 * PinToCore() - Pin the current calling thread to a particular core
 */
void PinToCore(size_t core_id) {
  cpu_set_t cpu_set;
  CPU_ZERO(&cpu_set);
  CPU_SET(core_id, &cpu_set);

  int ret = pthread_setaffinity_np(pthread_self(), sizeof(cpu_set), &cpu_set);

  printf("pthread_setaffinity_np() returns %d\n", ret);

  return;
}
