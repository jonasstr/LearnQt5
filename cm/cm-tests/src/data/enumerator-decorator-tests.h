#ifndef ENUMERATORDECORATORTESTS_H
#define ENUMERATORDECORATORTESTS_H

#include "data/enumerator-decorator.h"
#include "test-suite.h"

#include <QtTest>
#include <map>

namespace cm {
namespace data {

class EnumeratorDecoratorTests : public TestSuite {

    Q_OBJECT

public:
    EnumeratorDecoratorTests();

private slots:
    void constructor_noParameters_setsDefaultProperties();
    void constructor_parameters_setsDefaultProperties();
    void setValue_newValue_updatesValueAndEmitsSignal();
    void setValue_sameValue_takesNoAction();
    void jsonValue_defaultValue_returnsJson();
    void jsonValue_setValue_returnsJson();
    void update_presentInJson_updatesValue();
    void update_notPresentInJson_updatesValueToDefault();

private:
    enum TestEnum {
        UNKNOWN = 0,
        VALUE_1,
        VALUE_2,
        VALUE_3
    };

    const std::map<int, QString> descriptionMapper {
        {static_cast<int>(TestEnum::UNKNOWN), ""},
        {static_cast<int>(TestEnum::VALUE_1), "Value 1"},
        {static_cast<int>(TestEnum::VALUE_2), "Value 2"},
        {static_cast<int>(TestEnum::VALUE_3), "Value 3"}
    };
};

}}

#endif // ENUMERATORDECORATORTESTS_H
