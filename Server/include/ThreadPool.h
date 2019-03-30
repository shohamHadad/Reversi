#ifndef EX4_SERVER_THREADPOOL_H
#define EX4_SERVER_THREADPOOL_H

#include "Task.h"
#include <queue>
#include <pthread.h>

using namespace std;

class ThreadPool {
public:
  ThreadPool(int threadsNum);
  void addTask (Task *task);
  void terminate();
  virtual ~ThreadPool();
  static void* execute(void* arg);

private:
  queue<Task*> tasksQueue;
  pthread_t* threads;
  void executeTasks();
  bool stopped;
  pthread_mutex_t lock;
};


#endif //EX4_SERVER_THREADPOOL_H
