#pragma once
#include "User.h"

class Admin : public User {
public:
    void createAdminAccount(vector<User>&);
    void menuUser(vector<User>&) override;
    void menuUserControl();
    void viewUsers();
    void addUsers();
    void deleteUsers();
    void deleteAccount(vector<User>&, bool&) override;
    void changeAdmin();
};