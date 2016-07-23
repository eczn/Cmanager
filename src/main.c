#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "data_struct.h"
char user_name[16] = {'\0'};

void test(const char * str){
	printf(str);
	system("pause");
}

void print_list(struct subject_unit *head,char num){
	struct subject_unit *temA; 
	temA = head;
	while ( temA->next != NULL && num>1  ){
		temA = temA->next;
		num--; 
	}
	printf("\ntemA->Subname = %s \n",temA->Sub_name);
	printf("temA->credit = %.1f \n",temA->credit);
	printf("temA->next = %d , %s \n",temA->next,temA->next);
	printf("temA->us = %d , %s \n\n",temA->us,temA->us);
	system("pause");
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	char control = 0; 

	struct subject_unit *head = NULL; 
	struct subject_unit *t = NULL; 
	struct user_score *first = NULL;
	head = (struct subject_unit *)malloc(sizeof(struct subject_unit)); 
	head->next = NULL; 
	head->us = NULL;

	init(head);
	
//	printf("%s  %.1f",head->Sub_name,head->credit);	
	while (1){
		
		printf("* welcome..%s..这是某个软件的一部分... ESC也可以用来保存且退出.. \n",user_name);
		printf("1,科目>>\n");
		printf("2,用户成绩录入......\n");
		printf("3,以%s的成绩进行平均绩点计算\n",user_name);
		printf("4,列出%s的全部成绩.....\n",user_name);
		printf("5,save all\n");
//		printf("6,head->next = %d\n",head->next);
		bottom_print("Esc : exit   Number : Chose Function");
		control = getch();
		if (control != '1'){
			system("cls");
		}
		
		if (control == '1') {
			control = memu(1);
			system("cls");
			if (control == '1'){	
				new_sub_unit(head);
			} else if (control =='2'){
//				print_list(head,0);
				edit_sub_unit( head , &head);
//				print_list(head,0);
			}
			system("cls");
		} else if (control == '2') {
			input_user_score(head);
		} else if (control == '3') {
			output_GPA_all(head);
		} else if (control == '4') {
			output_user_score(head);
		} else if (control == '5' || control == 27) {
			
			if (control == 27)
				system("cls");
			_sleep(500); 
			printf("storing..."); 
			_sleep(1800); 
			data_stored(head);
			if (control == 27)
				return 0 ; 
		}
		
	}
	return 0;
}


