#ifndef _CLIENT_H
#define _CLIENT_H

void attemptNormalUserLogin(int sd);
void attemptJointUserLogin(int sd);
void attemptAdminLogin(int sd);
void showMenu(int sd);
void deposit(int sd);
void withdraw(int sd);
void balanceEnquiry(int sd);
void changePassword(int sd);
void viewDetails(int sd);
void addAccount(int sd);
void deleteAccount(int sd);
void modifyAccount(int sd);
void searchAccount(int sd);

#endif // !_CLIENT_H_