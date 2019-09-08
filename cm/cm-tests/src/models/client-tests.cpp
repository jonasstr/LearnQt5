#include "client-tests.h"

#include "models/client.h"

namespace cm {
namespace models {

static ClientTests instance;

ClientTests::ClientTests()
    : TestSuite("ClientTests") {}

void ClientTests::constructor_parent_setsParentAndDefaultProperties() {

    Client client(this);
    QCOMPARE(client.parent(), this);
    QCOMPARE(client.reference->value(), QString(""));
    QCOMPARE(client.name->value(), QString(""));

    verifyDefaultBillingAddress(client.billingAddress);
    verifyDefaultSupplyAddress(client.supplyAddress);
    verifyDefaultAppointments(client.appointments->derivedEntities());
    verifyDefaultContacts(client.contacts->derivedEntities());
}

void ClientTests::constructor_parentAndJsonObject_setsParentAndProperties() {

    Client client(this, QJsonDocument::fromJson(jsonByteArray).object());
    QVERIFY(client.reference != nullptr);
    QVERIFY(client.name != nullptr);
    QCOMPARE(client.parent(), this);
    QCOMPARE(client.reference->value(), QString("CM0001"));
    QCOMPARE(client.name->value(), QString("Mr Test Testerson"));
    //
    verifyBillingAddress(client.billingAddress);
    verifySupplyAddress(client.supplyAddress);
    QVERIFY(client.appointments != nullptr);
    verifyAppointments(client.appointments->derivedEntities());
    //verifyContacts(client.contacts->derivedEntities());*/
}

void ClientTests::toJson_defaultProperties_constructsJson() {

    Client client(this);
    QJsonDocument jsonDoc(client.toJson());
    QVERIFY(jsonDoc.isObject());
    QJsonObject jsonObject = jsonDoc.object();
    QVERIFY(jsonObject.contains("reference"));
    QCOMPARE(jsonObject.value("reference").toString(), QString(""));
    QVERIFY(jsonObject.contains("name"));
    QCOMPARE(jsonObject.value("name").toString(), QString(""));

    verifyDefaultBillingAddress(client.billingAddress);
    verifyDefaultSupplyAddress(client.supplyAddress);
    verifyDefaultAppointments(client.appointments->derivedEntities());
    verifyDefaultContacts(client.contacts->derivedEntities());
}

void ClientTests::toJson_setProperties_constructsJson() {

    Client client(this, QJsonDocument::fromJson(jsonByteArray).object());
    QCOMPARE(client.reference->value(), QString("CM0001"));
    QCOMPARE(client.name->value(), QString("Mr Test Testerson"));

    verifyBillingAddress(client.billingAddress);
    verifySupplyAddress(client.supplyAddress);
    verifyAppointments(client.appointments->derivedEntities());
    verifyContacts(client.contacts->derivedEntities());

    QJsonDocument jsonDoc(client.toJson());
    QVERIFY(jsonDoc.isObject());
    QJsonObject jsonObject = jsonDoc.object();
    QVERIFY(jsonObject.contains("reference"));
    QCOMPARE(jsonObject.value("reference").toString(), QString("CM0001"));
    QVERIFY(jsonObject.contains("name"));
    QCOMPARE(jsonObject.value("name").toString(), QString("Mr Test Testerson"));

    verifyBillingAddress(client.billingAddress);
    verifySupplyAddress(client.supplyAddress);
    verifyAppointments(client.appointments->derivedEntities());
    verifyContacts(client.contacts->derivedEntities());
}

void ClientTests::update_jsonObject_updatesProperties() {
    Client testClient(this);

    testClient.update(QJsonDocument::fromJson(jsonByteArray).object());

    QCOMPARE(testClient.reference->value(), QString("CM0001"));
    QCOMPARE(testClient.name->value(), QString("Mr Test Testerson"));

    verifyBillingAddress(testClient.billingAddress);
    verifySupplyAddress(testClient.supplyAddress);
    verifyAppointments(testClient.appointments->derivedEntities());
    verifyContacts(testClient.contacts->derivedEntities());
}

void ClientTests::update_emptyJsonObject_updatesPropertiesToDefaults() {
    Client testClient(this, QJsonDocument::fromJson(jsonByteArray).object());

    QCOMPARE(testClient.reference->value(), QString("CM0001"));
    QCOMPARE(testClient.name->value(), QString("Mr Test Testerson"));

    verifyBillingAddress(testClient.billingAddress);
    verifySupplyAddress(testClient.supplyAddress);
    verifyAppointments(testClient.appointments->derivedEntities());
    verifyContacts(testClient.contacts->derivedEntities());

    testClient.update(QJsonObject());

    QCOMPARE(testClient.reference->value(), QString(""));
    QCOMPARE(testClient.name->value(), QString(""));

    verifyDefaultBillingAddress(testClient.billingAddress);
    verifyDefaultSupplyAddress(testClient.supplyAddress);
    verifyDefaultAppointments(testClient.appointments->derivedEntities());
    verifyDefaultContacts(testClient.contacts->derivedEntities());
}

void ClientTests::verifyDefaultBillingAddress(const QJsonObject& jsonObject) {
    QVERIFY(jsonObject.contains("billingAddress"));
    QJsonObject billingAddress = jsonObject.value("billingAddress").toObject();
    QVERIFY(billingAddress.contains("building"));
    QCOMPARE(billingAddress.value("building").toString(), QString(""));
    QVERIFY(billingAddress.contains("street"));
    QCOMPARE(billingAddress.value("street").toString(), QString(""));
    QVERIFY(billingAddress.contains("city"));
    QCOMPARE(billingAddress.value("city").toString(), QString(""));
    QVERIFY(billingAddress.contains("postcode"));
    QCOMPARE(billingAddress.value("postcode").toString(), QString(""));
}

void ClientTests::verifyBillingAddress(Address* address) {
    QVERIFY(address != nullptr);
    QCOMPARE(address->building->value(), QString("Billing Building"));
    QCOMPARE(address->street->value(), QString("Billing Street"));
    QCOMPARE(address->city->value(), QString("Billing City"));
    QCOMPARE(address->postcode->value(), QString("Billing Postcode"));
}

void ClientTests::verifyDefaultBillingAddress(Address* address) {
    QVERIFY(address != nullptr);
    QCOMPARE(address->building->value(), QString(""));
    QCOMPARE(address->street->value(), QString(""));
    QCOMPARE(address->city->value(), QString(""));
    QCOMPARE(address->postcode->value(), QString(""));
}

void ClientTests::verifySupplyAddress(const QJsonObject& jsonObject) {
    QVERIFY(jsonObject.contains("supplyAddress"));
    QJsonObject billingAddress = jsonObject.value("supplyAddress").toObject();
    QVERIFY(billingAddress.contains("building"));
    QCOMPARE(billingAddress.value("building").toString(), QString("Supply Building"));
    QVERIFY(billingAddress.contains("street"));
    QCOMPARE(billingAddress.value("street").toString(), QString("Supply Street"));
    QVERIFY(billingAddress.contains("city"));
    QCOMPARE(billingAddress.value("city").toString(), QString("Supply City"));
    QVERIFY(billingAddress.contains("postcode"));
    QCOMPARE(billingAddress.value("postcode").toString(), QString("Supply Postcode"));
}

void ClientTests::verifyDefaultSupplyAddress(const QJsonObject& jsonObject) {
    QVERIFY(jsonObject.contains("supplyAddress"));
    QJsonObject billingAddress = jsonObject.value("supplyAddress").toObject();
    QVERIFY(billingAddress.contains("building"));
    QCOMPARE(billingAddress.value("building").toString(), QString(""));
    QVERIFY(billingAddress.contains("street"));
    QCOMPARE(billingAddress.value("street").toString(), QString(""));
    QVERIFY(billingAddress.contains("city"));
    QCOMPARE(billingAddress.value("city").toString(), QString(""));
    QVERIFY(billingAddress.contains("postcode"));
    QCOMPARE(billingAddress.value("postcode").toString(), QString(""));
}

void ClientTests::verifySupplyAddress(Address* address) {
    QVERIFY(address != nullptr);
    QCOMPARE(address->building->value(), QString("Supply Building"));
    QCOMPARE(address->street->value(), QString("Supply Street"));
    QCOMPARE(address->city->value(), QString("Supply City"));
    QCOMPARE(address->postcode->value(), QString("Supply Postcode"));
}

void ClientTests::verifyDefaultSupplyAddress(Address* address) {
    QVERIFY(address != nullptr);
    QCOMPARE(address->building->value(), QString(""));
    QCOMPARE(address->street->value(), QString(""));
    QCOMPARE(address->city->value(), QString(""));
    QCOMPARE(address->postcode->value(), QString(""));
}

void ClientTests::verifyAppointments(const QJsonObject& jsonObject) {
    QVERIFY(jsonObject.contains("appointments"));
    QJsonArray appointments = jsonObject.value("appointments").toArray();
    QCOMPARE(appointments.size(), 2);
    QVERIFY(appointments.at(0).isObject());
    QVERIFY(appointments.at(1).isObject());

    QJsonObject appointment1 = (appointments.at(0).toObject());
    QVERIFY(appointment1.contains("startAt"));
    QCOMPARE(appointment1.value("startAt").toString(), QString("2017-08-20T12:45:00"));
    QVERIFY(appointment1.contains("endAt"));
    QCOMPARE(appointment1.value("endAt").toString(), QString("2017-08-20T13:00:00"));
    QVERIFY(appointment1.contains("notes"));
    QCOMPARE(appointment1.value("notes").toString(), QString("Test appointment 1"));

    QJsonObject appointment2 = (appointments.at(1).toObject());
    QVERIFY(appointment2.contains("startAt"));
    QCOMPARE(appointment2.value("startAt").toString(), QString("2017-08-21T10:30:00"));
    QVERIFY(appointment2.contains("endAt"));
    QCOMPARE(appointment2.value("endAt").toString(), QString("2017-08-21T11:30:00"));
    QVERIFY(appointment2.contains("notes"));
    QCOMPARE(appointment2.value("notes").toString(), QString("Test appointment 2"));
}

void ClientTests::verifyDefaultAppointments(const QJsonObject& jsonObject) {
    QVERIFY(jsonObject.contains("appointments"));
    QJsonArray appointments = jsonObject.value("appointments").toArray();
    QCOMPARE(appointments.size(), 0);
}

void ClientTests::verifyAppointments(const QList<Appointment*>& appointments) {
    QCOMPARE(appointments.size(), 2);
    QVERIFY(appointments.at(0)->startAt != nullptr);
    QVERIFY(!appointments.at(0)->notes->value().isNull());
    qDebug() << appointments.at(0)->notes->value();

    QCOMPARE(appointments.at(0)->startAt->value(), QDateTime(QDate(2017, 8, 20), QTime(12, 45)));
    QCOMPARE(appointments.at(0)->endAt->value(), QDateTime(QDate(2017, 8, 20), QTime(13, 0)));
    QCOMPARE(appointments.at(0)->notes->value(), QString("Test appointment 1"));
    QCOMPARE(appointments.at(1)->startAt->value(), QDateTime(QDate(2017, 8, 21), QTime(10, 30)));
    QCOMPARE(appointments.at(1)->endAt->value(),QDateTime(QDate(2017, 8, 21), QTime(11, 30)));
    QCOMPARE(appointments.at(1)->notes->value(), QString("Test appointment 2"));
}

void ClientTests::verifyDefaultAppointments(const QList<Appointment*>& appointments) {
    QCOMPARE(appointments.size(), 0);
}

void ClientTests::verifyContacts(const QJsonObject& jsonObject) {
    QVERIFY(jsonObject.contains("contacts"));
    QJsonArray contacts = jsonObject.value("contacts").toArray();

    QCOMPARE(contacts.size(), 2);
    QVERIFY(contacts.at(0).isObject());
    QVERIFY(contacts.at(1).isObject());

    QJsonObject contact1 = (contacts.at(0).toObject());
    QVERIFY(contact1.contains("address"));
    QCOMPARE(contact1.value("address").toString(), QString("email@test.com"));
    QVERIFY(contact1.contains("contactType"));
    QCOMPARE(contact1.value("contactType").toInt(), static_cast<int>(Contact::ContactType::EMAIL));

    QJsonObject contact2 = (contacts.at(1).toObject());
    QVERIFY(contact2.contains("address"));
    QCOMPARE(contact2.value("address").toString(), QString("012345678"));
    QVERIFY(contact2.contains("contactType"));
    QCOMPARE(contact2.value("contactType").toInt(), static_cast<int>(Contact::ContactType::TELEPHONE));
}

void ClientTests::verifyDefaultContacts(const QJsonObject& jsonObject) {
    QVERIFY(jsonObject.contains("contacts"));
    QJsonArray contacts = jsonObject.value("contacts").toArray();
    QCOMPARE(contacts.size(), 0);
}

void ClientTests::verifyContacts(const QList<Contact*>& contacts) {
    QCOMPARE(contacts.size(), 2);
    QCOMPARE(contacts.size(), 2);
    QCOMPARE(contacts.at(0)->address->value(), QString("email@test.com"));
    QCOMPARE(contacts.at(0)->type->value(), static_cast<int>(Contact::ContactType::EMAIL));
    QCOMPARE(contacts.at(1)->address->value(), QString("012345678"));
    QCOMPARE(contacts.at(1)->type->value(), static_cast<int>(Contact::ContactType::TELEPHONE));
}

void ClientTests::verifyDefaultContacts(const QList<Contact*>& contacts) {
    QCOMPARE(contacts.size(), 0);
}

}}
