#include "master-controller-tests.h"

namespace cm {
namespace controllers { // Instance

static MasterControllerTests instance;

MasterControllerTests::MasterControllerTests()
    : TestSuite( "MasterControllerTests" )
{
}

}

namespace controllers { // Scaffolding

void MasterControllerTests::initTestCase()
{
}

void MasterControllerTests::tearDownTestCase()
{
}

void MasterControllerTests::init()
{
}

void MasterControllerTests::tearDown()
{
}

}

namespace controllers { // Tests

void MasterControllerTests::welcomeMsgReturnsCorrectMessage()
{
    QCOMPARE( controller.welcomeMessage(), QString("Welcome to the Client Management system!") );
}

}}
