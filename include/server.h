#include "data_structures.h"

#ifndef _SERVER_H
#define _SERVER_H

bool checkNormalUser(normalUser currUser);
bool checkJointUser(jointUser currUser);
bool checkAdmin(admin currUser);
void serverTask(int nsd);

#endif // !SERVER_H_