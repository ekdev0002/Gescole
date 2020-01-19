#include "mythread.h"

MyThread::MyThread()
{

}

void MyThread::run(std::vector <Note*> listNote)
{

    QString text;
    for (int i=0;i<listNote.size();i++)
    {
        this->sleep(1);
        text="NOTE-"+Service::genererId();
        qDebug()<<text;
        listNote[i]->Setid(text);
        Service::Persister(listNote[i]);
    }
}
