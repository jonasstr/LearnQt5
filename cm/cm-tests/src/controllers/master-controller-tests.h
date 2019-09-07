#ifndef MASTERCONTROLLERTESTS_H
#define MASTERCONTROLLERTESTS_H

#include <QtTest>

#include "controllers/master-controller.h"
#include "test-suite.h"

namespace cm {
namespace controllers {

class MasterControllerTests : public TestSuite {

    Q_OBJECT

public:
    MasterControllerTests();

private slots:
    void initTestCase();
    void tearDownTestCase();
    void init();
    void tearDown();

    void welcomeMsgReturnsCorrectMessage();

private:
    MasterController controller;

};
}}

#endif // MASTERCONTROLLERTESTS_H

