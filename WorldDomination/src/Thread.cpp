#include "Thread.h"

#include <pthread.h>

Thread::Thread() {
  this->muerto = false;
  this->thread = 0;
}

Thread::~Thread() {
}

void* Thread::starter(void* data) {
  Thread* realthread = (Thread*) data;
  realthread->run();
  return NULL;
}

void Thread::join() {
  pthread_join(this->thread, NULL);
}

void Thread::start() {
  pthread_create(&this->thread, NULL, starter, this);
}

void Thread::run() {
}

bool Thread::isMuerto() const {
  return this->muerto;
}

void Thread::setMuerto(bool estaMuerto) {
  this->muerto = estaMuerto;
}
