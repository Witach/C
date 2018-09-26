#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
int subtract(const char* number1, const char* number2, char** result);
int add(const char* number1, const char* number2, char** result);
int validate(const char *number);
int multiply(const char* number1, const char* number2, char** result);
int compare(const char* number1, const char* number2);
int validate_expression(const char *expr);
int calculate(const char* expr, char **result);
void dodaj(char *result, int n, int shift);
void pomnuz(const char *number1, const char *number2, char *result);
int ktora_weksza(const char *number1, const char *number2);
void przesun_1(char *str)
{
	int i;
	for(i=strlen(str);i>=0;i--)
	{
		*(str+i+1)=*(str+i);
		}	
}
void przesun_x(char *str,int x)
{
	int i;
	for(i=strlen(str);i>=0;i--)
	{
		*(str+i+x)=*(str+i);
	}
}
void usun_cyfre(char *str)
{
	int i=0;
	while(*(str+i)=='-')
	{
		i++;
	}
	int size=strlen(str);
	int j=i,s=0;
	for(j=i,s=0;j<=size;j++,s++)
	{
		*(str+s)=*(str+j);
	}
}
void usun_zero(char *str)
{
	int p=0;
	while(*(str+p)=='0')
	{
		p++;
	}
	int rozmiar=strlen(str);
	int j=p,s=0;
	for(j=p,s=0;j<=rozmiar;j++,s++)
	{
		*(str+s)=*(str+j);
	}
}
void reverse(char *tab)
{
	int i,j,rick;
	for(i=0;*(tab+i)!='\0';i++);
	i--;
	for(j=0;j<i;j++,i--)
	{
		rick=*(tab+j);
		*(tab+j)=*(tab+i);
		*(tab+i)=rick;
	}
}
void display(char *tab)
{
	while(*tab)
	{
		printf("%c",*tab++);
	}
}
int main(void)
{
	char *ptr,*result;
	//multiply("870\0","80987\0",&result);
//	puts(result);
//	printf("\n");
	ptr=malloc(sizeof(char)*501);
	if(ptr==NULL)
	{
		printf("Failed to allocate memory");
		return 3;
	}
    printf("podaj liczbe: ");
    scanf("%500s",ptr);
  //  printf("1");
    if(validate_expression(ptr)!=0)
    {
    	printf("Incorrect input");
    	free(ptr);
    	return 2;
	}
//	printf("2");
	if(calculate(ptr,&result)!=0)
	{
		printf("Failed to allocate memory");
		free(ptr);
		return 3;
	}
//	printf("3");;
	puts(result);
//	printf("4");
	free(ptr);
	free(result);
	return 0;
}
int ktora_wieksza(const char *number1, const char *number2)
{
	int i=0,j=0;
	int rozmiar1=strlen(number1),rozmiar2=strlen(number2);
	if(*number1=='-')
	{
		i++;
		rozmiar1--;
	}
	if(*number2=='-')
	{
		j++;
		rozmiar2--;
	}
	if(rozmiar1>rozmiar2)
	{
		return 1;
	}
	if(rozmiar1<rozmiar2)
	{
		return 0;
	}
	while(*(number2+j)!='\0'&&*(number1+i)==*(number2+j)&&*(number1+i)!='\0')
	{
		i++;
		j++;
	}
	if(*(number1+i)=='\0'&&*(number2+j)!='\0')
	{
		return 0;
	}
	if(*(number1+i)!='\0'&&*(number2+j)=='\0')
	{
		return 1;
	}
	if(*(number1+i)>*(number2+j))
	{
		return 1;
	}
	if(*(number1+i)<*(number2+j))
	{
		return 0;
	}
	if(*number1=='-'&&*number2!='-')
	{
		return -1;
	}
	if(*number1!='-'&&*number2=='-')
	{
		return -1;
	}
	return 1;
}
int calculate(const char* expr, char **result)
{
	if(expr==NULL||result==NULL)
	{
		return 1;
	}
	if(validate_expression(expr)!=0)
	{
		return 2;
	}
	*result=malloc(2*sizeof(char));
	if(*result==NULL)
	{
		return 3;
	}
	**result='0';
	*(*result+1)='\0';
	int k=0;
	for(k=0;*(expr+k)!='\0';k++)
	{
		if(*(expr+k)=='+')
		{
			k++;
			int id=k,dlugosc=0;
			if(*(expr+id)=='-')
			{
				dlugosc++;
				id++;
			}
			for(;isdigit(*(expr+id));id++,dlugosc++);
			char *liczba;
			liczba=malloc(sizeof(char)*(dlugosc+1));
			if(liczba==NULL)
			{
				free(*result);
				return 3;
			}
			int s;
			for(s=0;s<dlugosc;s++,k++)
			{
				*(liczba+s)=*(expr+k);
			}
			*(liczba+s)='\0';
			k--;
			char *str;
			int error=add(*result,liczba,&str);
			if(error==3)
			{
				free(liczba);
				free(*result);
				return 3;
			}
			*result=realloc(*result,(strlen(str)+1)*sizeof(char));
			unsigned int i;
			for(i=0;i<=strlen(str);i++)
			{
				*(*result+i)=*(str+i);
			}
			free(str);
			free(liczba);
		}
		else if(*(expr+k)=='-')
		{
			k++;
			int id=k,dlugosc=0;
			if(*(expr+id)=='-')
			{
				id++;
				dlugosc++;
			}
			for(;isdigit(*(expr+id));id++,dlugosc++);
			char *liczba;
			liczba=malloc(sizeof(char)*(dlugosc+1));
			if(liczba==NULL)
			{
				free(*result);
				return 3;
			}
			int s;
			for(s=0;s<dlugosc;s++,k++)
			{
				*(liczba+s)=*(expr+k);	
			}	
			*(liczba+s)='\0';
			k--;
			char *str;
			int error;
			error=subtract(*result,liczba,&str);
			if(error==3)
			{
				free(liczba);
				free(*result);
				return 3;
			}
			*result=realloc(*result,(strlen(str)+1)*sizeof(char));
			unsigned int i=0;
			for(i=0;i<=strlen(str);i++)
			{
				*(*result+i)=*(str+i);
			}
			free(str);
			free(liczba);
		}
		else if(*(expr+k)=='*')
		{
			k++;
			int id=k,dlugosc=0;
			if(*(expr+k)=='-')
			{
				id++;
				dlugosc++;
			}
			for(;isdigit(*(expr+id));id++,dlugosc++);
			char *liczba;
			liczba=malloc((dlugosc+1)*sizeof(char));
			if(liczba==NULL)
			{
				free(*result);
				return 3;
			}
			int s;
			for(s=0;s<dlugosc;s++,k++)
			{
				*(liczba+s)=*(expr+k);
			}
			*(liczba+s)='\0';
			k--;
			char *str;
			int error;
			error=multiply(*result,liczba,&str);
			if(error==3)
			{
				free(liczba);
				free(*result);
				return 3;
			}
			*result=realloc(*result,(strlen(str)+1)*sizeof(char));
			unsigned int i=0;
			for(i=0;i<=strlen(str);i++)
			{
				*(*result+i)=*(str+i);
			}
			free(str);
			free(liczba);
			
		}
		else
		{
			int id=k,dlugosc;
			if(*(expr+id)=='-')
			{
				id++;
				dlugosc++;
			}
			for(;isdigit(*(expr+id));id++,dlugosc++);
			char *liczba;
			liczba=malloc((dlugosc+1)*sizeof(char));
			if(liczba==NULL)
			{
				free(*result);
				return 3;
			}
			int s;
			for(s=0;s<dlugosc;s++,k++)
			{
				*(liczba+s)=*(expr+k);
			}
			*(liczba+s)='\0';
			char *str;
			int error;
			error=add(*result,liczba,&str);
			if(error==3)
			{
				free(liczba);
				free(*result);
				return 3;
			}
			*result=realloc(*result,(strlen(str)+1)*sizeof(char));
			unsigned int i;
			for(i=0;i<=strlen(str);i++)
			{
				*(*result+i)=*(str+i);
			}
			free(str);
			free(liczba);
			k--;
		}
	}
	return 0;
}
int validate_expression(const char *expr)
{
	if(expr==NULL)
	{
		return 2;
	}
	int a;
	if((*expr<'0'||*expr>'9')&&*expr!='-')
	{
		return 1;
	}
	for(a=0;*(expr+a);a++)
	{
		if(!((*(expr+a)>='0'&&*(expr+a)<='9')||*(expr+a)=='-'||*(expr+a)=='*'||*(expr+a)=='+'))
		{
		//	printf("t1");
			return 1;
		}
	}

	a=0;
	int i=0;
	for(a=0;*(expr+a);a++,i=0)
	{
		if(*(expr+a)=='+'||*(expr+a)=='-'||*(expr+a)=='*')
		{
			a++;
			/*if(*(expr+a)=='0'&&!(*(expr+a+1)=='+'||*(expr+a+1)=='-'||*(expr+a+1)=='*')||*(expr+a+1)=='0')
		    {
		    //	printf("t2");
		        return 1;
		    }*/
		     if(!((*(expr+a)=='-'&&(*(expr+a+1)>='1'&&*(expr+a+1)<='9'))||(*(expr+a)>='0'&&*(expr+a)<='9')))
		    {
		    //	printf("t3");
		        return 1;
		    }
		    while(*(expr+a+i)!='-'&&*(expr+a+i)!='+'&&*(expr+a+i)!='*'&&*(expr+a+i))
		    {
		        if(!(*(expr+i+a)>='0'&&*(expr+i+a)<='9'))
		        {
		        //	printf("t4 %c",*(expr+i+a));
		            return 1;   
		        //  printf("tutaj");
		        }
		        i++;
			}
		}
	}
	if(*(expr+a+i-1)=='+'||*(expr+a+i-1)=='-'||*(expr+a+i-1)=='*')
	{
		return 1;
	}
	return 0;
}

