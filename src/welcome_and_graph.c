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
	longBytes = ftell(fp);// longBytes�����ļ����� 
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
			printf(" finished ��\n"); 
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
	bottom_print("�Ǹ�... �밴���������!");
	printf("\n���������"); 
	_wait(4,0); getch(); 
	printf("��һ�ν����Ҫ������������ɶ�ġ�������ʵ�����Ǵ���Ŀ¼�µ�user.data����ļ�\n");
	getch();
	printf("���һ�Ϊ�㴴��һ�� ����\"�Ǹ�����û������\"�Ŀγ� = = \n");
	getch();
	printf("����������һ�����ػ������ݲɼ��� for credit ^v^ \n"); 
	getch();
	bottom_print("��������ɫ���ȶ��ԣ����˵�gui��ƣ��������û����鰡��");
	gotoxy(0,4); 
	getch();
	printf("������˵�����ȣ����޸�\"�Ǹ�����û������\"�����ְ�\n");
	printf("�����ǣ�: ");
	gets(temA->Sub_name); 
	printf("�������أ���������\"%s\"��ѧ�ְѡ�ѧ��credit = ? ",temA->Sub_name);
	scanf("%f",&temA->credit); getchar(); 
	
	printf("\n�����ķǳ���,����"); _wait(4,0); 
	getch(); 
	printf("\n��ô���������Ѿ������һ����Ҫ�Ĳ��������ҽ�Ҫ��Ԧ������ĳ�����.\n");
	getch(); 
	printf("������һ�κò��ð��� y/n ");
	control = getch(); 
	if (control == 'y'){
		system("cls");
		gotoxy(0,9);
		printf("--------------------Read Me--------------------\n");
		printf("| ���һ���� = =                            |\n");
		printf("| ������ʾ����ײ�,�����������������й���   |\n");
		
		printf("| n����һ������������ֻ��һ��%s",temA->Sub_name);
		tem = strlen(temA->Sub_name); 
		while ( 17-tem++ >= 1 ){
			printf(" "); 
		} printf("|\n");
		printf("| p��ǰһ��.... = =                           |\n",temA->Sub_name);
		printf("| ������ 1��2��3 ��Ӣ����ʾ�ѡ�               |\n"); 
		printf("| Esc�뿪����ص��̳�                       |\n");
		printf("-------------------**-----**-------------------\n"); 
		edit_sub_unit(head);
		system("cls");
		printf("\n\n\n\n\n\nţ�ư�\n\n\n hava fun!        ---- sb���Ͽ����ߺ���\n\n");
		getch();  
	} else {
		printf("\n .......\n");
		getch(); 
		printf("�����������ú�ʹ�ð�233");
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
	
	strcpy(head->Sub_name,"\"�Ǹ�����û������\""); 
	head->credit = 0;
	head->us = NULL;

	printf("��һ��ʹ������𣿣���Ҫ�̳�ʲô��ô��y/n ");
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
	printf("1,��ӿ�Ŀ"); 
	gotoxy(36+ini_x,ini_y+funtion+1);
	printf("2,�༭��Ŀ"); 
	
	gotoxy(35+ini_x,ini_y+funtion);
	control = getch(); 
	return control; 
}



