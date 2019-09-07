#ifndef STRINGDECORATORTESTS_H
#define STRINGDECORATORTESTS_H

#include "data/string-decorator.h"
#include "test-suite.h"

#include <QtTest>

namespace cm {
namespace data {

class StringDecoratorTests : public TestSuite {

    Q_OBJECT

public:
    StringDecoratorTests();

private slots:
    void constructor_noParameters_setsDefaultProperties();
    void constructor_parameters_setsDefaultProperties();
    void setValue_newValue_updatesValueAndEmitsSignal();
    void setValue_sameValue_takesNoAction();
    void jsonValue_defaultValue_returnsJson();
    void jsonValue_setValue_returnsJson();
    void update_presentInJson_updatesValue();
    void update_notPresentInJson_updatesValueToDefault();
};

}}

#endif // STRINGDECORATORTESTS_H