int multiply(const char* number1, const char* number2, char** result)
{
	if(number1==NULL||number2==NULL||result==NULL)
	{
		return 1;
	}
	if(validate(number1)||validate(number2))
	{
		return 2;
	}
	unsigned int rozmiar;
	rozmiar=strlen(number1)+strlen(number2)+3;
	*result=malloc(sizeof(char)*rozmiar);
	if(*result==NULL)
	{
		return 3;
	}
	int znak1=1,znak2=1;
	if(*number1=='-')
	{
		znak1=0;
	}
	if(*number2=='-')
	{
		znak2=0;
	}
	if(*number1=='0'||*number2=='0')
	{
		**result='0';
		*(*result+1)='\0';
		//printf("1");
		return 0;
	}
	else if(znak1==1&&znak2==1&&ktora_wieksza(number1,number2))
	{
		pomnuz(number1,number2,*result);
		//printf("2");
	}
	else if(znak1==1&&znak2==1&&!ktora_wieksza(number1,number2))
	{
		pomnuz(number2,number1,*result);
		//printf("3");
	}
	//
	else if(znak1==1&&znak2==0&&ktora_wieksza(number1,number2))
	{
		pomnuz(number1,number2,*result);
		przesun_1(*result);
		**result='-';
		//printf("4");
	}
	else if(znak1==1&&znak2==0&&!ktora_wieksza(number1,number2))
	{
		pomnuz(number2,number1,*result);
		przesun_1(*result);
		**result='-';
		//printf("5");
	}
	//
	else if(znak1==0&&znak2==1&&ktora_wieksza(number1,number2))
	{
		pomnuz(number1,number2,*result);
		przesun_1(*result);
		**result='-';
		//printf("6");
	}
	else if(znak1==0&&znak2==1&&!ktora_wieksza(number1,number2))
	{
		pomnuz(number2,number1,*result);
		przesun_1(*result);
		**result='-';
		//printf("7");
	}
	//
	else if(znak1==0&&znak2==0&&ktora_wieksza(number1,number2))
	{
		pomnuz(number1,number2,*result);
		usun_cyfre(*result);
		//printf("8");
	}
	else if(znak1==0&&znak2==0&&!ktora_wieksza(number1,number2))
	{
		pomnuz(number2,number1,*result);
		usun_cyfre(*result);
		//printf("9");
	}
	return 0;
	
}
int validate(const char * number)
{
    if(number==0)
    {
        return 2;
    }
    int a=1;
    if(*number=='0'&&*(number+1)!='\0')
    {
        return 1;
    }
     if(!((*(number)=='-'&&(*(number+1)>='1'&&*(number+1)<='9'))||(*number>='0'&&*number<='9')))
    {
        return 1;
    }
    while(*(number+a))
    {
        if(!(*(number+a)>='0'&&*(number+a)<='9'))
        {
            return 1;   
        //  printf("tutaj");
        }
        a++;
    }
    return 0;
}
int add(const char* number1, const char* number2, char** result)
{
    int size1=0,size2=0,sum=0,a=0,licznik=0,znak1=0,znak2=0;
    if(number1==0||number2==0||result==0)
    {
        return 1;
    }
    if(validate(number1)==1||validate(number2)==1)
    {
        return 2;
    }
    char *tab,*number11,*number22;
    for(size1=0;*(number1+size1)!='\0';size1++);
//  printf("1 %d ",size1);
    number11=malloc(sizeof(char)*(size1+1));
    if(number11==NULL)
    {
        return 3;
    }
    for(size2=0;*(number2+size2)!='\0';size2++);
//  printf("2 %d ",size2);
    number22=malloc(sizeof(char)*(size2+1));
    if(number22==NULL)
    {
        free(number11);
        return 3;
    }
    if(size1>size2)
    {
        tab=malloc(sizeof(char)*(size1+3+1));
        if(tab==NULL)
        {
            free(number11);
            free(number22);
            return 3;
        }   
    }
//  printf("1*%d*",number11);
//  printf("2*%d*",number22);
    if(size2>=size1)
    {
        tab=malloc(sizeof(char)*(size2+3+1));
        if(tab==NULL)
        {
            free(number11);
            free(number22);
            return 3;
        }
    }
    //printf("12");
    size1=0;
    size2=0;
    for(a=0;*(number1+a)!='\0';a++)
    {
        *(number11+a)=*(number1+a);
    }
    *(number11+a)='\0';
//  printf("3 %d ",a);
    for(a=0;*(number2+a)!='\0';a++)
    {
        *(number22+a)=*(number2+a);
    }
    *(number22+a)='\0';
    //printf("4 %d ",a);
    if(*number1=='-')
    {
    //  printf("tu");
        znak1=1;
        for(a=0;*(number11+a+1);a++)
        {
            *(number11+a)=*(number11+a+1);
        }
        *(number11+a)='\0';
    }
    //printf("5 %d ",a);
    if(*number2=='-')
    {
//      printf("tu");
        znak2=1;
        for(a=0;*(number22+a+1);a++)
        {
            *(number22+a)=*(number22+a+1);
        }
        *(number22+a)='\0';
    }
    //printf("6 %d ",a);
    if(znak1==0&&znak2==1)
    {   free(tab);
        free(number11);
        free(number22);
    //  printf("number1=%d,number2=%d");
        subtract(number1,number2+1,result);
        return 0;
    }
    if(znak1==1&&znak2==0)
    {
        subtract(number2,number1+1,result);
        free(number11);
        free(number22);
        free(tab);
        return 0;
    }
    
    while(*number11)
    {
        number11++;
        size1++;
    }
   // printf("7 %d ",size1);
    while(*number22)
    {
        number22++;
        size2++;
    }
     //printf("8 %d ",size2);
    number11--;
    number22--;
   a=0;
    while(size1>a&&size2>a)
    {
        sum=sum+(*number11-48)+(*number22-48);
        if(sum>=10)
        {
            *tab=(sum%10)+48;
            sum=sum-(sum%10);
            sum=sum/10;
            licznik++;
        }
        else
        {
            *tab=sum+48;
            sum=0;
            licznik++;
        }
        number11--;
        number22--;
        tab++;   
        a++;
    }
    if(size2==size1&&sum!=0)
    {
        *tab=sum+48;
        sum=0;
        tab++;
        licznik++;
        a++;
    }
    if(size2>size1)
    {
        while(a<size2)
        {
            if(sum==0)
            {
                while(a<size2)
                {
                    *tab=*number22;
                    number22--;
                    tab++;
                    a++;
                    licznik++;
                }
                break;
            }
    while(sum&&a<size2)
    {
        sum=sum+(*number22-48);
        if(sum>=10)
        {
            *tab=(sum%10)+48;
            sum=sum-(sum%10);
            sum=sum/10;
            licznik++;
        }
        else
        {
            *tab=sum+48;
            sum=0;
            licznik++;
        }
        number22--;
        tab++;
        a++;    
    }
    }
    }
    if(size2<size1)
    {
        while(a<size1)
        {
            if(sum==0)
            {
                while(a<size1)
                {
                    *tab=*number11;
                    number11--;
                    licznik++;
                    tab++;
                    a++;
                }
                break;
            }
    while(sum&&a<size1)
    {
        sum=sum+(*number11-48);
        if(sum>=10)
        {
            *tab=(sum%10)+48;
            sum=sum-(sum%10);
            sum=sum/10;
            licznik++;
        }
        else
        {
            *tab=sum+48;
            sum=0;
            licznik++;
        }
        number11--;
        tab++;
        a++;    
    }
            
        }
    }
       
    if(sum!=0)
    {
        *tab=sum+48;
        tab++;
        a++;
        licznik++;
    }
    *tab='\0';
    tab=tab-a;
    //printf("%s %c",tab,*(tab+-1+a));
      //printf("tutaj");
    int b=0;
    if(znak1==1&&znak2==1)
    {
        *result=malloc(sizeof(char)*(licznik+3));
        if(*result==NULL)
        {
            free(number11);
            free(number22);
            free(tab);
            return 3;
        }
        **result='-';
        for(b=1;b<=a;b++)
        {
//          printf("*");
            *(*result+b)=*(tab+a-b);
//          printf("*");
        }
    //  printf("end");
        *(*result+b)='\0';
    //  printf("toi");
        number11++;
        number22++;
        free(tab);
        free(number11);
        free(number22);
    //  printf("alok");
        return 0;
    }
    *result=malloc(sizeof(char)*(licznik+3));
    if(*result==NULL)
    {
        free(tab);
        free(number11);
        free(number22);
        return 3;
    }
    for(b=0,a=a-1;b<=a;b++)
    {
            *(*result+b)=*(tab+a-b);
    }
    *(*result+b)='\0';
    number11++;
    number22++;
    free(number11);
    free(number22);
    free(tab);
//  printf(" 1*%d*",number11);
//  printf(" 2*%d*",number22);
    return 0;
    
}
int subtract(const char* number1, const char* number2, char** result)
{
    if(number1==NULL||number2==NULL||result==NULL)
    {
        return 1;
    }   
     if(validate(number1)==1||validate(number2)==1)
    {
        return 2;
    }
    //printf("1");
    int size1=0,size2=0;
    for(size1=0;*(number1+size1)!='\0';size1++);
    for(size2=0;*(number2+size2)!='\0';size2++);
    if(size1>size2)
    {
        *result=malloc(sizeof(char)*(size1+3));
        if(*result==NULL)
        {
            return 3;
        }   
    }
    if(size2>=size1)
    {
        *result=malloc(sizeof(char)*(size2+3));
        if(*result==NULL)
        {
            return 3;
        }
    }
    int znak1=0,znak2=0;
    int a=0,b=0,k=0,i=0;
    if(*number1=='-')
    {
        znak1=1;
    }
    if(*number2=='-')
    {
        znak2=1;
    }
    if(znak1==1&&znak2==1)
    {
        free(*result);
        subtract(number2+1,number1+1,result);
        return 0;
    }
    if(znak1==1&&znak2==0)
    {
        free(*result);
        add(number1+1,number2,result);
        //printf("  %s  ",*result);
        for(a=0;*(*result+a)!='\0';a++);
        *(*result+a+1)='\0';
            for(;a>=0;a--)
            {
                *(*result+a+1)=*(*result+a);
            }
        *(*result)='-';
        return 0;
    }
    if(znak1==0&&znak2==1)
    {
        free(*result);
        add(number1,number2+1,result);
        return 0;
    }
    if(znak1==0&&znak2==0)
    {
        if(compare(number1,number2)==-1)
        {
            free(*result);
            subtract(number2,number1,result);
            for(a=0;*(*result+a)!='\0';a++);
            *(*result+a+1)='\0';
            for(;a>=0;a--)
            {
                *(*result+a+1)=*(*result+a);
            }
            *(*result)='-';
            return 0;
        }
    }
    size1--;
    size2--;
    k=0;
    while(size1!=-1&&size2!=-1)
    {
        a=*(number1+size1)-48;
        b=*(number2+size2)-48;
        if(k==-1)
        {
            a=a+k;
            k=0;
        }
        if(a<b)
        {
            k=-1;
            a+=10;
        }
        //printf("*%d*",a);
        *(*result+i)=a-b+48;
        //printf("&%d& ",*(*result+i));
        size1--;
        size2--;
        //printf("*%d %d*",size1,size2);
        i++;
    }
    while(size1!=-1)
    {
        if(k==-1)
        {
            a=*(number1+size1)-48+k;
            //printf("&%d&",a);
            k=0;
            if(a<0)
            {
                k=-1;
                a=9;
            }
            *(*result+i)=a+48;
            i++;
            size1--;
            continue;
        }
        *(*result+i)=*(number1+size1);
        i++;
        size1--;
    }
    *(*result+i)='\0';
    int j=0;
    int rick;
    for(j=0,i=i-1;i>j;j++,i--)
    {
        rick=*(*result+i);
        *(*result+i)=*(*result+j);
        *(*result+j)=rick;
    }
    while(*(*result)=='0')
    {
        for(k=0;*(*result+k+1)!='\0';k++)
        {
            *(*result+k)=*(*result+k+1);
        }
        *(*result+k)='\0';
    }
    if(**result=='\0')
    {
        **result='0';
        *(*result+1)='\0';
    }
    if((*(*result))=='-'&&(*(*result+1))=='0')
    {
        (*(*result))='0';
        (*(*result+1))='\0';
    }
    return 0;
}
int compare(const char* number1, const char* number2)
{
    if(number1==NULL||number2==NULL)
    {
        return 2;
    }
    if(validate(number1)==1||validate(number2)==1)
    {
        return 3;
    }
    int znak1=0;
    int znak2=0;
    if(*number1=='-')
    {
        znak1=1;
    }
    if(*number2=='-')
    {
        znak2=1;
    }
    if(znak1==1&&znak2==0)
    {
        return -1;
    }
    if(znak1==0&&znak2==1)
    {
        return 1;
    }
    int n1=0,n2=0;
    for(;*(number1+n1)!='\0';n1++);
    for(;*(number2+n2)!='\0';n2++);
    if(n1>n2)
    {
        if(znak1==1&&znak2==1)
        {
            return -1;
        }
        return 1;
    }
    if(n2>n1)
    {
        if(znak1==1&&znak2==1)
        {
            return 1;
        }
        
        return -1;
    }
    n1=0;
    if(znak1==1&&znak2==1)
    {
        while(*(number1+n1)==*(number2+n1)&&n1!=n2)
        {
            n1++;
        }
        if(n1==n2)
        {
            return 0;
        }
        if(*(number1+n1)>*(number2+n1))
        {
            return -1;
        }
        if(*(number2+n1)>*(number1+n1))
        {
            return 1;
        }
    }
    if(znak1==0&&znak2==0)
    {
        while(*(number1+n1)==*(number2+n1)&&n1!=n2)
        {
            n1++;
        }
        if(n1==n2)
        {
            return 0;
        }
        if(*(number1+n1)>*(number2+n1))
        {
            return 1;
        }
        if(*(number2+n1)>*(number1+n1))
        {
            return -1;
        }
    }
    return 0;
}

