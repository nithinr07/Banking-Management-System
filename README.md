# Banking-Management-System
#### Kocherla Nithin Raj - IMT2017511
EG-301P - Operating Systems Lab 
## Objective 

This project aims to model a banking system which supports three types of users - normal, joint and admin. Functionalities such as authentication, depost and withdrawal are provided to users via CLI. A concurrent server is used to facilitate multiple clients at once. The admin can add/destroy/modify users. 

## Functionalities
#### User : 
- Login
- Deposit
- Withdraw
- Balance enquiry
- Password change
- View details
- Exit

#### Admin :
- Add user
- Delete user
- Modify user
- Search user

## Structure
The 'include' directory consists of the header files. The 'src' directory consists of the source code. The code is divided into three files: client, server and database. A seed file is used to initialise the database with three accounts; one of each type. The database file handles read/write calls as per client request, directed from the server. The server file takes in client response and triggers required action. Basically, the client file acts as the 'View', the server file acts as the 'Controller', and the database file acts as the 'Model'.

## Code Execution

#### Building
Run `make` to build binaries. Run `make clean` to clean up

#### Seed Database
Run `make seed` to create database and seed it. Take a note of the output to see the user ids and passwords.

#### Start Server
Run `make server` to start the server

#### Start Client
Run `make client` to start the client
