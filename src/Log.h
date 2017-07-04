#ifndef __LOG__H__
#define  __LOG__H__


#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>      
#include <sys/socket.h>
#include <sys/epoll.h>
#include <errno.h>
#include <assert.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>
#include <dirent.h>



#define LOGFILE "./Log"
#define LOGDIR "./Logs"

#define LOG_MAX_SIZE 1024*1024*20          //日志文件最大为20M，超过20M则将日志文件保存在日志文件目录下，重新打开新的日志文件

typedef enum hah{
	QTSS_Err = 0,
	QTSS_NoErr	
}haha;

typedef enum Bool
{
	False = 0,
	True
}Bool;

int CMS_Log_Printf(char *fmt,char *Fullfile,int lines,...);
void GetFileName(char *Fullfile,char *FileName);
int get_file_size(const char *path);
void SaveLogFile(void);


#define CMS_LOG_Printf(fmt,...) \
	CMS_Log_Printf(fmt,__FILE__,__LINE__,##__VA_ARGS__);



#endif
