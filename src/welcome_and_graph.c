#include <stdio.h>
#include <windows.h>
#include <string.h>
//#include <sys/stat.h>
//#include <unistd.h>
#include "data_struct.h"
#define ini_y			0
#define ini_x			0
//#define 	SU			sizeof(struct subject_unit)		

extern char user_name[16]; 

void _wait( int i ,char flag){
//	int d = SU;
	if (flag){
		printf("welcome,loading...");
	}
	while ( i-- ){
		printf(".");
		_sleep(200);
	}
}

void _user_create(){
	printf("The first time you enter this software.\n"); 
	printf("input your nanme (less than 16 characters) : ");
	gets(user_name);
}

void _user_file_process(){
	FILE *fp_for_user = NULL;
	fp_for_user = fopen("user.data","r"); 
	if (fp_for_user == NULL){
		_user_create();
		fp_for_user = fopen("user.data","w+");
		fwrite(user_name,1,16,fp_for_user); 
	} else {
		fread(user_name,1,16,fp_for_user); 
	}
	fclose(fp_for_user);
}

int _data_load(struct subject_unit *head){
	int num = 0,num_all = 0;
	long longBytes = 0; 
	char ts_eof = 0; 
	struct subject_unit *temp = NULL; 
//	struct stat fileData; 
	FILE *fp;
	FILE *fp_for_data = NULL;
	
//	if (0 == stat("", &fileData)){
//		printf("file size %u.", fileData.st_size);
//	}	
	
	fp = fopen("sub_unit.data","rb");
	fseek(fp,0,SEEK_SET);
	fseek(fp,0,SEEK_END);
	longBytes = ftell(fp);// longBytes就是文件长度 
	fclose(fp);
	
	printf("sub_unit.size : %4d Bytes\n",longBytes);
	if ( longBytes<37 ){ 	
		return ; 
	}
	
	
	fp_for_data = fopen("sub_unit.data","a+");
	if (fp_for_data == NULL){
		if (feof(fp_for_data))
			return 0 ;
	}

	temp = head;

	while ( 1 ){
		fread(temp->Sub_name,1,32,fp_for_data);
		fread(&temp->credit,1,sizeof(float),fp_for_data);
		temp->us = NULL;
		temp->next = NULL;
		
		ts_eof = '\0'; 
		num_all += fread(&ts_eof,1,sizeof(char),fp_for_data);
		printf("%2d Subject loaded .",num_all);
		_wait(2,0); 
		if (ts_eof == 'U'){
			printf(" finished √\n"); 
		} else if (ts_eof == 'B'){
			printf(" data standing by \n");
			_sleep(500); 
		}
		_sleep(100); 
		
		if (ts_eof == 'U' || ts_eof == 'B'){
			temp->us = (struct user_score *)malloc(sizeof(struct user_score));
			fread( &(temp->us->score) ,1,sizeof(float),fp_for_data ); 
			fread( &(temp->us->BD_GPA),1,sizeof(float),fp_for_data );
			
			if (ts_eof == 'B'){
				
				fclose(fp_for_data);
				break;
			}
		} 
		
		if (ts_eof == 'U' || ts_eof == 'n'){
			temp->next = (struct subject_unit *)malloc(sizeof(struct subject_unit));
			temp = temp->next;
			num = 0 ;
		}
		
	}
}

void _jiaocheng(struct subject_unit *head){
	struct subject_unit *temA = NULL;
	char control = 0; 
	int tem = 0; 
	temA = head; 
	
	_wait(8,0);
	bottom_print("那个... 请按任意键继续!");
	printf("\n这个程序呢"); 
	_wait(4,0); getch(); 
	printf("第一次进入会要求你输入名字啥的。。。（实质上是创建目录下的user.data这个文件\n");
	getch();
	printf("而且会为你创建一个 叫做\"那个，我没有名字\"的课程 = = \n");
	getch();
	printf("讲道理，这是一个本地化的数据采集器 for credit ^v^ \n"); 
	getch();
	bottom_print("（（（出色的稳定性，撩人的gui设计，完美的用户体验啊！");
	gotoxy(0,4); 
	getch();
	printf("话不多说，首先，先修改\"那个，我没有名字\"的名字把\n");
	printf("名字是？: ");
	gets(temA->Sub_name); 
	printf("接下来呢，继续输入\"%s\"的学分把。学分credit = ? ",temA->Sub_name);
	scanf("%f",&temA->credit); getchar(); 
	
	printf("\n你做的非常好,而且"); _wait(4,0); 
	getch(); 
	printf("\n这么看来，你已经完成了一个重要的操作，而且将要驾驭这个糟糕的程序了.\n");
	getch(); 
	printf("再来输一次好不好啊？ y/n ");
	control = getch(); 
	if (control == 'y'){
		system("cls");
		gotoxy(0,9);
		printf("--------------------Read Me--------------------\n");
		printf("| 额，第一次呢 = =                            |\n");
		printf("| 操作提示在最底部,那里有这个版面的所有功能   |\n");
		
		printf("| n是下一个，在这里你只有一个%s",temA->Sub_name);
		tem = strlen(temA->Sub_name); 
		while ( 17-tem++ >= 1 ){
			printf(" "); 
		} printf("|\n");
		printf("| p是前一个.... = =                           |\n",temA->Sub_name);
		printf("| 其他的 1和2和3 看英文提示把。               |\n"); 
		printf("| Esc离开这里，回到教程                       |\n");
		printf("-------------------**-----**-------------------\n"); 
		edit_sub_unit(head);
		system("cls");
		printf("\n\n\n\n\n\n牛逼啊\n\n\n hava fun!        ---- sb智障开发者红莲\n\n");
		getch();  
	} else {
		printf("\n .......\n");
		getch(); 
		printf("不管怎样，好好使用把233");
	}
}

int _file_exist(){
	FILE *fp;
	fp = fopen("sub_unit.data","r");
	
	if (fp == NULL){
		fclose(fp);
		return 0; 	
	} else {
		fclose(fp);
		return 1; 
	}
}
void _subject_unit_data_create(struct subject_unit *head ){
	char control = 0 ; 
	FILE *fp = NULL; 
	fp = fopen("sub_unit.data","w+");
	fclose(fp);
	
	strcpy(head->Sub_name,"\"那个，我没有名字\""); 
	head->credit = 0;
	head->us = NULL;

	printf("第一次使用软件吗？，需要教程什么的么？y/n ");
	control = getch();
	if (control == 'y'){
		system("cls");
		_jiaocheng(head); 
	} else {
		return ; 
	}
}


int init(struct subject_unit *head){
	system("mode con cols=120 lines=30");
	
	printf("welcome to this unnamed software....ver 0.03 -->_-->\n"); 
	
	_user_file_process();
	
	if ( _file_exist() ){
		_data_load(head);
	} else {
		
		printf("create user file ...");
		_subject_unit_data_create(head); 
		_wait(6,0);
		printf("\n"); 
	}

	
	_wait(10,1); /* 200ms*8 */
	system("cls");
	return 0;
}

int gotoxy(int x,int y){
	COORD c;
	c.X=x;
	c.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
	return 0; 
}

void bottom_print(char *ptr){
	gotoxy(0,29);
	printf(ptr);
	gotoxy(0,0);
}

char memu(char funtion){
	char control = '\0'; 
	gotoxy(36+ini_x,ini_y+funtion);
	printf("1,添加科目"); 
	gotoxy(36+ini_x,ini_y+funtion+1);
	printf("2,编辑科目"); 
	
	gotoxy(35+ini_x,ini_y+funtion);
	control = getch(); 
	return control; 
}



