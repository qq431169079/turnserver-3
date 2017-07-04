#include "Log.h"


int CMS_Log_Printf(char *fmt,char *Fullfile,int lines,...)
{
//	if (fmt == NULL)
//        return 1;

	if(get_file_size(LOGFILE) > LOG_MAX_SIZE)
		SaveLogFile();	
	char Buff[1024] = {0};
	time_t timevalue;
	struct tm *p;
	FILE * fp = NULL;
	char FileName[32] = {0};
	GetFileName(Fullfile,FileName);
	time(&timevalue);
	p = localtime(&timevalue);
	sprintf(Buff,"%04d-%02d-%02d %02d:%02d:%02d ",(1900+p->tm_year), (1+p->tm_mon),p->tm_mday,p->tm_hour, p->tm_min, p->tm_sec);
	sprintf(Buff+strlen(Buff),"%s|%d INFO ",FileName,lines);
	va_list args; 
	va_start(args, lines);
	int result =  vsprintf(Buff+strlen(Buff),fmt, args);
	va_end(args);
	
 	fp = fopen(LOGFILE,"a+");
	if(fp == NULL)
		return QTSS_Err;
	fprintf(fp,"%s\n",Buff);
	fclose(fp);fp = NULL;
    return result;
}


void SaveLogFile(void)
{
	char NewFileName[64] = {0};
	time_t timevalue;
	struct tm *p;
	time(&timevalue);
	p = localtime(&timevalue);
	sprintf(NewFileName,"%s/Log_%04d%02d%02d%02d%02d%02d",LOGDIR,(1900+p->tm_year), (1+p->tm_mon),p->tm_mday,p->tm_hour, p->tm_min, p->tm_sec);
	
	if(opendir(LOGDIR) == NULL)
    {	
		mkdir(LOGDIR,0777);
    }
	rename(LOGFILE,NewFileName);
}


int get_file_size(const char *path)    
{    
    unsigned long filesize = -1;        
    struct stat statbuff;    
    if(stat(path, &statbuff) < 0){    
        return QTSS_NoErr;    
    }else{    
        filesize = statbuff.st_size;    
    }    
    return filesize;    
}   


void GetFileName(char *Fullfile,char *FileName)
{
	char *p = Fullfile,*q = NULL;
	while((q = strstr(p,"/")) != NULL)
	{
		p = q+1;
	}
	strcpy(FileName,p);
}

