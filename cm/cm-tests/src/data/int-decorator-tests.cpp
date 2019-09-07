#include "int-decorator-tests.h"

#include <QSignalSpy>
#include "data/entity.h"

namespace cm {
namespace data {

static IntDecoratorTests instance;

IntDecoratorTests::IntDecoratorTests()
    : TestSuite("IntDecoratorTests") {}

void IntDecoratorTests::constructor_noParameters_setsDefaultProperties() {

    IntDecorator decorator;
    QCOMPARE(decorator.parentEntity(), nullptr);
    QCOMPARE(decorator.key(), QString("SomeItemKey"));
    QCOMPARE(decorator.label(), QString(""));
    QCOMPARE(decorator.value(), 0);
}

void IntDecoratorTests::constructor_parameters_setsDefaultProperties() {

    Entity parentEntity;
    IntDecorator decorator(&parentEntity, "Test Key", "Test Label", 99);

    QCOMPARE(decorator.parentEntity(), &parentEntity);
    QCOMPARE(decorator.key(), QString("Test Key"));
    QCOMPARE(decorator.label(), QString("Test Label"));
    QCOMPARE(decorator.value(), 99);
}

void IntDecoratorTests::setValue_newValue_updatesValueAndEmitsSignal() {

    IntDecorator decorator;
    QSignalSpy valueChangedSpy(&decorator, &IntDecorator::valueChanged);
    QCOMPARE(decorator.value(), 0);
    decorator.setValue(99);
    QCOMPARE(decorator.value(), 99);
    QCOMPARE(valueChangedSpy.count(), 1);
}

void IntDecoratorTests::setValue_sameValue_takesNoAction() {

    IntDecorator decorator(nullptr, "Test Key", "Test Label", 99);
    QSignalSpy valueChangedSpy(&decorator, &IntDecorator::valueChanged);
    QCOMPARE(decorator.value(), 99);
    decorator.setValue(99);
    QCOMPARE(decorator.value(), 99);
    QCOMPARE(valueChangedSpy.count(), 0);
}

void IntDecoratorTests::jsonValue_defaultValue_returnsJson() {
    IntDecorator decorator;
    QCOMPARE(decorator.jsonValue(), QJsonValue(0));
}

void IntDecoratorTests::jsonValue_setValue_returnsJson() {
    IntDecorator decorator;
    decorator.setValue(99);
    QCOMPARE(decorator.jsonValue(), QJsonValue(99));
}

void IntDecoratorTests::update_presentInJson_updatesValue() {

    IntDecorator decorator(nullptr, "Test Key", "Test Label", 99);
    QSignalSpy valueChangedSpy(&decorator, &IntDecorator::valueChanged);
    QCOMPARE(decorator.value(), 99);
    QJsonObject jsonObject;
    jsonObject.insert("Key 1", "Value 1");
    jsonObject.insert("Test Key", 123);
    jsonObject.insert("Key 3", 3);
    decorator.update(jsonObject);
    QCOMPARE(decorator.value(), 123);
    QCOMPARE(valueChangedSpy.count(), 1);
}

void IntDecoratorTests::update_notPresentInJson_updatesValueToDefault() {

    IntDecorator decorator(nullptr, "Test Key", "Test Label", 99);
    QSignalSpy valueChangedSpy(&decorator, &IntDecorator::valueChanged);
    QCOMPARE(decorator.value(), 99);
    QJsonObject jsonObject;
    jsonObject.insert("Key 1", "Value 1");
    jsonObject.insert("Key 2", 123);
    jsonObject.insert("Key 3", 3);
    decorator.update(jsonObject);
    QCOMPARE(decorator.value(), 0);
    QCOMPARE(valueChangedSpy.count(), 1);
}

}}
