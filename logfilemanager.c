#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int islineinfile(char* file,char* str){
 FILE *f=fopen(file,"r");
 char* buff=NULL;
 size_t bbytes=0;
 int lcount=0;
 while(getline(&buff,&bbytes,f)!=-1){
  char *tmpholder=malloc(sizeof(char)*(strlen(str)+1));
  strcpy(tmpholder,str);
  strcat(tmpholder,"\n");
  if(strcmp(tmpholder,buff)==0){
   free(tmpholder);
   free(buff);
   fclose(f);
   return lcount;
  }
  free(tmpholder);
  lcount++;
 }
 free(buff);
 fclose(f);
 return -1;
}
void addlinetofile(char* file, char* line){
 char* filetext;
 long size;
 FILE *f=fopen(file,"r");
 fseek(f,0,SEEK_END);
 size=sizeof(char)*(ftell(f));
 rewind(f);
 filetext=malloc(size);
 fread(filetext,sizeof(filetext),size,f);
 fclose(f);
 char* newtext=malloc(size+sizeof(char)*(strlen(line)+1));
 strcpy(newtext,filetext);
 free(filetext);
 strcat(newtext,line);
 strcat(newtext,"\n");
 f=fopen(file,"w+");
 fprintf(f,"%s",newtext);
 fclose(f);
 free(newtext);
 
}
void writetofile(char* file, char* text){
 FILE *f=fopen(file,"w+");
 fprintf(f,"%s",text);
 fclose(f);
}
