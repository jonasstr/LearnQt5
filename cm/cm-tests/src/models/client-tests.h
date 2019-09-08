#ifndef CLIENTTESTS_H
#define CLIENTTESTS_H

#include "test-suite.h"
#include "models/address.h"
#include "models/appointment.h"
#include "models/contact.h"

#include <QtTest>

namespace cm {
namespace models {

class ClientTests : public TestSuite {

    Q_OBJECT

public:
    ClientTests();

private slots:
    void constructor_parent_setsParentAndDefaultProperties();
    void constructor_parentAndJsonObject_setsParentAndProperties();
    void toJson_defaultProperties_constructsJson();
    void toJson_setProperties_constructsJson();
    void update_jsonObject_updatesProperties();
    void update_emptyJsonObject_updatesPropertiesToDefaults();

private:
    void verifyBillingAddress(const QJsonObject& jsonObject);
    void verifyDefaultBillingAddress(const QJsonObject& jsonObject);
    void verifyBillingAddress(Address* address);
    void verifyDefaultBillingAddress(Address* address);
    void verifySupplyAddress(const QJsonObject& jsonObject);
    void verifyDefaultSupplyAddress(const QJsonObject& jsonObject);
    void verifySupplyAddress(Address* address);
    void verifyDefaultSupplyAddress(Address* address);
    void verifyAppointments(const QJsonObject& jsonObject);
    void verifyDefaultAppointments(const QJsonObject& jsonObject);
    void verifyAppointments(const QList<Appointment*>& appointments);
    void verifyDefaultAppointments(const QList<Appointment*>& appointments);
    void verifyContacts(const QJsonObject& jsonObject);
    void verifyDefaultContacts(const QJsonObject& jsonObject);
    void verifyContacts(const QList<Contact*>& contacts);
    void verifyDefaultContacts(const QList<Contact*>& contacts);

    QByteArray jsonByteArray = R"(
    {
        "reference": "CM0001",
        "name": "Mr Test Testerson",
        "billingAddress": {
            "building": "Billing Building",
            "city": "Billing City",
            "postcode": "Billing Postcode",
            "street": "Billing Street"
        },
        "appointments": [
         {"startAt": "2017-08-20T12:45:00", "endAt": "2017-08-20T13:00:00", "notes": "Test appointment 1"},
         {"startAt": "2017-08-21T10:30:00", "endAt": "2017-08-21T11:30:00", "notes": "Test appointment 2"}
        ],
        "contacts": [
            {"contactType": 2, "address":"email@test.com"},
            {"contactType": 1, "address":"012345678"}
        ],
        "supplyAddress": {
            "building": "Supply Building",
            "city": "Supply City",
            "postcode": "Supply Postcode",
            "street": "Supply Street"
        }
    })";
};

}}

#endif // CLIENTTESTS_H
