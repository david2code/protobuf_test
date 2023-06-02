#include <iostream>
#include <fstream>
#include <string>
#include "addressbook.pb.h"

using namespace std;

void PromptForAddress(tutorial::Person *person) 
{
    cout << "Enter person ID number: ";
    int id;
    cin >> id;
    person->set_id(id);
    cin.ignore(256, '\n');

    cout << "Enter name: ";
    getline(cin, *person->mutable_name());

    cout << "Enter email address (blank for none): ";
    string email;
    getline(cin, email);
    if (!email.empty()) {
        person->set_email(email);
    }

    while(true) {
        cout << "Enter a phone number (or leave blank to finish): ";
        string number;
        getline(cin, number);
        if (number.empty()) {
            break;
        }
        tutorial::Person::PhoneNumber* phone_number = person->add_phones();
        phone_number->set_number(number);

        cout << "Is this a mobile, home, or work phone? ";
        string type;
        getline(cin, type);
        if (type == "mobile") {
            phone_number->set_type(tutorial::Person::MOBILE);
        } else if (type == "home") {
            phone_number->set_type(tutorial::Person::HOME);
        } else if (type == "work") {
            phone_number->set_type(tutorial::Person::WORK);
        } else {
            cout << "Unknonw phone type. Using default." << endl;
        }

    }
}

void ListPeople(const tutorial::AddressBook &address_book)
{
    for (int i = 0; i < address_book.people_size(); i++) {
        const tutorial::Person &person = address_book.people(i);

        cout << "Person ID: " << person.id() << endl;
        cout << " Name: " << person.name() << endl;
        if (person.has_email()) {
            cout << " E-mail address: " << person.email() << endl;
        }

        for (int j = 0; j < person.phones_size(); j++) {
            const tutorial::Person::PhoneNumber &phone_number = person.phones(j);
            switch (phone_number.type()) {
                case tutorial::Person::MOBILE:
                    cout << "   Mobile phone #: ";
                break;
                case tutorial::Person::HOME:
                    cout << "   Home phone #: ";
                break;
                case tutorial::Person::WORK:
                    cout << "   Work phone #: ";
                break;
            }
            cout << phone_number.number() << endl;
        }
    }
}

int main(int argc, char *argv[])
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " ADDRESS BOOK FILE" << endl;
        return -1;
    }

    tutorial::AddressBook address_book;

    {
        fstream input(argv[1], ios::in | ios::binary);
        if (!input) {
            cout << argv[1] << ": File not found. Create a new File." << endl;
        } else if (!address_book.ParseFromIstream(&input)) {
            cerr << "Failed to parse address book." << endl;
            return -1;
        }
    }

    ListPeople(address_book);
    PromptForAddress(address_book.add_people());

    {
        fstream output(argv[1], ios::out | ios::trunc | ios::binary);
        if (!address_book.SerializeToOstream(&output)) {
            cerr << "Failed to write address book." << endl;
            return -1;
        }
    }

    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
