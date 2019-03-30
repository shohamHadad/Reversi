#include "ThreadPool.h"
#include <unistd.h>
#define SLEEP_TIME 1

ThreadPool::ThreadPool(int threadsNum): stopped(false) {
    threads = new pthread_t [threadsNum];
    for(int i = 0; i < threadsNum; i++) {
        pthread_create(threads + i, NULL, execute, this);
    }
    pthread_mutex_init (&lock, NULL);
}

void* ThreadPool::execute(void* arg) {
    ThreadPool* pool = (ThreadPool*)arg;
    pool->executeTasks();
}

void ThreadPool::addTask(Task *task) {
    pthread_mutex_trylock(&lock);
    tasksQueue.push(task);
    pthread_mutex_unlock(&lock);
}

void ThreadPool::executeTasks() {
    while (!stopped) {
        pthread_mutex_trylock(&lock);
        if(!tasksQueue.empty()) {
            Task* task = tasksQueue.front();
            tasksQueue.pop();
            pthread_mutex_unlock (&lock);
            task->execute();
            delete task;
        }
        else {
            pthread_mutex_unlock (&lock);
            sleep(SLEEP_TIME);
        }
    }
}

void ThreadPool::terminate() {
    stopped = true;
    pthread_mutex_destroy (&lock);
}

ThreadPool ::~ThreadPool() {
    delete [] threads;
    while (!tasksQueue.empty()) {
        Task* t = tasksQueue.front();
        tasksQueue.pop();
        delete t;
    }
}
