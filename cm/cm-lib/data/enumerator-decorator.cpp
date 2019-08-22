#include <QVariant>
#include "enumerator-decorator.h"

namespace cm {
namespace data {

class EnumeratorDecorator::Implementation {
public:

    Implementation(EnumeratorDecorator* decorator, std::map<int, QString> descriptionMapper, int value)
        : decorator(decorator), descriptionMapper(descriptionMapper), value(value) {}

    EnumeratorDecorator* decorator;
    std::map<int, QString> descriptionMapper;
    int value;
};

EnumeratorDecorator::EnumeratorDecorator(Entity* parent, const QString& key,
                                 const QString& label, int value, const std::map<int, QString> descriptionMapper)
    : DataDecorator(parent) {

    impl.reset(new Implementation(this, descriptionMapper, value));
}

EnumeratorDecorator::~EnumeratorDecorator() {}

int EnumeratorDecorator::value() const {
    return impl->value;
}

QString EnumeratorDecorator::valueDescription() const {
    if (impl->descriptionMapper.find(impl->value) != impl->descriptionMapper.end()) {
        return impl->descriptionMapper.at(impl->value);
    }
    return {};
}

EnumeratorDecorator& EnumeratorDecorator::setValue(int value) {
    if (value != impl->value) {
        impl->value = value;
        emit valueChanged();
    }
    return *this;
}

QJsonValue EnumeratorDecorator::jsonValue() const {
    return QJsonValue::fromVariant(QVariant(impl->value));
}

void EnumeratorDecorator::update(const QJsonObject &jsonObject) {
    if (jsonObject.contains(key())) {
        setValue(jsonObject.value(key()).toInt());
    } else {
        setValue(0);
    }
}
}}
