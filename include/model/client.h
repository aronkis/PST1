#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client
{
public:
    Client(int id, const std::string& name, const std::string& email, const std::string& phone_number);

    int GetId() const;
    std::string GetName() const;
    std::string GetEmail() const;
    std::string GetPhoneNumber() const;

    void SetId(int id);
    void SetName(const std::string& name);
    void SetEmail(const std::string& email);
    void SetPhoneNumber(const std::string& number);
    
private:
    int id;
    std::string name;
    std::string email;
    std::string phone_number;

};

#endif // CLIENT_H
