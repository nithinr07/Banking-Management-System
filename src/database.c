#include "database.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include "constants.h"

bool addNormalUser(normalUser record){
	int fd=open(NORMALUSER_DB_PATH,O_RDWR,0744);
	bool result;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_END;
	lock.l_start=(-1)*sizeof(normalUser);    //nth record
	lock.l_len=sizeof(normalUser);	             //sizeof(record)
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	normalUser endUser;
	lseek(fd,(-1)*sizeof(normalUser),SEEK_END);  //changing the file pointer to the selected record
	read(fd,&endUser,sizeof(normalUser));
		
	record.userID=endUser.userID+1;
	record.account_no=endUser.account_no+1;
	strcpy(record.status,"ACTIVE");
	
	int j=write(fd,&record,sizeof(normalUser));
	if(j!=0)	result=true;
	else	result=false;
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return result;	
}

bool addJointUser(jointUser record){
	int fd=open(JOINTUSER_DB_PATH,O_RDWR,0744);
	bool result;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_END;
	lock.l_start=(-1)*sizeof(jointUser);    //nth record
	lock.l_len=sizeof(jointUser);	             //sizeof(record)
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	jointUser endUser;
	lseek(fd,(-1)*sizeof(jointUser),SEEK_END);  //changing the file pointer to the selected record
	read(fd,&endUser,sizeof(jointUser));
		
	record.userID=endUser.userID+1;
	record.account_no=endUser.account_no+1;
	strcpy(record.status,"ACTIVE");
	
	int j=write(fd,&record,sizeof(jointUser));
	if(j!=0)	result=true;
	else	result=false;
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return result;	
}

bool deleteNormalUser(int ID){
	int i=ID-1;
	int fd=open(NORMALUSER_DB_PATH,O_RDWR,0744);
	bool result;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(normalUser);    //nth record
	lock.l_len=sizeof(normalUser);	             //sizeof(record)
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	normalUser currUser;
	lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(normalUser));
	
	if(!strcmp(currUser.status,"ACTIVE")){	
		strcpy(currUser.status,"CLOSED");
		currUser.balance=0;
		
		lseek(fd,(-1)*sizeof(normalUser),SEEK_CUR); 
		int j=write(fd,&currUser,sizeof(normalUser));
		if(j!=0)	result=true;
		else		result=false;
	}
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return result;	
}

bool deleteJointUser(int ID){
	int i=ID-1;
	int fd=open(JOINTUSER_DB_PATH,O_RDWR,0744);
	bool result;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(jointUser);    //nth record
	lock.l_len=sizeof(jointUser);	             //sizeof(record)
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	jointUser currUser;
	lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(jointUser));
	
	if(!strcmp(currUser.status,"ACTIVE")){	
		strcpy(currUser.status,"CLOSED");
		currUser.balance=0;
		
		lseek(fd,(-1)*sizeof(jointUser),SEEK_CUR); 
		int j=write(fd,&currUser,sizeof(jointUser));
		if(j!=0)	result=true;
		else		result=false;
	}
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return result;	
}

bool modifyNormalUser(normalUser modUser){
    printf("id mod user = %d\n", modUser.userID);
	int i=modUser.userID-1;
	int fd=open(NORMALUSER_DB_PATH,O_RDWR,0744);
	bool result=false;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(normalUser);    //nth record
	lock.l_len=sizeof(normalUser);	             //sizeof(record)
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	normalUser currUser;
	lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(normalUser));
	
	if(!strcmp(currUser.status,"ACTIVE") && (modUser.account_no==currUser.account_no)){	
		strcpy(modUser.status,"ACTIVE");
		lseek(fd,(-1)*sizeof(normalUser),SEEK_CUR); 
		int j=write(fd,&modUser,sizeof(normalUser));
		if(j!=0)	result=true;
		else		result=false;
	}
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return result;	
}

bool modifyJointUser(jointUser modUser){
	int i=modUser.userID-1;
	int fd=open(JOINTUSER_DB_PATH,O_RDWR,0744);
	bool result=false;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(jointUser);    //nth record
	lock.l_len=sizeof(jointUser);	             //sizeof(record)
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	jointUser currUser;
	lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(jointUser));
	
	if(!strcmp(currUser.status,"ACTIVE")  && (modUser.account_no==currUser.account_no)){	
		strcpy(modUser.status,"ACTIVE");
		lseek(fd,(-1)*sizeof(jointUser),SEEK_CUR); 
		int j=write(fd,&modUser,sizeof(jointUser));
		if(j!=0)	result=true;
		else		result=false;
	}
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return result;	
}

normalUser getNormalUser(int ID){
	int i=ID-1;
	normalUser currUser;
	int fd=open(NORMALUSER_DB_PATH,O_RDONLY,0744);
	
	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(normalUser);    	     //nth record
	lock.l_len=sizeof(normalUser);	             //sizeof(record)
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(normalUser));

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return currUser;
}

