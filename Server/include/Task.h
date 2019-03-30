#ifndef EX4_SERVER_TASK_H
#define EX4_SERVER_TASK_H

class Task {
public:
    Task(void* (*func)(void*arg), void* arg): func(func), arg(arg) {}
    void execute() {
        func(arg);
    }
    virtual ~Task() {}

private:
    void* (*func)(void*arg);
    void* arg;
};

#endif //EX4_SERVER_TASK_H
