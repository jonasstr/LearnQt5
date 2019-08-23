#include "contact.h"

using namespace cm::data;

namespace cm {
namespace models {

auto Contact::contactTypeMapper = std::map<int, QString> {
    {Contact::ContactType::UNKNOWN, ""},
    {Contact::ContactType::TELEPHONE, "Telephone"},
    {Contact::ContactType::EMAIL, "Email"},
    {Contact::ContactType::FAX, "Fax"}
};

Contact::Contact(QObject* parent)
    : Entity(parent, "contact") {

    auto enumDecorator = new EnumeratorDecorator(this, "contactType", "Contact Type", 0, contactTypeMapper);
    type = static_cast<EnumeratorDecorator*>(addDataItem(enumDecorator));
    address = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "address", "Address")));
}

Contact::Contact(QObject* parent, const QJsonObject& json)
    : Contact(parent){

    update(json);
}

}}
