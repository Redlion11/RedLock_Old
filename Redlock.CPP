/*******************************************************************************************
*Developed by: Redlion
*
*For Uset It:-
*1. Copy Build Exe to anywhere in pc.
*2. If it run first time in directory then enter initilization password.
*3. After enter password it will open directory.
*4. copy data in that directory what you want to keep secret.
*5. After copy just enter any key on console.
*
********************************************************************************************/
#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<time.h>

#define DNAME "red"
using namespace std;

void block();
void unblock();

int main(){
const int ssize=30;
char str[ssize],tmp[ssize];;
char chk[20],*s1,*s2;
struct dirent *de;
int p;
FILE *fp;
system("icacls .\\red /grant Everyone:(D,RD) /Q /T");
DIR *dr = opendir(".");
s2=chk;

if (dr == NULL)
  {
   cout<<"Could not open current directory";
   return 0;
  }

 while ((de = readdir(dr)) != NULL){
 int st=strcmp(de->d_name,DNAME);
 if(st==0){
  system("icacls red /grant Everyone:(D,RD) /Q /T");
 // chdir("red");
  if((fp=fopen("red\\redx.dat","r"))==NULL)
	{
    if((fp=fopen("red\\redx.dat","w"))!=NULL)
        {
            cout<<"Enter Your Password..#!";
            cin>>str;
            if(strlen(str)>4 && strlen(str)<15){
            fputs(str,fp);
            }
            else{
            cout<<"password lenth must be in between 5 to 15 character long."<<endl;
            fclose(fp);
            system("del red\\redx.dat");
            getch();
            exit(0);
            }
            fclose(fp);
        }
        system("attrib +s +h red\\redx.dat");
        block();
        cout<<"password creation done"<<endl;
	}
  goto done;
    }
 else{
    int stat=mkdir(DNAME);
    if(!stat){
        system("attrib +s +h red");
        if((fp=fopen("red\\redx.dat","w"))!=NULL)
        {
            cout<<"Enter Your Password..#!";
            cin>>str;

            if(strlen(str)>4 && strlen(str)<15){
            fputs(str,fp);
            }
            else{
            cout<<"password lenth must be in between 5 to 15 character long."<<endl;
            fclose(fp);
            system("del red\\redx.dat");
            getch();
            exit(0);
            }
  //        strclr(str);
            fclose(fp);
        }
        system("attrib +s +h red\\redx.dat");
        block();
        cout<<"directory creation done"<<endl;
    }
 }
 }
closedir(dr);
done:
do{
system("cls");
cout<<"Enter Password:-> (For exit enter bye)";
cin>>chk;
system("icacls red\\redx.dat /grant Everyone:(D,DE) /Q"); //for access file
system("icacls red\\redx.dat /grant Administrators:(D,DE) /Q");
unblock();

  if((fp=fopen("red\\redx.dat","r"))!=NULL)
	{
	    fseek(fp,SEEK_SET,0);
	    fread(tmp,ssize,ssize,fp);
	    //fgets(tmp,strlen(tmp)+1,fp);
	    s1=tmp;
	    p=strcmp(tmp,s2);
        if(p==0){
            system("start red");
            fclose(fp);
            system("icacls red\\redx.dat /deny Administrators:(D,DE) /Q");
            system("icacls red\\redx.dat /deny Everyone:(D,DE) /Q");
            system("cls");
            cout<<"Plese Enter After Completion...#!"<<endl;
            getch();
            block();
            exit(0);
        }
        else{
            cout<<"Try again..."<<endl;
            fclose(fp);
            //system("cls");
        }
    }
fclose(fp);
}while(strcmpi(chk,"bye"));
block();
fclose(fp);
return 0;
}

void block(){
        system("icacls red\\redx.dat /deny Administrators:(D,DE) /Q");
        system("icacls red\\redx.dat /deny Everyone:(D,DE) /Q");
        system("icacls .\\red\\* /deny Everyone:(D,RD) /Q /T");
        system("icacls .\\red\\* /deny Everyone:(D,DE) /Q /T");
        system("icacls .\\red\\ /deny Everyone:(D,RD) /Q /T");
        system("attrib +s +h .\\red\\*");
        system("cls");
}


void unblock(){
        system("icacls * /grant Everyone:(D,RD) /Q");
        system("icacls .\\red\\* /grant Everyone:(D,RD) /Q /T");
        system("icacls .\\red\\* /grant Everyone:(D,DE) /Q /T");
        system("icacls .\\red\\ /grant Everyone:(D,RD) /Q /T");
        system("attrib -s -h .\\red\\*");
        system("attrib +s +h .\\red\\redx.dat");
        system("cls");

}

