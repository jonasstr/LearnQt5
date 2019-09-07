#ifndef DATETIMEDECORATORTESTS_H
#define DATETIMEDECORATORTESTS_H

#include "data/datetime-decorator.h"
#include "test-suite.h"

#include <QtTest>
#include <QDateTime>

namespace cm {
namespace data {

class DateTimeDecoratorTests : public TestSuite {

    Q_OBJECT

public:
    DateTimeDecoratorTests();

private slots:
    void constructor_noParameters_setsDefaultProperties();
    void constructor_parameters_setsDefaultProperties();
    void setValue_newValue_updatesValueAndEmitsSignal();
    void setValue_sameValue_takesNoAction();
    void jsonValue_defaultValue_returnsJson();
    void jsonValue_setValue_returnsJson();
    void update_presentInJson_updatesValue();
    void update_notPresentInJson_updatesValueToDefault();

    void toIso8601String_defaultValue_returnsString();
    void toIso8601String_valueSet_returnsString();
    void toPrettyDateString_defaultValue_returnsString();
    void toPrettyDateString_valueSet_returnsString();
    void toPrettyTimeString_defaultValue_returnsString();
    void toPrettyTimeString_valueSet_returnsString();
    void toPrettyString_defaultValue_returnsString();
    void toPrettyString_valueSet_returnsString();

private:
    QDateTime testDate {QDate(2019, 9, 17), QTime(18, 22, 20)};
};

}}

#endif // DATETIMEDECORATORTESTS_H
