#ifndef MYTHREAD_H
#define MYTHREAD_H

#include<QThread>
#include<vector>
#include "Note.h"
#include "service.h"

class MyThread  :public QThread
{

    Q_OBJECT

public:
    MyThread();
    void run(std::vector <Note*> listNote);
};

#endif // MYTHREAD_H
