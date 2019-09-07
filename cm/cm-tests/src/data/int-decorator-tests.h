#ifndef INTDECORATORTESTS_H
#define INTDECORATORTESTS_H

#include "data/int-decorator.h"
#include "test-suite.h"

#include <QtTest>

namespace cm {
namespace data {

class IntDecoratorTests : public TestSuite {

    Q_OBJECT

public:
    IntDecoratorTests();

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

#endif // INTDECORATORTESTS_H
