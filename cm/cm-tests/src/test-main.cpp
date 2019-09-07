#include <QtTest/QtTest>
#include <QDebug>

#include "test-suite.h"

using namespace cm;

int main(int argc, char* argv[]) {

    Q_UNUSED(argc);
    Q_UNUSED(argv);

    qDebug() << "Starting test suite...";
    qDebug() << "Accessing tests from" << &TestSuite::testList();
    int testCount = TestSuite::testList().size();
    qDebug() << testCount << (testCount == 1 ? "test detected" : "tests detected");

    int failedTestsCount = 0;
    for (auto* t : TestSuite::testList()) {
        qDebug() << "Executing test" << t->testName;
        QString fileName(t->testName + ".xml");
        int result = QTest::qExec(t, QStringList() << " " << "-o" << fileName << "-xunitxml");
        qDebug() << "=== Test result" << result << "===";

        if (result != 0) {
            failedTestsCount++;
        }
    }
    QString result = failedTestsCount == 0 ? "all tests passed!" : QString::number(failedTestsCount).append("failures detected.");
    qDebug().noquote() << "Test suite complete -" << result;
    return failedTestsCount;
}
