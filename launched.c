#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<stdlib.h>
#include<ctype.h>

struct Node{
 char* name;
 int head;
 struct Node* next;
};//linked list


struct Node* head;


void setmem(){
 head=(struct Node*)malloc(sizeof(struct Node));
 head->head=1;//create the linked list
}
void add(char* str){
 struct Node* next=(struct Node*)malloc(sizeof(struct Node));
 next->name=malloc(sizeof(char)*strlen(str));
 strcpy(next->name,str);
 next->next=head;
 head->head=-1;
 head=next;//add element
}
int gothrough(struct Node* in,char* look){//go through the list to find "look"
 //in=in->next;
 while(in->name!=NULL){
  if(strcmp(in->name,look)==0){
   return 1;
  }
  in=in->next;
 }
 return -1;
}
void close(){
 free(head);
}

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
}
void showNotInList(char* filter){
 DIR *d=opendir("/proc");
 struct dirent *dd;
 char* proc;
 while((dd=readdir(d))!=NULL){
  proc=dd->d_name;
  if(isdigit(proc[0])){
   char* namedisp=getprocessnamefromid(proc);
   if(gothrough(head,namedisp)==-1&&!strstr(namedisp,filter)){
    printf("NEW: %s %s\n",proc,namedisp);
    add(namedisp);
   }
   free(namedisp);
  }
 }
 closedir(d);
}

void intake(){//grab all processes before as refernce to not print them only print new ones
 setmem();
 DIR *d=opendir("/proc");
 struct dirent *dd;
 char* proc;
 while((dd=readdir(d))!=NULL){
  proc=dd->d_name;
  if(isdigit(proc[0])){
    char* namedisp=getprocessnamefromid(proc);
    
    add(namedisp);
    free(namedisp);
    
  }
 } 
 closedir(d);
}


