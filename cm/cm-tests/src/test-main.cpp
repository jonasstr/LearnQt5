#include <QtTest/QtTest>
#include <QDebug>

#include "test-suite.h"

using namespace cm;

int main(int argc, char* argv[]) {

    Q_UNUSED(argc);
    Q_UNUSED(argv);

    qDebug() << "Starting test suite...";
    int testCount = TestSuite::testList().size();
    QString testCountString = testCount == 1 ? " test class found." : " test classes found.";
    qDebug().nospace().noquote() << "Accessing tests from " << &TestSuite::testList() << ": " << testCount << testCountString;

    QDir testDir(".");
    testDir.mkdir("tests/");
    int failedTestsCount = 0;
    for (auto* t : TestSuite::testList()) {
        QString testFileName("tests/" + t->testName + ".xml");
        int result = QTest::qExec(t, QStringList() << " " << "-o" << testFileName << "-xunitxml");

        QString resultString;
        if (result == 0) {
            // Append check mark for successful test
            resultString = QChar(0x2713);
        } else {
            for (int i = 0; i < result; i++) {
                // Append X characters for each failed test
                resultString.append(QChar(0x2717));
            }
        }
        qDebug().noquote().nospace() << "- " << t->testName << ": " << resultString;
        failedTestsCount += result;
    }
    QString failedResult = failedTestsCount == 1 ? "1 TEST FAILED" : (QString::number(failedTestsCount).append(" TESTS FAILED"));
    QString result = failedTestsCount == 0 ? "ALL TESTS PASSED!" : failedResult;
    qDebug().noquote() << "Test suite complete -" << result;
    qDebug().noquote() << "Saving test results to" << testDir.absoluteFilePath("tests");
    return failedTestsCount;
}
