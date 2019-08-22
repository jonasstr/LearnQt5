#include "data-decorator.h"

namespace cm {
namespace data {
class DataDecorator::Implementation {

public:
    Implementation(Entity* parent, const QString& key, const QString& label)
        : parentEntity(parent), key(key), label(label) {}

    Entity* parentEntity;
    QString key;
    QString label;
};

DataDecorator::DataDecorator(Entity* parent, const QString& key, const QString& label) : QObject((QObject*)parent) {
    impl.reset(new Implementation(parent, key, label));
}

DataDecorator::~DataDecorator() {}

const QString& DataDecorator::key() const {
    return impl->key;
}

const QString& DataDecorator::label() const {
    return impl->label;
}

Entity* DataDecorator::parentEntity() {
    return impl->parentEntity;
}

}}
