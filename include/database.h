#include "data_structures.h"
#include <stdbool.h>

#ifndef _DATABASE_H
#define  _DATABASE_H

bool addNormalUser(normalUser record);
bool addJointUser(jointUser record);
bool deleteNormalUser(int ID);
bool deleteJointUser(int ID);
bool modifyNormalUser(normalUser modUser);
bool modifyJointUser(jointUser modUser);
normalUser getNormalUser(int ID);
jointUser getJointUser(int ID);
admin getAdmin(int ID);
bool depositMoney(int accType,int ID,float amt);
bool withdrawMoney(int accType,int ID,float amt);
float getBalance(int accType,int ID);
bool alterPassword(int accType,int ID,char newPwd[10]);
// bool checkNormalUser(normalUser currUser);
// bool checkJointUser(jointUser currUser);
// bool checkAdmin(admin currUser);

#endif