#include "client.h"

Client::Client(int id, const std::string& name, const std::string& email, const std::string& phone_number)
{
    this->id = id;
    this->name = name;
    this->email = email;
    this->phone_number = phone_number;
}

int Client::GetId() const
{
    return id;
}

std::string Client::GetName() const
{
    return name;
}

std::string Client::GetEmail() const
{
    return email;
}

std::string Client::GetPhoneNumber() const
{
    return phone_number;
}

void Client::SetId(int id)
{
    this->id = id;
}

void Client::SetName(const std::string& name)
{
    this->name = name;
}

void Client::SetEmail(const std::string& email)
{
    this->email = email;
}

void Client::SetPhoneNumber(const std::string& number)
{
    this->phone_number = number;
}