void pomnuz(const char *number1, const char *number2, char *result)
{
	unsigned int i=0;
	for(i=0;i<(strlen(number1)+strlen(number2)+1);i++)
	{
		*(result+i)='0';
	}
	*(result+1)='\0';
	int pozycja=0;
	int j;
	for(j=strlen(number2)-1;j>=0;j--)
	{
		if(*(number2+j)=='-')
		{
			continue;
		}
		int shift=pozycja,pmt,k;
		for(k=strlen(number1)-1;k>=0;k--)
		{
			if(*(number1+k)=='-')
			{
				continue;
			}
			pmt=((int)*(number2+j)-48)*((int)*(number1+k)-48);
			dodaj(result,pmt,shift);
			shift++;
		}
		pozycja++;
	}
}
void dodaj(char *result, int n, int shift)
{
	if(*result=='-')
	{
		*result='0';
	}
	int dlugosc=strlen(result)-1;
	if(dlugosc<=shift)
	{
		przesun_x(result,shift-dlugosc+1);
		int k=0;
		for(k=0;k<=shift-dlugosc;k++)
		{
			*(result+k)='0';
		}
	}
	int carry=0,cyfra;
	dlugosc=strlen(result)-1;
	int i;
	for(i=dlugosc-shift;i>=0;i--)
	{
		cyfra=(int)*(result+i)+carry-48+(n%10);
		if(cyfra>9)
		{
			cyfra-=10;
			carry=1;
		}
		else
		{
			carry=0;
		}
		*(result+i)=(char)(cyfra+48);
		n/=10;
	}
	if(carry)
	{
		przesun_1(result);
		*result='1';
	}
	usun_zero(result);
}



