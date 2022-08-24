#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<ctype.h>
#include<time.h>
#include "logfilemanager.c"
#include "definitions.h"
#include "launched.c"

char filter[15];
void set_filter(char* str){
 strcpy(filter,str);
}
/* MOVED
char* getprocessnamefromid(char* id){//function to get the name of the process from id

 char *path=malloc(sizeof(char)*(strlen(id)+strlen("/proc/status/")));//allocate the string to hold the path
 strcpy(path,"/proc/");//   /proc/<ps id>/status
 strcat(path,id);
 strcat(path,"/status");//finished creating the path
 FILE *f=fopen(path,"r");//open the file

 free(path);
 if(f==NULL){//check for failure to open process file, the process exited too fast
  char* strbk="<exited>";
  char *retpoint=malloc(sizeof(char)*strlen(strbk));
  strcpy(retpoint,strbk);
  return retpoint;
 }
 fseek(f,6,SEEK_SET);//file starts with "Name: ", we don't want that
 char* line=NULL;
 size_t bytebuff=0;
 getline(&line,&bytebuff,f);//read the first line with the name
 fclose(f);
 line[strlen(line)-1]='\0';//omit \n
 return line;
}*/
void dumptofile(){//dumps all current process names to file
 FILE *f=fopen(FILENAME,"w+");//defined in defenitions
 DIR *dir=opendir("/proc");
 struct dirent *dirinfo;
 if(dir==NULL){ printf("no /proc acccess, terminating"); return;}
 while((dirinfo=readdir(dir))!=NULL){
   char* name=dirinfo->d_name;
   if(isdigit(name[0])){
    char* psnm=getprocessnamefromid(name);
    if(strcmp(name,"<exited>")!=0){//don't save to file if failed to get name
     fprintf(f,"%s\n",psnm);
    }
    free(psnm);
   }
 }
 closedir(dir);
 fclose(f); 
}
void dumpall(){//dumps all the proceses in the terminal
 DIR *dir=opendir("/proc");
 struct dirent *dirinfo;
 if(dir==NULL){ printf("no /proc acccess, terminating"); return;}
 while((dirinfo=readdir(dir))!=NULL){
   char* name=dirinfo->d_name;
   if(isdigit(name[0])){
    char* psnm=getprocessnamefromid(name);
    printf("%s %s\n",name,psnm);
    free(psnm);
   }
 }
 closedir(dir);

}
void listnew(){
 DIR *dir=opendir("/proc");
 struct dirent *dirinfo;
 if(dir==NULL){ printf("no /proc acccess, terminating"); return;}
 while((dirinfo=readdir(dir))!=NULL){
   char* name=dirinfo->d_name;
   if(isdigit(name[0])){
    char* psnm=getprocessnamefromid(name);
    if(islineinfile(FILENAME,psnm)==-1){
     if(!strstr(psnm,filter)){
      printf("%s %s\n",name,psnm);
     }else if(strcmp(filter,"")==0){
      printf("%s %s\n",name,psnm);
     }
    }    
    free(psnm);
   }
 }
 closedir(dir);

}
void clear(){
  FILE *f=fopen(FILENAME,"w+");
  fprintf(f," ");
  fclose(f);
}
void setfilter(){
 printf("dont show process with this name: ");
 scanf("%s",filter);
}
void delay(int milliseconds)//delay function off of the internet
{
    long pause;
    clock_t now,then;
    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}
void loopdat(){
 intake();
 while(1==1){// CTRL-C for now
  delay(1000);//debateable, less delay time allows to catch processes that enter and exit quickly but puts more work on the system
  showNotInList(filter);
 }
 close();
}
//w-write all process to file
//d-dump all processes
//n-list new processes not in file
//c-clear file
//l-show launched processes
//f-set filter
void dumpps(char command){
 switch(command){
  case 'w':
   printf("---written to file ./%s",FILENAME);
   dumpall();
   dumptofile();
   printf("---written to file ./%s",FILENAME);
   break;
  case 'd':
   dumpall();
   break;
  case 'r':
   remove(FILENAME);
   break;
  case 'n':
   listnew();
   break;
  case 'c':
   clear();
   break;
  case 'l':
   loopdat();
   break;
  case 'f':
   setfilter();
   break;
 }
 
}
void psdog(){
 strcpy(filter,"kworker");
 char input=' ';
 while(input!='q'){
  printf("-----------------------------------\n");
  printf(MENU);
  printf("\n$ ");
  input=getchar();
  while(input=='\n'){
   input=getchar();
  }
  getchar();
  dumpps(input);
 }

}

