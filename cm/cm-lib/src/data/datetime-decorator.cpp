#include <QVariant>

#include "datetime-decorator.h"

namespace cm {
namespace data {

class DateTimeDecorator::Implementation {
public:

    Implementation(DateTimeDecorator* decorator, const QDateTime& value)
        : decorator(decorator), value(value) {}

    DateTimeDecorator* decorator;
    QDateTime value;
};

DateTimeDecorator::DateTimeDecorator(Entity* parent, const QString& key,
                                 const QString& label, const QDateTime& value)
    : DataDecorator(parent) {

    impl.reset(new Implementation(this, value));
}

DateTimeDecorator::~DateTimeDecorator() {}

const QDateTime& DateTimeDecorator::value() const {
    return impl->value;
}

const QString& DateTimeDecorator::toIso8601String() const {
    if (impl->value.isNull()) {
        return "";
    } else {
        return impl->value.toString(Qt::ISODate);
    }
}

const QString& DateTimeDecorator::toPrettyString() const {
    if (impl->value.isNull()) {
        return "Not set";
    } else {
        return impl->value.toString("ddd d MMM <<<< @ HH:mm:ss");
    }
}

const QString& DateTimeDecorator::toPrettyDateString() const {
    if (impl->value.isNull()) {
        return "Not set";
    } else {
        return impl->value.toString("d MMM yyyy");
    }
}

const QString& DateTimeDecorator::toPrettyTimeString() const {
    if (impl->value.isNull()) {
        return "Not set";
    } else {
        return impl->value.toString("hh:mm ap");
    }
}

DateTimeDecorator& DateTimeDecorator::setValue(const QDateTime& value) {
    if (value != impl->value) {
        impl->value = value;
        emit valueChanged();
    }
    return *this;
}

QJsonValue DateTimeDecorator::jsonValue() const {
    return QJsonValue::fromVariant(QVariant(impl->value.toString(Qt::ISODate)));
}

void DateTimeDecorator::update(const QJsonObject& jsonObject) {
    if (jsonObject.contains(key())) {
        auto valueAsString = jsonObject.value(key()).toString();
        auto valueAsDate = QDateTime::fromString(valueAsString, Qt::ISODate); // yyyy-MM-ddTHH:mm:ss
        setValue(valueAsDate);
    } else {
        setValue(QDateTime());
    }
}
}}
