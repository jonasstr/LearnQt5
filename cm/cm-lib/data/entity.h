#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>

#include "data/data-decorator.h"
#include "data/entity-collection.h"

namespace cm {
namespace data {

class Entity : public QObject {

    Q_OBJECT

public:
    Entity(QObject *parent = nullptr, const QString& key = "SomeEntityKey");
    Entity(QObject *parent, const QString &key, const QJsonObject& jsonObject);
    virtual ~Entity();

    const QString& key() const;
    void update(const QJsonObject& jsonObject);
    QJsonObject toJson() const;

signals:
    void childEntitiesChanged();
    void dataDecoratorsChanged();
    void childCollectionsChanged(const QString& collectionKey);

protected:
    Entity* addChild(Entity* entity, const QString& key);
    DataDecorator* addDataItem(DataDecorator* dataDecorator);
    EntityCollectionBase* addChildCollection(EntityCollectionBase* entityCollection);

protected:
    class Implementation;
    QScopedPointer<Implementation> impl;
};

}}

#endif // ENTITY_H
