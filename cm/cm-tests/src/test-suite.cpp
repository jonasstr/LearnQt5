#include "test-suite.h"

#include <QDebug>

namespace cm {

TestSuite::TestSuite(const QString& testName)
    : QObject(), testName(testName) {

    //qDebug() << "Creating test" << testName;
    testList().push_back(this);
    int testCount = testList().size();
}

TestSuite::~TestSuite() {
    //qDebug() << "Destroying test" << testName;
}

std::vector<TestSuite*>& TestSuite::testList() {
    static std::vector<TestSuite*> instance = std::vector<TestSuite*>();
    return instance;
}
}
