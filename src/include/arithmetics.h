#include <string.h>

#ifndef _ARITHMETICS_H
#define _ARITHMETICS_H
#include <math.h>

char * vartostr(element_var_t var)
{
	char * str = calloc(64,1);	//An int or floating point number can't go over this size 
	switch(var.type)
	{
		case INT:
			sprintf( str , "%d" , var.val.int_t );
			return str;
		case DOUBLE:
			sprintf( str , "%lf" , var.val.double_t );
			return str;
		case STRING:
			return var.val.char_t;
	}
	return NULL;
}

char * add_string(element_var_t var1 , element_var_t var2)	
{
	/* Concatenating two strings */
	char * str1 = vartostr(var1);
	char * str2 = vartostr(var2);
	int64_t len1 = strlen(str1);
	int64_t len2 = strlen(str2);
	char * tmp = malloc(len1+len2+1);
	int64_t i,j=0;
	for(i=0;i<len1;i++)
	tmp[j++] = str1[i] ;
	for(i=0;i<len2;i++)
		tmp[j++] = str2[i] ;
	tmp[len1+len2] = '\0' ;
	return tmp;
}

void alu_add(element_var_t * var1 , element_var_t * var2 , element_var_t * dest)
{
	if((*var1).type == INT && (*var2).type == INT) {		
		//Numerical (int64_t) addition
		(*dest).type = INT;
		(*dest).val.int_t = (*var1).val.int_t + (*var2).val.int_t ;
	}
	else if((*var1).type == INT && (*var2).type == DOUBLE) {		
		//Numerical (double) addition
		(*dest).type = DOUBLE;
		(*dest).val.double_t = (*var1).val.int_t + (*var2).val.double_t ;
	}
	else if((*var1).type == DOUBLE && (*var2).type == INT) {		
		//Numerical (double) addition
		(*dest).type = DOUBLE;
		(*dest).val.double_t = (*var1).val.double_t + (*var2).val.int_t ;
	}
	else if((*var1).type == DOUBLE && (*var2).type == DOUBLE) {		
		//Numerical (double) addition
		(*dest).type = DOUBLE;
		(*dest).val.double_t = (*var1).val.double_t + (*var2).val.double_t ;
	}
	else if((*var1).type == STRING || (*var2).type == STRING) {		//If one of the two elements is a string then it's string concatenation
		//String concatination
		(*dest).type = STRING;
		(*dest).val.char_t = add_string(*var1,*var2) ;
	}
}


void alu_sub(element_var_t * var1 , element_var_t * var2 , element_var_t * dest)
{
	if((*var1).type == INT && (*var2).type == INT) {		
		//Numerical (int64_t) subtraction
		(*dest).type = INT;
		(*dest).val.int_t = (*var1).val.int_t - (*var2).val.int_t ;
	}
	else if((*var1).type == INT && (*var2).type == DOUBLE) {		
		//Numerical (double) subtraction
		(*dest).type = DOUBLE;
		(*dest).val.double_t = (*var1).val.int_t - (*var2).val.double_t ;
	}
	else if((*var1).type == DOUBLE && (*var2).type == INT) {		
		//Numerical (double) subtraction
		(*dest).type = DOUBLE;
		(*dest).val.double_t = (*var1).val.double_t - (*var2).val.int_t ;
	}
	else if((*var1).type == DOUBLE && (*var2).type == DOUBLE) {		
		//Numerical (double) subtraction
		(*dest).type = DOUBLE;
		(*dest).val.double_t = (*var1).val.double_t - (*var2).val.double_t ;
	}
}


void alu_mul(element_var_t * var1 , element_var_t * var2 , element_var_t * dest)
{
	if((*var1).type == INT && (*var2).type == INT) {		
		//Numerical (int64_t) multiplication
		(*dest).type = INT;
		(*dest).val.int_t = (*var1).val.int_t * (*var2).val.int_t ;
	}
	else if((*var1).type == INT && (*var2).type == DOUBLE) {		
		//Numerical (double) multiplication
		(*dest).type = DOUBLE;
		(*dest).val.double_t = (*var1).val.int_t * (*var2).val.double_t ;
	}
	else if((*var1).type == DOUBLE && (*var2).type == INT) {		
		//Numerical (double) multiplication
		(*dest).type = DOUBLE;
		(*dest).val.double_t = (*var1).val.double_t * (*var2).val.int_t ;
	}
	else if((*var1).type == DOUBLE && (*var2).type == DOUBLE) {		
		//Numerical (double) multiplication
		(*dest).type = DOUBLE;
		(*dest).val.double_t = (*var1).val.double_t * (*var2).val.double_t ;
	}
}

void alu_div(element_var_t * var1 , element_var_t * var2 , element_var_t * dest)
{	
	/* All division is treated as double division */
	if((*var1).type == INT && (*var2).type == INT) {		
		//Numerical (int64_t) division
		(*dest).type = DOUBLE;
		double tmp1 = (*var1).val.int_t;
		double tmp2 = (*var2).val.int_t;
		double tmp3 = tmp1 / tmp2 ;
		if(isnormal(tmp3))	/* If NaN return INTEGER 0 */
		{
			(*dest).val.double_t = tmp3;
		} else 
		{
			(*dest).val.double_t = 0;
		}

	}
	else if((*var1).type == INT && (*var2).type == DOUBLE) {		
		//Numerical (double) division
		(*dest).type = DOUBLE;
		(*dest).val.double_t = (*var1).val.int_t / (*var2).val.double_t ;
	}
	else if((*var1).type == DOUBLE && (*var2).type == INT) {		
		//Numerical (double) division
		(*dest).type = DOUBLE;
		(*dest).val.double_t = (*var1).val.double_t / (*var2).val.int_t ;
	}
	else if((*var1).type == DOUBLE && (*var2).type == DOUBLE) {		
		//Numerical (double) division
		(*dest).type = DOUBLE;
		(*dest).val.double_t = (*var1).val.double_t / (*var2).val.double_t ;
	}
}

int64_t ipow(int64_t a , int64_t b)
{
	int64_t tmp = a;
	while(--b)
		a *= tmp;
	return a;
}

double dpow(double a , int64_t b)
{
	int64_t tmp = a;
	while(--b)
		a *= tmp;
	return a;
}


void alu_pow(element_var_t * var1 , element_var_t * var2 , element_var_t * dest)
{
	/* dest = var1 ^ var2 */

	if((*var1).type == INT && (*var2).type == INT) {		
		(*dest).type = INT;
		(*dest).val.int_t = ipow((*var1).val.int_t , (*var2).val.int_t) ;
	}
	/*
	else if((*var1).type == INT && (*var2).type == DOUBLE) {		
		(*dest).type = DOUBLE;
		double tmp = (*var1).val.int_t;
		(*dest).val.double_t = pow(tmp , (*var2).val.double_t) ;
	}
	*/
	else if((*var1).type == DOUBLE && (*var2).type == INT) {		
		(*dest).type = DOUBLE;
		(*dest).val.double_t = dpow((*var1).val.double_t , (*var2).val.int_t) ;
	}
	/*
	else if((*var1).type == DOUBLE && (*var2).type == DOUBLE) {	
		(*dest).type = DOUBLE;
		(*dest).val.double_t = pow((*var1).val.double_t , (*var2).val.double_t) ;
	}
	*/
}



#endif