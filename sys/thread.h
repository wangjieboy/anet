
#ifndef SYS_THREAD_H_
#define SYS_THREAD_H_

#include <linux/unistd.h>

namespace sys {

class CThread {

public:
CThread() {
tid = 0;
pid = 0;
}

bool start(Runnable *r, void *a) {
runnable = r;
args = a;
return 0 == pthread_create(&tid, NULL, CThread::hook, this);
}

void join() {
if (tid) {
pthread_join(tid, NULL);
tid = 0;
pid = 0;
}
}

Runnable *getRunnable() {
return runnable;
}

void *getArgs() {
return args;
}

int getpid() {
return pid;
}


static void *hook(void *arg) {
CThread *thread = (CThread*) arg;
thread->pid = gettid();

if (thread->getRunnable()) {
thread->getRunnable()->run(thread, thread->getArgs());
}

return (void*) NULL;
}

private:
#ifdef _syscall0
static _syscall0(pid_t,gettid)
#else
static pid_t gettid() { return static_cast<pid_t>(syscall(__NR_gettid));}
#endif

private:
pthread_t tid;      // pthread_self() id
int pid;            // 线程的进程ID
Runnable *runnable;
void *args;
};

}

#endif /*THREAD_H_*/