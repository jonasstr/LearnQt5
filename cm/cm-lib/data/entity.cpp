#include "entity.h"

#include <QJsonArray>

namespace cm {
namespace data {

class Entity::Implementation {

public:
    Implementation(Entity* _entity, const QString& _key)
        : entity(_entity), key(_key) {}

    Entity* entity{nullptr};
    QString key;
    std::map<QString, Entity*> childEntities;
    std::map<QString, DataDecorator*> dataDecorators;
    std::map<QString, EntityCollectionBase*> childCollections;
};

Entity::Entity(QObject* parent, const QString& key)
    : QObject(parent) {

    impl.reset(new Implementation(this, key));
}

Entity::Entity(QObject* parent, const QString& key, const QJsonObject& jsonObject)
    : Entity(parent, key) {

    update(jsonObject);
}

Entity::~Entity() {}

const QString& Entity::key() const {
    return impl->key;
}

Entity* Entity::addChild(Entity* entity, const QString& key) {
    if(impl->childEntities.find(key) == std::end(impl->childEntities)) {
        impl->childEntities[key] = entity;
        emit childEntitiesChanged();
    }
    return entity;
}

EntityCollectionBase* Entity::addChildCollection(EntityCollectionBase* entityCollection) {
    if(impl->childCollections.find(entityCollection->getKey()) == std::end(impl->childCollections)) {
        impl->childCollections[entityCollection->getKey()] = entityCollection;
        emit childCollectionsChanged(entityCollection->getKey());
    }
    return entityCollection;
}

DataDecorator* Entity::addDataItem(DataDecorator* dataDecorator) {
    if(impl->dataDecorators.find(dataDecorator->key()) == std::end(impl->dataDecorators)) {
        impl->dataDecorators[dataDecorator->key()] = dataDecorator;
        emit dataDecoratorsChanged();
    }
    return dataDecorator;
}

void Entity::update(const QJsonObject& jsonObject) {
    // Update data decorators
    for (std::pair<QString, DataDecorator*> dataDecoratorPair : impl->dataDecorators) {
        dataDecoratorPair.second->update(jsonObject);
    }
    // Update child entities
    for (std::pair<QString, Entity*> childEntityPair : impl->childEntities) {
        childEntityPair.second->update(jsonObject.value(childEntityPair.first).toObject());
    }
    // Update child collections
    for (std::pair<QString, EntityCollectionBase*> childCollectionPair : impl->childCollections) {
        childCollectionPair.second->update(jsonObject.value(childCollectionPair.first).toArray());
    }
}

QJsonObject Entity::toJson() const {
    QJsonObject returnValue;
    // Add data decorators
    for (std::pair<QString, DataDecorator*> dataDecoratorPair : impl->dataDecorators) {
        returnValue.insert(dataDecoratorPair.first, dataDecoratorPair.second->jsonValue());
    }
    // Add child entities
    for (std::pair<QString, Entity*> childEntityPair : impl->childEntities) {
        returnValue.insert(childEntityPair.first, childEntityPair.second->toJson());
    }
    // Add child collections
    for (std::pair<QString, EntityCollectionBase*> childCollectionPair : impl->childCollections) {
        QJsonArray entityArray;
        for (Entity* entity : childCollectionPair.second->baseEntities()) {
            entityArray.append(entity->toJson());
        }
        returnValue.insert(childCollectionPair.first, entityArray);
    }
    return returnValue;
}

}}
