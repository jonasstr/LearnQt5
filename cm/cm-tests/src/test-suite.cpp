#include "test-suite.h"

#include <QDebug>

namespace cm {

TestSuite::TestSuite(const QString& testName)
    : QObject(), testName(testName) {

    qDebug() << "Creating test" << testName;
    testList().push_back(this);
    int testCount = testList().size();
    QString testsRecorded = "" ;
    qDebug() << testCount << (testCount == 1 ? "test class found" : "test classes found");
}

TestSuite::~TestSuite() {
    qDebug() << "Destroying test...";
}

std::vector<TestSuite*>& TestSuite::testList() {
    static std::vector<TestSuite*> instance = std::vector<TestSuite*>();
    return instance;
}
}
