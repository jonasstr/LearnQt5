#ifndef STRINGDECORATOR_H
#define STRINGDECORATOR_H

#include <data/data-decorator.h>

namespace cm {
namespace data {

class CMLIBSHARED_EXPORT StringDecorator : public DataDecorator {

    Q_OBJECT
    Q_PROPERTY(QString ui_value READ value WRITE setValue NOTIFY valueChanged)

public:
    StringDecorator(Entity *parent = nullptr, const QString& key = "SomeItemKey",
                    const QString& label = "", const QString& value = "");
    ~StringDecorator();

    StringDecorator& setValue(const QString& value);
    const QString& value() const;

    QJsonValue jsonValue() const override;
    void update(const QJsonObject &jsonObject) override;

signals:
    void valueChanged();

public:
    class Implementation;
    QScopedPointer<Implementation> impl;
};
}}

#endif // STRINGDECORATOR_H
