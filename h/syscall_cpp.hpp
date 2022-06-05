#ifndef _syscall_cpp
#define _syscall_cpp

#include "syscall_c.h"

void* operator new(size_t);
void* operator new[](size_t);
void operator delete(void*);
void operator delete[](void*);

class Thread;
typedef void (Thread::*run_ptr)();

typedef void(*user)();

class PeriodicThread;
typedef void (PeriodicThread::*periodic_ptr)();

void user_wrapper(void*);

struct thread_ {
    run_ptr fn;
    Thread* t;
};

struct periodic_thread {

    periodic_ptr periodic_fn;
    PeriodicThread* pt;
    time_t period;
};

struct user_main_{
    user fn;
};

class Thread {
public:
    Thread(void (*body)(void*), void* arg);
    virtual ~Thread();

    int start();

    static void dispatch();
    static int sleep(time_t);

protected:
    Thread();
    virtual void run() {}

private:
    thread_t myHandle;
};

class Semaphore {
public:

    Semaphore(unsigned init = 1);
    virtual ~Semaphore();

    int wait();
    int signal();

private:
    sem_t myHandle;

};

class PeriodicThread : public Thread {
protected:
    PeriodicThread(time_t period);
    virtual void periodicActivation() {}
};

class Console {
public:
    static char getc();
    static void putc(char);
};


#endif