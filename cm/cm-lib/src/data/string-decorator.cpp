#include "string-decorator.h"
#include <QVariant>

namespace cm {
namespace data {

class StringDecorator::Implementation {
public:

    Implementation(StringDecorator* decorator, const QString& value)
        : decorator(decorator), value(value) {}

    StringDecorator* decorator;
    QString value;
};

StringDecorator::StringDecorator(Entity* parent, const QString& key,
                                 const QString& label, const QString& value)
    : DataDecorator(parent, key, label) {

    impl.reset(new Implementation(this, value));
}

StringDecorator::~StringDecorator() {}

const QString& StringDecorator::value() const {
    return impl->value;
}

StringDecorator& StringDecorator::setValue(const QString &value) {
    if (value != impl->value) {
        impl->value = value;
        emit valueChanged();
    }
    return *this;
}

QJsonValue StringDecorator::jsonValue() const {
    return QJsonValue::fromVariant(QVariant(impl->value));
}

void StringDecorator::update(const QJsonObject &jsonObject) {
    if (jsonObject.contains(key())) {
        setValue(jsonObject.value(key()).toString());
    } else {
        setValue("");
    }
}
}}
