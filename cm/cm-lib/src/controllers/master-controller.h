#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H

#include <QObject>
#include <cm-lib_global.h>

namespace cm {
namespace controllers {

class CMLIBSHARED_EXPORT MasterController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString ui_welcomeMsg MEMBER welcomeMsg CONSTANT)

public:
    explicit MasterController(QObject *parent = nullptr);

    QString welcomeMsg = "Hello there, General Kenobi!";
};
}}

#endif
