#include <stdio.h>
#include <string.h>
#include "data_struct.h"

extern user_name[32];



float _BDGPA_calc(float score){
	if (score >= 90){
		return 4.0f; 
	} else if (score >= 85){
		return 3.7f; 
	} else if (score >= 82){
		return 3.3f;
	} else if (score >= 78){
		return 3.0f; 
	} else if (score >= 75){
		return 2.7f; 
	} else if (score >= 71){
		return 2.3f;
	} else if (score >= 66){
		return 2.0f; 
	} else if (score >= 62){
		return 1.7f;
	} else if (score >= 60){
		return 1.3f; 
	} else if (score < 60){
		return 0; 
	}
}

void input_user_score(struct subject_unit *head) {
	struct subject_unit *temA = NULL;
	float test;
	char temp[32];
	temA = head;
	
	bottom_print("成绩输入-1可以跳过单项成绩录入，输入-2以输入优秀，良好什么的 优秀:A,良好:B 后面的不清楚叫什么暂且保留,挂科请输入D = =");

	
//	print_list(head,1);

	while (1) {
		if (*temA->Sub_name == NULL){
			if (temA->next!=NULL){
				temA = temA->next;
			}
			continue; 
		}
		printf("....课程名 ：%s 成绩是？",temA->Sub_name);
		scanf("%f",&test);
		getchar();
		if ( (int)test == -1 ) {
			if (temA->us != NULL)
				printf("%s之前的成绩为%.1f\n\n",temA->Sub_name,(temA->us)->score);
			else 
				printf("%s从未给%s记录过程序！(您想找bug么233?? \n\n",user_name,temA->Sub_name);
		} else {
			temA->us = (struct user_score *)malloc(sizeof(struct user_score));
			(temA->us)->score = test;
			(temA->us)->BD_GPA = _BDGPA_calc(test);

			if (  (int)test == -2 ){							/* 数据还需要斟酌的地方 */
				printf("那个,请输入A、B或者D : ");
				gets(temp); 
				if ( *temp == 'A'){
					(temA->us)->score = 101; 
					(temA->us)->BD_GPA = 4.0f; 
				} else if ( *temp == 'B' ){
					(temA->us)->score = 102;
					(temA->us)->BD_GPA = 3.3f;					// 3.3??? 3.0???
				} else if ( *temp == 'C' ){
					(temA->us)->score = 103;
					(temA->us)->BD_GPA = 2.0f;	
				} else if ( *temp == 'D' ){
					(temA->us)->score = 104;
					(temA->us)->BD_GPA = 1.3f;
				}
			}
		}
		if (temA->next != NULL){
			temA = temA->next;
		} else break; 
	}
	system("pause");
	system("cls");
}

void _print(char n){
	while (--n){
		putchar(' ');
	}
}
void output_user_score(struct subject_unit *head){
	char c = 0; 
	struct subject_unit *temA = NULL;
	temA = head; 
	
	bottom_print("press 'a' to print all , any press to print next");
	printf("    ★★★  %s的七天七杀  ★★★\n",user_name);
	printf("科目名称               成绩\t单项绩点\n"); 
	
	if (temA->us == NULL){
		c = -1; 
	}
	while ((c != -1)) {
		if (temA->us != NULL){
			printf("%s",temA->Sub_name);
			_print( 24 - strlen(temA->Sub_name)); 
			if ( 0 < (temA->us)->score &&(temA->us)->score <= 100 ){
				printf("%.1f     %.1f\n",(temA->us)->score,(temA->us)->BD_GPA);
			} else {
				printf("%c        %.1f\n",(int)((temA->us)->score) - 100 + 'A'-1, (temA->us)->BD_GPA);
			}
		}
		else 
			goto s;
		if (c != 'a'){
			c = getch();
		}
		if (c == 'a'){
			_sleep(200); 
		}

s: 
	
		if ((temA->next != NULL)){
			temA = temA->next;
			
			
		} else break; 
	}
	printf("...没有了！\n");
	getch();
	system("cls");
}

void new_sub_unit(struct subject_unit *head){
	char con = 'y'; 
	struct subject_unit *temA;
	
	temA = head;
	while (temA->next != NULL) {	
		temA = temA->next;
	}
	
	while (con == 'y'){
		temA->next = (struct subject_unit *)malloc(sizeof(struct subject_unit));
		temA = temA->next; 
		printf("新的课程名？:");
		gets(temA->Sub_name); 
		printf("课程%s的学分呢？:",temA->Sub_name);
		scanf("%f",&temA->credit); 
		getchar(); 
		temA->next = NULL; 
		temA->us = NULL;
		
		printf("继续吗？y/n\n");
		con = getch(); 
	}
	system("cls");
}
int _len_of_list(struct subject_unit *head,struct subject_unit *temA){
	int number = 1; 
	struct subject_unit *temB; 
	
	temB = head;
	if (temB->next == NULL || temA == head){
		return 1;
	}
	
	while ( 1 ){
		if (temB == temA){
			break;
		} else {
			temB = temB->next;
			number++; 
		}
	}
	return number; 
}

