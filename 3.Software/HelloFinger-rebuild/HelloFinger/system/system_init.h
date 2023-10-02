#ifndef SYSTEM_INIT_H
#define SYSTEM_INIT_H

#include <QObject>

class System_Init : public QObject
{
    Q_OBJECT
public:
    explicit System_Init(QObject *parent = nullptr);

signals:

};

#endif // SYSTEM_INIT_H
