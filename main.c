#include<stdio.h>
#include<dirent.h>
#include<ctype.h>
#include "filer.c"
#include "psaccess.c"
#include "definitions.h"

int main(int argn,char** args){
        set_filter("kworker");
        if(argn>1){
         if(strcmp(args[1],"interactive")==0){
          psdog();
          return 0;
         }
         if(strcmp(args[1],"watchdog")==0){
          if(argn==3){
            set_filter(args[2]);
          }
          dumpps('l');
          return 0;
         }
         if(strcmp(args[1],"h")==0){
          printf("%s\n",HELP);
          return 0;
         }
        }
	if(argn==2){
         char* pathtocmd=filegroup("/proc/",args[1],"/status");
         printfiledata(pathtocmd);
         free(pathtocmd);
         return 0;
        }
	struct dirent *dirinfo;
	DIR *dir=opendir("/proc");
        if(dir==NULL){ printf("no /proc acccess, terminating"); return 0;}
	while((dirinfo=readdir(dir))!=NULL){
         char* name=dirinfo->d_name;
	  if(isdigit(name[0])){
            char* pathtocmd=filegroup("/proc/",name,"/cmdline");
	    char* pathtostat=filegroup("/proc/",name,"/status");          
            printf("id: %s | ",name);
	    printfirstline(pathtostat);
	    free(pathtostat);
	    printf(" | launch command: ");
            printfiledata(pathtocmd);
            free(pathtocmd);
            printf("\n");
            //printf("type pmmanager h for help option \n");
	  }
          //printf("type pmmanager h for help option \n");
         //free(name);
        }
        printf("type pmmanager h for help option \n");
        closedir(dir);
        return 0;

}