void edit_sub_unit( struct subject_unit *head , struct subject_unit **head_path ){
	struct subject_unit *temA = NULL; 
	struct subject_unit *temB = NULL; 
	struct subject_unit *temC = NULL;
	int number = 1 ;
	char control = '\0';
	
	
	temA = head;
	
	while ( 1 ){
		number = _len_of_list(head,temA);
		
		bottom_print("n,next one    p,previou one    1,edit name    2,edit credit    3,delete it!!!!    Esc,exit");
		printf("233,this is , NO.%d subject unit\n",number);
		printf("    called : %s   \n",temA->Sub_name);
		printf("    credit : %.1f \n",temA->credit  ); 
		control = 0 ; 
		control = getch();
		gotoxy(0,0);
		
		if (control == 'p' && temA != head ){
			system("cls");
			temB = head; 
			while ( 1 ){
				if (temB->next == temA) 
					break; 
				else 
					temB = temB->next;		
			}
			temA = temB; 
		} else if (control == 'n' && temA->next != NULL){
			system("cls");
			temA = temA->next;
		} else if (control == '1'){
			gotoxy(0,3); 
			printf("new subject name ?? \n");
			gets(temA->Sub_name);
			system("cls");
		} else if (control == '2'){
			gotoxy(0,3);
			printf("学分credit = ? ");
			scanf("%f",&temA->credit);
			getchar(); 
			system("cls");
		} else if (control == 27){
//			print_list(head,0);
//			print_list(temA,0); 
			return; 
		} else if (control == '3'){
			if (temA == head){	
				if ( temA->next == NULL ){
					temA->credit = 0 ;
					*temA->Sub_name = NULL;
					if (temA->us != NULL){
						free(temA->us);
					}
					temA->us = NULL; 
					continue;
				}
				
				/******  指向结构的指针,作用域的问题。这里的head不能传递到函数外部  ******/
				temB = head;
				temA = temA->next;
				head = head->next;
				*head_path = temA; 
				if (temB->us != NULL) 
					free(temB->us);
				free(temB);
				/******  指向结构的指针,作用域的问题。这里的head不能传递到函数外部  ******/
			 
				
			} else {			// temA != head; temA 不是 head 的情况集  
				temB = head;
				if (temA->next == NULL){//temA != head && temA->next == NULL 末尾 
					while ( 1 ){
						if (temB->next == temA) 
							break; 
						else 
							temB = temB->next;		
					}
					temC = temA; 
					temA = temB; 
					temB->next = NULL;
					if (temC->us != NULL)
						free(temC->us);
					free(temC);
				} else {		//temA != head && temA->next != NULL  在中间
					temB = head;
					while ( 1 ){
						if (temB->next == temA) 
							break; 
						else 
							temB = temB->next;	
					}
					
					temB->next = temA->next;
					
					if (temA->us != NULL){
						free(temA->us);
					}
					free(temA);
					temA = temB ;  // 不然闪退gj 
				}
			}
			system("cls");
		}
	}
	system("cls");
}


void output_GPA_all(struct subject_unit * head){
	double up = 0,total_credit = 0;  
	struct subject_unit *temA; 
	temA = head; 
	
	system("cls"); 
	
	bottom_print("那个..... 绩点怎么算的啊... 那些实验课按优秀良好及格差评分的又是怎么计算的呢？");
	while (1){
		total_credit = total_credit + temA->credit;
		
		up = up + temA->credit * (temA->us)->BD_GPA;
		if (temA->next == NULL){
			break;
		} else {
			temA = temA->next; 
		}
	}
	printf("(分段绩点法) 绩点 : %lf\n",up / total_credit);
	printf("那个,请按任意键继续!!");
	getch();
	system("cls");
}

void data_stored(struct subject_unit *head){
	struct subject_unit *temA; 
	char us = 'U',next_subject_unit = 'n',B_eof = 'B'; 
	FILE *fp = NULL; 
	
	temA = head;
	fp = fopen("sub_unit.data","w+");
	
	while ( fp != NULL ) {
		fwrite(temA->Sub_name,1,32,fp); 
		fwrite(&temA->credit,1,sizeof(float),fp); 
		
		if (temA->us != NULL){
			if (temA->next != NULL){
				fwrite(&us,1,1,fp);
			} else {
				fwrite(&B_eof,1,1,fp);
			}
			fwrite(&(temA->us->score) ,1,sizeof(float),fp); 
			fwrite(&(temA->us->BD_GPA),1,sizeof(float),fp); 
		} else {
			fwrite(&next_subject_unit,1,1,fp); 
		}
		
		if (temA->next == NULL){
			
			break;
		} else {
			temA = temA->next; 
		}
	}
}

