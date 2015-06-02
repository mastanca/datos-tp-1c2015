#ifndef TP2TALLER_SERVIDOR_SRC_SERVER_THREAD_H_
#define TP2TALLER_SERVIDOR_SRC_SERVER_THREAD_H_
#include <pthread.h>

class Thread {
 public:
  Thread();
  virtual ~Thread();
  void start();
  void join();
  virtual void run();
  bool isMuerto() const;
  void setMuerto(bool estaMuerto);

 protected:
  bool muerto;
 private:
  pthread_t thread;
  static void *starter(void* data);
};

#endif
