#ifndef DEBUG_H
#define DEBUG_H

#include <QObject>

class Debug : public QObject
{
    Q_OBJECT
public:
    explicit Debug(QObject *parent = nullptr);

signals:

public slots:
};

#endif // DEBUG_H