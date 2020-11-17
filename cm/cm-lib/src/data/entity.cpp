#include "entity.h"

#include <QJsonArray>
#include <QUuid>

namespace cm {
namespace data {

class Entity::Implementation {

public:
    Implementation(Entity* entity, const QString& key)
        : entity(entity), key(key), id(QUuid::createUuid().toString()) {}

    Entity* entity{nullptr};
    QString key;
    QString id;
    StringDecorator* primaryKey{nullptr};
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

const QString& Entity::id() const {
    if (impl->primaryKey != nullptr && !impl->primaryKey->value().isEmpty()) {
        return impl->primaryKey->value();
    }
    return impl->id;
}

void Entity::setPrimaryKey(StringDecorator* primaryKey) {
    impl->primaryKey = primaryKey;
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

    // Update ID if already present
    if (jsonObject.contains("id")) {
        impl->id = jsonObject.value("id").toString();
    }
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
    returnValue.insert("id", impl->id);
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
