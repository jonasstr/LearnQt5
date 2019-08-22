#ifndef INTDECORATOR_H
#define INTDECORATOR_H

#include <data/data-decorator.h>

namespace cm {
namespace data {

class CMLIBSHARED_EXPORT IntDecorator : public DataDecorator {

    Q_OBJECT
    Q_PROPERTY(int ui_value READ value WRITE setValue NOTIFY valueChanged)

public:
    IntDecorator(Entity *parent = nullptr, const QString& key = "SomeItemKey",
                    const QString& label = "", int value = 0);
    ~IntDecorator();

    IntDecorator& setValue(int value);
    int value() const;

    QJsonValue jsonValue() const override;
    void update(const QJsonObject &jsonObject) override;

signals:
    void valueChanged();

private:
    class Implementation;
    QScopedPointer<Implementation> impl;
};
}}

#endif // INTDECORATOR_H
