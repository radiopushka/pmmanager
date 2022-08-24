#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void printfiledata(char* path){
 FILE *f=fopen(path,"r");
 char tmp;
 while((tmp=fgetc(f))!=EOF){
  printf("%c",tmp);
 }
 fclose(f);
}
void printfirstline(char* path){
 FILE *f=fopen(path,"r");
 char tmp;
 while(fgetc(f)!='	'){}
 printf("name: ");
 while((tmp=fgetc(f))!='\n'){
  printf("%c",tmp);
 }
 fclose(f);

}
char* filegroup(const char* pred,const char* med, const char* end){
 char *out=malloc(strlen(pred)+strlen(med)+strlen(end)+1); //creates path for the file 
 strcpy(out,pred);
 strcat(out,med);
 strcat(out,end);
 return out;
}
