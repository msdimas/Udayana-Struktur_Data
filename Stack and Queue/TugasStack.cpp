#include<stdio.h>
#include<stdlib.h>      
#include<ctype.h>    
#include<string.h>

#define BATAS 100

char stack[BATAS];
int top = -1;


void push(char item) {
	if(top >= BATAS-1) {
		printf("\nStack Overflow.");
	} else {
		top = top+1;
		stack[top] = item;
	}
}

char pop() {
	char item ;

	if(top < 0) {
		printf("Stack under flow: invalid infix expression");
		getchar();
		exit(1);
	} else {
		item = stack[top];
		top = top-1;
		return(item);
	}
}

int is_operator(char simbol) {
	if(simbol == '^' || simbol == '*' || simbol == '/' || simbol == '+' || simbol =='-') {
		return 1;
	} else {
		return 0;
	}
}

int precedence(char simbol) {
	if(simbol == '^') {
		return(3);
	} else if(simbol == '*' || simbol == '/') {
		return(2);
	} else if(simbol == '+' || simbol == '-') {
		return(1);
	} else {
		return(0);
	}
}

void InfixToPostfix(char infix_exp[], char postfix_exp[]) { 
	int i, j;
	char item;
	char x;

	push('(');                             
	strcat(infix_exp,")");                  

	i=0;
	j=0;
	item=infix_exp[i];         

	while(item != '\0') {
		if(item == '(') {
			push(item);
		} else if( isdigit(item) || isalpha(item)) {
			postfix_exp[j] = item;              
			j++;
		} else if(is_operator(item) == 1) {
			x=pop();
			while(is_operator(x) == 1 && precedence(x)>= precedence(item))
			{
				postfix_exp[j] = x;                  
				j++;
				x = pop();                      
			}
			push(x);
			push(item);                 
		} else if(item == ')') {
			x = pop();                 
			while(x != '(')            
			{
				postfix_exp[j] = x;
				j++;
				x = pop();
			}
		} else { 
			printf("\nInvalid infix Expression.\n");        
			getchar();
			exit(1);
		}
		i++;
		item = infix_exp[i]; 
	} 

	if(top>0) {
		printf("\nInvalid infix Expression.\n");        
		getchar();
		exit(1);
	}

	if(top>0) {
		printf("\nInvalid infix Expression.\n");        
		getchar();
		exit(1);
	}


	postfix_exp[j] = '\0';

}

int main() {
	char infix[BATAS], postfix[BATAS];     

	printf("\nMasukkan Operasi Infix (Tanpa Sepasi) : ");
	gets(infix);

	InfixToPostfix(infix,postfix);             
	printf("Hasil Operasi Postfix: ");
	puts(postfix);                     

	return 0;
}