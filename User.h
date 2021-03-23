#pragma once
#include "Namespace.h"

class User {
private:
    inline static string currentUser;
    string login, password;
public:
    User();
    User(string, string);
    static void setCurrentUser(const string&);
    static void getCurrentUser(string&);
    void setLoginAndPassword(const string&, const string&);
    string getLogin();
    string getPassword();
    void enterAccount(vector<User>&); 
    void createUserAccount(vector<User>&);
    void changePassword(vector<User>&, const string&);
    virtual void menuUser(vector<User>&);
    virtual void deleteAccount(vector<User>&, bool&);
    friend bool operator==(const User&, const User&);
};