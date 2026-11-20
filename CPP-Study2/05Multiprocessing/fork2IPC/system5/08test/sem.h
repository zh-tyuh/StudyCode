#ifndef _SEM_H
#define _SEM_H

//创建信号量集并进行初始化：semcouunt表示要创建的信号量集中信号灯的个数，
int create_sem(int semcount);

//申请资源操作，semno表示要申请资源的信号量编号
int P(int semid,int semno);

//释放操作，semno表示要释放资源的信号量编号
int V(int semid,int semno);

//删除信号量集
int delete_sem(int semid);

#endif