jointUser getJointUser(int ID){
	int i=ID-1;
	jointUser currUser;
	int fd=open(JOINTUSER_DB_PATH,O_RDONLY,0744);
	
	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(jointUser);    	     //nth record
	lock.l_len=sizeof(jointUser);	             //sizeof(record)
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(jointUser));

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return currUser;
}

admin getAdmin(int ID){
	int i=ID-1;
	admin currUser;
	int fd=open(ADMIN_DB_PATH,O_RDONLY,0744);
	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(admin);    	     //nth record
	lock.l_len=sizeof(admin);	             //sizeof(record)
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	lseek(fd,(i)*sizeof(admin),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(admin));

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return currUser;
}

bool depositMoney(int accType,int ID,float amt){
	int i=ID-1;
	if(accType==1){
		int fd=open(NORMALUSER_DB_PATH,O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(normalUser);    //nth record
		lock.l_len=sizeof(normalUser);	             //sizeof(record)
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		//getchar();

		normalUser currUser;
		lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&currUser,sizeof(normalUser));
		
		if(!strcmp(currUser.status,"ACTIVE")){
			currUser.balance+=amt;
			lseek(fd,sizeof(normalUser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(normalUser));
			result=true;
		}
		else	result=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;		
	}
	else if(accType==2){
		int fd=open(JOINTUSER_DB_PATH,O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(jointUser);    //nth record
		lock.l_len=sizeof(jointUser);	             //sizeof(record)
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		//getchar();

		jointUser currUser;
		lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&currUser,sizeof(jointUser));
		
		if(!strcmp(currUser.status,"ACTIVE")){
			currUser.balance+=amt;
            getchar();
			lseek(fd,sizeof(jointUser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(jointUser));
			result=true;
		}
		else	result=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;	
	}
	return false;
}

bool withdrawMoney(int accType,int ID,float amt){
	int i=ID-1;
	if(accType==1){
		int fd=open(NORMALUSER_DB_PATH,O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(normalUser);    //nth record
		lock.l_len=sizeof(normalUser);	             //sizeof(record)
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		//getchar();

		normalUser currUser;
		lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&currUser,sizeof(normalUser));
		
		if(!strcmp(currUser.status,"ACTIVE") && currUser.balance>=amt){
			currUser.balance-=amt;
			lseek(fd,sizeof(normalUser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(normalUser));
			result=true;
		}
		else	result=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;	
	}
	else if(accType==2){
		int fd=open(JOINTUSER_DB_PATH,O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(jointUser);    //nth record
		lock.l_len=sizeof(jointUser);	             //sizeof(record)
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		//getchar();

		jointUser currUser;
		lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&currUser,sizeof(jointUser));
		
		if(!strcmp(currUser.status,"ACTIVE") && currUser.balance>=amt){
			currUser.balance-=amt;
			lseek(fd,sizeof(jointUser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(jointUser));
			result=true;
		}
		else	result=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	return false;
}

float getBalance(int accType,int ID){
	int i=ID-1;
	float result;
	if(accType==1){
		int i=ID-1;
		int fd=open(NORMALUSER_DB_PATH,O_RDONLY,0744);
		normalUser temp;
	
		int fl1;
		struct flock lock;
		lock.l_type = F_RDLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(normalUser);    	     //nth record
		lock.l_len=sizeof(normalUser);	             //sizeof(record)
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		//getchar();

		lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&temp,sizeof(normalUser));
		if(!strcmp(temp.status,"ACTIVE"))	result=temp.balance;
		else					result=0;

		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	else if(accType==2){
		int i=ID-1;
		int fd=open(JOINTUSER_DB_PATH,O_RDONLY,0744);
		jointUser temp;
	
		int fl1;
		struct flock lock;
		lock.l_type = F_RDLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(jointUser);    	     //nth record
		lock.l_len=sizeof(jointUser);	             //sizeof(record)
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		//getchar();

		lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&temp,sizeof(jointUser));
		if(!strcmp(temp.status,"ACTIVE"))	result=temp.balance;
		else					result=0;

		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	return 0;
}

bool alterPassword(int accType,int ID,char newPwd[10]){
	int i=ID-1;
	if(accType==1){
		int fd=open(NORMALUSER_DB_PATH,O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(normalUser);    //nth record
		lock.l_len=sizeof(normalUser);	             //sizeof(record)
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		//getchar();

		normalUser currUser;
		lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&currUser,sizeof(normalUser));
		
		if(!strcmp(currUser.status,"ACTIVE")){
			strcpy(currUser.password,newPwd);
			lseek(fd,sizeof(normalUser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(normalUser));
			result=true;
		}
		else	result=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	else if(accType==2){
		int fd=open(JOINTUSER_DB_PATH,O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(jointUser);    //nth record
		lock.l_len=sizeof(jointUser);	             //sizeof(record)
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		//getchar();

		jointUser currUser;
		lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&currUser,sizeof(jointUser));
		
		if(!strcmp(currUser.status,"ACTIVE")){
			strcpy(currUser.password,newPwd);
			lseek(fd,sizeof(jointUser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(jointUser));
			result=true;
		}
		else	result=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	return false;
}