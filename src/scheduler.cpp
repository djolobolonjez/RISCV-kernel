#include "../h/scheduler.h"

TCB* Scheduler::head;
TCB* Scheduler::tail;

class TCB;

TCB* Scheduler::idleThread = nullptr;

TCB* Scheduler::get() {

    if(!head) return idleThread;
    TCB* data = head;
    head = head->next;

    data->next = nullptr;
    if(!head) tail = nullptr;
    else head->prev = nullptr;

    return data;

}

void Scheduler::put(TCB* tcb){

    if(tail){
        tail->next = tcb;
        tcb->prev = tail;
        tail = tail->next;
    }else
    {
        head = tail = tcb;
    }

}

void Scheduler::idle(void*) {
    while(1) { thread_dispatch(); }
};