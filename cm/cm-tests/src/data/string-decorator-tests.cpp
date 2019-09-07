#include "string-decorator-tests.h"

#include <QSignalSpy>
#include "data/entity.h"

namespace cm {
namespace data {

static StringDecoratorTests instance;

StringDecoratorTests::StringDecoratorTests()
    : TestSuite("StringDecoratorTests") {}

void StringDecoratorTests::constructor_noParameters_setsDefaultProperties() {

    StringDecorator decorator;
    QCOMPARE(decorator.parentEntity(), nullptr);
    QCOMPARE(decorator.key(), QString("SomeItemKey"));
    QCOMPARE(decorator.label(), QString(""));
    QCOMPARE(decorator.value(), QString(""));
}

void StringDecoratorTests::constructor_parameters_setsDefaultProperties() {

    Entity parentEntity;
    StringDecorator decorator(&parentEntity, "Test Key", "Test Label", QString("Test Value"));

    QCOMPARE(decorator.parentEntity(), &parentEntity);
    QCOMPARE(decorator.key(), QString("Test Key"));
    QCOMPARE(decorator.label(), QString("Test Label"));
    QCOMPARE(decorator.value(), QString("Test Value"));
}

void StringDecoratorTests::setValue_newValue_updatesValueAndEmitsSignal() {

    StringDecorator decorator;
    QSignalSpy valueChangedSpy(&decorator, &StringDecorator::valueChanged);
    QCOMPARE(decorator.value(), QString(""));
    decorator.setValue(QString("Test Value"));
    QCOMPARE(decorator.value(), QString("Test Value"));
    QCOMPARE(valueChangedSpy.count(), 1);
}

void StringDecoratorTests::setValue_sameValue_takesNoAction() {

    StringDecorator decorator(nullptr, "Test Key", "Test Label", QString("Test Value"));
    QSignalSpy valueChangedSpy(&decorator, &StringDecorator::valueChanged);
    QCOMPARE(decorator.value(), QString("Test Value"));
    decorator.setValue(QString("Test Value"));
    QCOMPARE(decorator.value(), QString("Test Value"));
    QCOMPARE(valueChangedSpy.count(), 0);
}

void StringDecoratorTests::jsonValue_defaultValue_returnsJson() {
    StringDecorator decorator;
    QCOMPARE(decorator.jsonValue(), QJsonValue(""));
}

void StringDecoratorTests::jsonValue_setValue_returnsJson() {
    StringDecorator decorator;
    decorator.setValue(QString("Test Value"));
    QCOMPARE(decorator.jsonValue(), QJsonValue(QString("Test Value")));
}

void StringDecoratorTests::update_presentInJson_updatesValue() {

    StringDecorator decorator(nullptr, "Test Key", "Test Label", QString("Test Value"));
    QSignalSpy valueChangedSpy(&decorator, &StringDecorator::valueChanged);
    QCOMPARE(decorator.value(), QString("Test Value"));
    QJsonObject jsonObject;
    jsonObject.insert("Key 1", "Value 1");
    jsonObject.insert("Test Key", QString("New Test Value"));
    jsonObject.insert("Key 3", 3);
    decorator.update(jsonObject);
    QCOMPARE(decorator.value(), QString("New Test Value"));
    QCOMPARE(valueChangedSpy.count(), 1);
}

void StringDecoratorTests::update_notPresentInJson_updatesValueToDefault() {

    StringDecorator decorator(nullptr, "Test Key", "Test Label", QString("Test Value"));
    QSignalSpy valueChangedSpy(&decorator, &StringDecorator::valueChanged);
    QCOMPARE(decorator.value(), QString("Test Value"));
    QJsonObject jsonObject;
    jsonObject.insert("Key 1", "Value 1");
    jsonObject.insert("Key 2", 123);
    jsonObject.insert("Key 3", 3);
    decorator.update(jsonObject);
    QCOMPARE(decorator.value(), QString(""));
    QCOMPARE(valueChangedSpy.count(), 1);
}

}}
