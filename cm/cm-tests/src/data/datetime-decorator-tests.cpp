#include "datetime-decorator-tests.h"

#include <QSignalSpy>
#include "data/entity.h"

namespace cm {
namespace data {

static DateTimeDecoratorTests instance;

DateTimeDecoratorTests::DateTimeDecoratorTests()
    : TestSuite("DateTimeDecoratorTests") {}

void DateTimeDecoratorTests::constructor_noParameters_setsDefaultProperties() {

    DateTimeDecorator decorator;
    QCOMPARE(decorator.parentEntity(), nullptr);
    QCOMPARE(decorator.key(), QString("SomeItemKey"));
    QCOMPARE(decorator.label(), QString(""));
    QCOMPARE(decorator.value(), QDateTime());
}

void DateTimeDecoratorTests::constructor_parameters_setsDefaultProperties() {

    Entity parentEntity;
    DateTimeDecorator decorator(&parentEntity, "Test Key", "Test Label", testDate);

    QCOMPARE(decorator.parentEntity(), &parentEntity);
    QCOMPARE(decorator.key(), QString("Test Key"));
    QCOMPARE(decorator.label(), QString("Test Label"));
    QCOMPARE(decorator.value(), testDate);
}

void DateTimeDecoratorTests::setValue_newValue_updatesValueAndEmitsSignal() {

    DateTimeDecorator decorator;
    QSignalSpy valueChangedSpy(&decorator, &DateTimeDecorator::valueChanged);
    QCOMPARE(decorator.value(), QDateTime());
    decorator.setValue(testDate);
    QCOMPARE(decorator.value(), testDate);
    QCOMPARE(valueChangedSpy.count(), 1);
}

void DateTimeDecoratorTests::setValue_sameValue_takesNoAction() {

    DateTimeDecorator decorator(nullptr, "Test Key", "Test Label", testDate);
    QSignalSpy valueChangedSpy(&decorator, &DateTimeDecorator::valueChanged);
    QCOMPARE(decorator.value(), testDate);
    decorator.setValue(testDate);
    QCOMPARE(decorator.value(), testDate);
    QCOMPARE(valueChangedSpy.count(), 0);
}

void DateTimeDecoratorTests::jsonValue_defaultValue_returnsJson() {
    DateTimeDecorator decorator;
    QCOMPARE(decorator.jsonValue(), QJsonValue(QDateTime().toString(Qt::ISODate)));
}

void DateTimeDecoratorTests::jsonValue_setValue_returnsJson() {
    DateTimeDecorator decorator;
    decorator.setValue(testDate);
    QCOMPARE(decorator.jsonValue(), QJsonValue(testDate.toString(Qt::ISODate)));
}

void DateTimeDecoratorTests::update_presentInJson_updatesValue() {

    DateTimeDecorator decorator(nullptr, "Test Key", "Test Label", testDate);
    QSignalSpy valueChangedSpy(&decorator, &DateTimeDecorator::valueChanged);
    QDateTime newDate{QDate(2018, 12, 31), QTime(23, 59, 59)};

    QCOMPARE(decorator.value(), testDate);
    QJsonObject jsonObject;
    jsonObject.insert("Key 1", "Value 1");
    jsonObject.insert("Test Key", newDate.toString(Qt::ISODate));
    jsonObject.insert("Key 3", 3);
    decorator.update(jsonObject);
    QCOMPARE(decorator.value(), newDate);
    QCOMPARE(valueChangedSpy.count(), 1);
}

void DateTimeDecoratorTests::update_notPresentInJson_updatesValueToDefault() {

    DateTimeDecorator decorator(nullptr, "Test Key", "Test Label", testDate);
    QSignalSpy valueChangedSpy(&decorator, &DateTimeDecorator::valueChanged);
    QDateTime newDate{QDate(2018, 12, 31), QTime(23, 59, 59)};

    QCOMPARE(decorator.value(), testDate);
    QJsonObject jsonObject;
    jsonObject.insert("Key 1", "Value 1");
    jsonObject.insert("Key 2", newDate.toString(Qt::ISODate));
    jsonObject.insert("Key 3", 3);
    decorator.update(jsonObject);
    QCOMPARE(decorator.value(), QDateTime());
    QCOMPARE(valueChangedSpy.count(), 1);
}

void DateTimeDecoratorTests::toIso8601String_defaultValue_returnsString() {
    DateTimeDecorator decorator;
    QCOMPARE(decorator.toIso8601String(), QString(""));
}

void DateTimeDecoratorTests::toIso8601String_valueSet_returnsString() {
    DateTimeDecorator decorator;
    decorator.setValue(testDate);
    QCOMPARE(decorator.toIso8601String(), QString("2019-09-17T18:22:20"));
}

void DateTimeDecoratorTests::toPrettyDateString_defaultValue_returnsString() {
    DateTimeDecorator decorator;
    QCOMPARE(decorator.toPrettyDateString(), QString("Not set"));
}

void DateTimeDecoratorTests::toPrettyDateString_valueSet_returnsString() {
    DateTimeDecorator decorator;
    decorator.setValue(testDate);
    QCOMPARE(decorator.toPrettyDateString(), QString("17 Sep. 2019"));
}

void DateTimeDecoratorTests::toPrettyTimeString_defaultValue_returnsString() {
    DateTimeDecorator decorator;
    QCOMPARE(decorator.toPrettyTimeString(), QString("Not set"));
}

void DateTimeDecoratorTests::toPrettyTimeString_valueSet_returnsString() {
    DateTimeDecorator decorator;
    decorator.setValue(testDate);
    QCOMPARE(decorator.toPrettyTimeString(), QString("06:22 nachm."));
}

void DateTimeDecoratorTests::toPrettyString_defaultValue_returnsString() {
    DateTimeDecorator decorator;
    QCOMPARE(decorator.toPrettyString(), QString("Not set"));
}

void DateTimeDecoratorTests::toPrettyString_valueSet_returnsString() {
    DateTimeDecorator decorator;
    decorator.setValue(testDate);
    QCOMPARE(decorator.toPrettyString(), QString("Di. 17 Sep. <<<< @ 18:22:20"));
}

}}
