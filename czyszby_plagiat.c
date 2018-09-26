#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#define PI 3.14159265
struct word_count_t
{
	char *word;
	int counter;
};
struct dictionary_t
{
	int size;
	int capacity;
	struct word_count_t *wc;
};
struct array_t
{
	float *ptr;
	int size;
	int capacity;
};
void usun_znak(char *tab);
struct dictionary_t* create_dictionary(int N);
void destroy_dictionary(struct dictionary_t** d);
struct word_count_t* dictionary_find_word(const struct dictionary_t *d, const char *word);
void dictionary_display(const struct dictionary_t *d);
int dictionary_add_word(struct dictionary_t *d, const char *word);
int add_vectors(const struct array_t *a, const struct array_t *b, struct array_t **c);
int subtract_vectors(const struct array_t *a, const struct array_t *b, struct array_t **c);
float dot_product(const struct array_t *a, const struct array_t *b);
float angle_between_vectors(const struct array_t *a, const struct array_t *b);
float length(const struct array_t *a);
int normalize_vector(const struct array_t *a, struct array_t **b);
int create(struct array_t *a, int N);
int add(struct array_t *a, float value);
void display(const struct array_t *a);
void destroy(struct array_t *a);
int create_array(struct array_t **a, int N);
void destroy_array(struct array_t **a);
int remove_item(struct array_t *a, float value);
int nowy_slownik(FILE *file,struct dictionary_t *p);
int sumuj_slownik(struct dictionary_t *a,struct dictionary_t *b,struct dictionary_t *c)
{
	int i=0;
	struct word_count_t *f;
	for(i=0;i<a->size;i++)//kopia
	{
		if(dictionary_add_word(c,(a->wc+i)->word)!=0)
		{
			return 4;
		}	
		f=dictionary_find_word(c,(a->wc+i)->word);
		f->counter=(a->wc+i)->counter;
	}
	for(i=0;i<b->size;i++)//kopia
	{
		f=dictionary_find_word(c,(b->wc+i)->word);
		if(f==NULL)
		{
			if(dictionary_add_word(c,(b->wc+i)->word)!=0)
			{
				return 4;
			}	
			f=dictionary_find_word(c,(b->wc+i)->word);
			f->counter=(b->wc+i)->counter;	
			continue;
		}	
		f->counter+=(b->wc+i)->counter;
	}
	return 0;
}
void zrob_vector(struct dictionary_t* dcommon,struct dictionary_t* slownik,struct array_t *v)
{
	int suma=0,i=0;
	for(i=0;i<slownik->size;i++)
	{
		suma+=(slownik->wc+i)->counter;
	}
	struct word_count_t *f;
	for(i=0;i<dcommon->size;i++)
	{
		f=dictionary_find_word(slownik,(dcommon->wc+i)->word);
		if(f==NULL)
		{
			*(v->ptr+i)=0;
			v->size+=1;
			continue;
		}
		*(v->ptr+i)=(f->counter*1.0)/(suma*1.0);
		v->size+=1;
	}
}
float oblicz_kat(const struct array_t *a, const struct array_t *b)
{
	if(a==NULL||b==NULL||a->ptr==NULL||b->ptr==NULL||a->capacity<1||b->capacity<1||a->size<1||b->size<1||a->capacity<a->size||b->capacity<b->size)
	{
		return -1;
	}
	float x=dot_product(a,b);
	float y=length(a)*length(b);
	return	(x/y);
}
int main(void)
{
	//int gdzie=0;
	char*  filename1;
	filename1=malloc(sizeof(char)*51);
	if(filename1==NULL)
	{
		printf("Failed to allocate memory");
		return 4;
	}
	char *filename2;
	filename2=malloc(sizeof(char)*51);
	if(filename2==NULL)
	{
		free(filename1);
		printf("Failed to allocate memory");
		return 4;
	}
	printf("podaj nazwe pliku\n");
	scanf("%50s",filename1);
	FILE *file1;
	if((file1=fopen(filename1,"rt"))==NULL)
	{
		free(filename1);
		free(filename2);
		printf("File not found");
		return 2;
	}
	printf("podaj nazwe pliku\n");
	scanf("%50s",filename2);
	FILE *file2;
	if((file2=fopen(filename2,"rt"))==NULL)
	{
		free(filename1);
		free(filename2);
		fclose(file1);
		printf("File not found");
		return 2;
	}
	//printf("%d",gdzie++);
	struct dictionary_t *p=create_dictionary(10);
	if(p==NULL)
	{	
		printf("Failed to allocate memory");
		free(filename1);
		free(filename2);
		fclose(file1);
		fclose(file2);
		return 4;
	}
	//printf("%d",gdzie++);
	struct dictionary_t *d=create_dictionary(10);
	if(p==NULL)
	{	
		printf("Failed to allocate memory");
		free(filename1);
		free(filename2);
		fclose(file1);
		fclose(file2);
		destroy_dictionary(&p);
		return 4;
	}
	//printf("%d",gdzie++);
	if(nowy_slownik(file1,p)!=0)
	{
		printf("Failed to allocate memory");
		fclose(file1);
		fclose(file2);
		free(filename1);
		free(filename2);
		destroy_dictionary(&p);
		destroy_dictionary(&d);
		return 4;
	}
	//printf("%d",gdzie++);
	if(nowy_slownik(file2,d)!=0)
	{
		printf("Failed to allocate memory");
		fclose(file1);
		fclose(file2);
		free(filename1);
		free(filename2);
		destroy_dictionary(&p);
		destroy_dictionary(&d);
		return 4;
	}
	//printf("%d",gdzie++);
	struct dictionary_t *dcommon=create_dictionary(10);
	if(dcommon==NULL)
	{	
		printf("Failed to allocate memory");
		free(filename1);
		free(filename2);
		fclose(file1);
		fclose(file2);
		destroy_dictionary(&p);
		destroy_dictionary(&d);
		return 4;
	}
	//printf("%d",gdzie++);
	if(sumuj_slownik(p,d,dcommon)!=0)
	{
		printf("Failed to allocate memory");
		free(filename1);
		free(filename2);
		fclose(file1);
		fclose(file2);
		destroy_dictionary(&p);
		destroy_dictionary(&d);
		return 4;
	}
	//printf("%d",gdzie++);
	struct array_t *v1,*v2;
	int error=create_array(&v1,dcommon->size);
	if(error!=0)
	{
		printf("Failed to allocate memory");
		free(filename1);
		free(filename2);
		fclose(file1);
		fclose(file2);
		destroy_dictionary(&p);
		destroy_dictionary(&d);
		return 4;
	}
	//printf("%d",gdzie++);
	error=create_array(&v2,dcommon->size);
	if(error!=0)
	{
		printf("Failed to allocate memory");
		free(filename1);
		free(filename2);
		fclose(file1);
		fclose(file2);
		destroy_dictionary(&p);
		destroy_dictionary(&d);
		return 4;
	}
	//printf("%d",gdzie++);
	zrob_vector(dcommon,p,v1);
	zrob_vector(dcommon,d,v2);
	//printf("%d\n",gdzie++);
	printf("%.5f",oblicz_kat(v1,v2));
	/*dictionary_display(p);
	printf("\nnnnnnnnnnnnnnnnnnnnnnnnnnnnnn\n");
	dictionary_display(d);
	printf("\nnnnnnnnnnnnnnnnnnnnnnnnnnnnnn\n");
	dictionary_display(dcommon);*/
	free(filename1);
	free(filename2);
	fclose(file1);
	fclose(file2);
	destroy_dictionary(&p);
	destroy_dictionary(&d);
	destroy_dictionary(&dcommon);
	destroy_array(&v1);
	destroy_array(&v2);
	return 0;
}
void usun_znak(char *tab)
{
	int i=0;
	for(i=0;*(tab+i)!='\0';i++)
	{
		if(!((*(tab+i)>=65&&*(tab+i)<=90)||(*(tab+i)>=97&&*(tab+i)<=122)))
		{
			int j;
			for(j=i;*(tab+j+1)!='\0';j++)
			{
				*(tab+j)=*(tab+j+1);
			}
			*(tab+j)='\0';
			
		}
	}
}
int nowy_slownik(FILE *file,struct dictionary_t *p)
{
	char znak;
    char* word=malloc(sizeof(char)*101);
    if(word==NULL)
	{
		return 4;
	}
    int czy_eof=0;
	while(1)
	{
		while(1)
		{
			znak=fgetc(file);
			//putchar(znak);
			if((znak>=65&&znak<=90)||(znak>=97&&znak<=122))
			{
				break;
			}
			if(znak==EOF)
			{
				czy_eof=1;
				break;
			}
		}
		*(word)=znak;
		int id=1;
		while(1)
		{
			znak=fgetc(file);
			if(znak==' '||znak=='\n')
			{
				break;
			}
			if(znak==EOF)
			{
				czy_eof=1;
				break;
			}
			*(word+id)=znak;
			id++;
		}
		*(word+id)='\0';
		usun_znak(word);
	//	display(word);
	//	printf("\n");
		
		if(strlen(word)!=0)
		{
			int error=0;
			error=dictionary_add_word(p,word);
			if(error!=0)
			{
				free(word);
				return 4;
			}	
		}
		if(czy_eof==1)
		{
			break;
		}
	//	dictionary_display(p);
	//	printf("\n************************\n");
		int i;
		for(i=0;i<101;i++)
		{
			*(word+i)='\0';
		}	
	}
	free(word);
	return 0;
}
void displayr(char *tab)
{
	while(*tab)
	{
		printf("%c",*tab++);
	}
}
struct dictionary_t* create_dictionary(int N)
{
	if(N<1)
	{
		return NULL;
	}
	struct dictionary_t *p;
	p=malloc(sizeof(struct dictionary_t));
	if(p==NULL)
	{
		return NULL;
	}
	p->size=0;
	p->capacity=N;
	p->wc=malloc(sizeof(struct word_count_t)*N);
	if(p->wc==NULL)
	{
		free(p);
		return NULL;
	}	
	return p;
}
void destroy_dictionary(struct dictionary_t** d)
{
	if(d!=NULL&&*d!=NULL)
	{
		if((*d)->wc!=NULL)
		{
			int i;
			for(i=0;i<(*d)->size;i++)
			{
			
				if(((*d)->wc+i)!=NULL&&((*d)->wc+i)->word!=NULL)
				{
					free(((*d)->wc+i)->word);	
				}
			}
			free((*d)->wc);
		}
		free(*d);
	}
}
struct word_count_t* dictionary_find_word(const struct dictionary_t *d, const char *word)
{
	if(d==NULL||d->wc==NULL||word==NULL||d->capacity<1||d->size<0||d->size>d->capacity)
	{
		return NULL;
	}
	int i,j,k;
	for(i=0;i<d->size;i++)
	{
		if(((d->wc+i)->word)==NULL)
		{
			return NULL;
		}
		for(j=0;*((d->wc+i)->word+j)!='\0';j++);
		for(k=0;*(word+k)!='\0';k++);
		if(k!=j)
		{
			continue;
		}
	//	printf("tak");
		for(j=0;j<k;j++)
		{
			if(*((d->wc+i)->word+j)!=*(word+j))
			{
	//			printf("%s\n",word);
	//			printf("%s\n",(d->wc+i)->word);
				break;
			}
		}
		if(j==k)
		{
	//		printf("ejjjj");
			return (d->wc+i);
		}
		
	}
	return NULL;
}
void dictionary_display(const struct dictionary_t *d)
{
	if(d!=NULL&&d->capacity>=1&&d->size>=0&&d->size<=d->capacity&&d->wc!=NULL)
	{
		int i;
		for(i=0;i<d->size;i++)
		{
			if((d->wc+i)!=NULL&&((d->wc+i)->word)!=NULL)
			{
				displayr(((d->wc+i)->word));
				printf(" %d\n",(d->wc+i)->counter);
			}
		}
	}
}
int dictionary_add_word(struct dictionary_t *d, const char *word)
{
	if(word==NULL||d==NULL||d->capacity<=0||d->size<0||d->wc==NULL)
	{
		return 1;
	}
	struct word_count_t *p=dictionary_find_word(d, word);	
	if(p==NULL)
	{
		if(d->size==d->capacity)
		{
		//	printf("to to:");
		//	puts(d->wc->word);
			struct word_count_t *p=malloc(sizeof(struct word_count_t)*d->capacity);
			if(p==NULL)
			{
				return 2;
			}
			free(p);
			d->wc=(struct word_count_t *)realloc(d->wc,d->capacity*2*sizeof(struct word_count_t));
		//	printf("to to:");
		//	puts(d->wc->word);
			d->capacity*=2;
		}
		(d->wc+d->size)->word=malloc(sizeof(char)*(strlen(word)+1));
		if((d->wc+d->size)->word==NULL)
		{
			return 2;
		}
		strcpy((d->wc+d->size)->word,word);
		((d->wc+d->size)->counter)=1;
		d->size+=1;
		return 0;
	}
	else
	{
		p->counter++;
		return 0;
	}	
	return 1;
	
}
int create(struct array_t *a, int N)
{
	if(N<1||a==NULL)
	{
		return 1;
	}
	a->ptr=malloc(sizeof(int)*N);
	if(a->ptr==NULL)
	{
		return 2;
	}
	a->size=0;
	a->capacity=N;
	return 0;
}
int add(struct array_t *a, float  value)
{
	if(a==NULL||a->ptr==NULL||a->capacity<1||a->size<0)
	{
		return 1;
	}
	if(a->capacity==a->size)
	{
		return 2;
	}
	*(a->ptr+a->size)=value;
//	a->capacity-=1;
	a->size+=1;
	return 0;
}
void display(const struct array_t  *a)
{
	if(a!=NULL&&a->ptr!=NULL&&a->capacity>0&&a->size>0&&a->size<=a->capacity)
	{
		int i;
		for(i=0;i<a->size;i++)
		{
			printf("%.2f ",*(a->ptr+i));
		}
	}
}
void destroy(struct array_t *a)
{
	if(a!=NULL&&a->ptr!=NULL)
	{
		free(a->ptr);
	}
}
int create_array(struct array_t **a, int N)
{
	if(N<1||a==NULL)
	{
		return 1;
	}
	*a=malloc(sizeof(struct array_t));
	if(*a==NULL)
	{
		return 2;
	}
	int error;
	error=create(*a,N);
	if(error==2)
	{
		free(*a);
		return 2;
	}
	if(error==1)
	{
		free(*a);
		return 1;
	}
	return 0;
	
}
void destroy_array(struct array_t **a)
{
	if(a!=NULL&&*a!=NULL)
	{
		if((*a)->ptr!=NULL)
		{
			destroy(*a);
		}
		free(*a);
	}
	
}
int remove_item(struct array_t *a, float value)
{
	if(a==NULL||a->ptr==NULL||a->capacity<1||a->size<1||a->size>a->capacity)
	{
		return -1;
	}
	int i,j,licznik=0;
	for(i=0;i<a->size;i++)
	{
		if(*(a->ptr+i)==value)
		{
			licznik++;
			for(j=i;j<(a->size-1);j++)
			{
				*(a->ptr+j)=*(a->ptr+j+1);
			}
			a->size-=1;
			i--;
		}
	}
	return licznik;
}
int add_vectors(const struct array_t *a, const struct array_t *b, struct array_t **c)
{
	if(c==NULL||a==NULL||b==NULL||a->ptr==NULL||b->ptr==NULL||a->capacity<1||a->size<1||b->capacity<1||b->size<1||b->size>b->capacity||a->capacity<a->size)
	{
		return 1;
	}
	*c=malloc(sizeof(struct array_t));
	if((*c)==NULL)
	{
		return 2;
	}
	int size;
	if(a->size>b->size)
	{
		(*c)->ptr=malloc(sizeof(float)*a->size);
		if((*c)->ptr==NULL)
		{
			free(*c);
			return 2;
		}
		size=a->size;
	}
	else
	{
		(*c)->ptr=malloc(sizeof(float)*(b->size));
		if((*c)->ptr==NULL)
		{
			free(*c);
			return 2;
		}
		size=b->size;
	}
	int i;
	(*c)->size=size;
		for(i=0;i<a->size&&i<b->size;i++)
		{
			*((*c)->ptr+i)=*(a->ptr+i)+*(b->ptr+i);
		}
	if(b->size>a->size)
	{
		for(;i<b->size;i++)
		{
			*((*c)->ptr+i)=*(b->ptr+i);
		}
	}
	else
	{
		for(;i<a->size;i++)
		{
			*((*c)->ptr+i)=*(a->ptr+i);
		}
	}
	(*c)->capacity=(*c)->size;
	return 0;
}
int subtract_vectors(const struct array_t *a, const struct array_t *b, struct array_t **c)
{
	if(c==NULL||a==NULL||b==NULL||a->ptr==NULL||b->ptr==NULL||a->capacity<1||a->size<1||b->capacity<1||b->size<1||b->size>b->capacity||a->capacity<a->size)
	{
		return 1;
	}
	*c=malloc(sizeof(struct array_t));
	if((*c)==NULL)
	{
		return 2;
	}
	int size;
	if(a->size>b->size)
	{
		(*c)->ptr=malloc(sizeof(float)*a->size);
		if((*c)->ptr==NULL)
		{
			free(*c);
			return 1;
		}
		size=a->size;
	}
	else
	{
		(*c)->ptr=malloc(sizeof(float)*(b->size));
		if((*c)->ptr==NULL)
		{
			free(*c);
			return 2;
		}
		size=b->size;
	}
	int i;
	(*c)->size=size;
		for(i=0;i<a->size&&i<b->size;i++)
		{
			*((*c)->ptr+i)=*(a->ptr+i)-*(b->ptr+i);
		}
	if(b->size>a->size)
	{
		for(;i<b->size;i++)
		{
			*((*c)->ptr+i)=*(b->ptr+i);
		}
	}
	else
	{
		for(;i<a->size;i++)
		{
			*((*c)->ptr+i)=*(a->ptr+i);
		}
	}
	(*c)->capacity=(*c)->size;
	return 0;
}
float dot_product(const struct array_t *a, const struct array_t *b)
{
	if(a==NULL||b==NULL||a->ptr==NULL||b->ptr==NULL||a->capacity<1||b->capacity<1||a->size<1||b->size<1||a->capacity<a->size||b->capacity<b->size)
	{
		return -1;
	}
	float suma=0;
	int i;
	for(i=0;i<a->size;i++)
	{
		suma+=(*(a->ptr+i))*(*(b->ptr+i));
			
	}
	return suma;
}
float angle_between_vectors(const struct array_t *a, const struct array_t *b)
{
	if(a==NULL||b==NULL||a->ptr==NULL||b->ptr==NULL||a->capacity<1||b->capacity<1||a->size<1||b->size<1||a->capacity<a->size||b->capacity<b->size)
	{
		return -1;
	}
	float x=dot_product(a,b);
	float y=length(a)*length(b);
	if(y==0)
	{
		return -1;
	}
	float ret=180.0/PI;
	return	(acos(x/y)*ret);
}
float length(const struct array_t *a)
{
	if(a==NULL||a->ptr==NULL||a->size<1||a->capacity<1||a->size>a->capacity)
	{
		return -1;
	}
	int i;
	float suma=0;
	for(i=0;i<a->size;i++)
	{
		suma+=pow(*(a->ptr+i),2);
	}
	return sqrt(suma);
}
int normalize_vector(const struct array_t *a, struct array_t **b)
{
	if(a==NULL||a->ptr==NULL||a->size<1||a->capacity<1||a->size>a->capacity||b==NULL)
	{
		return 1;
	}
	*b=malloc(sizeof(struct array_t));
	if(*b==NULL)
	{
		return 2;
	}
	(*b)->ptr=malloc(sizeof(float)*a->size);
	if((*b)->ptr==NULL)
	{
		free(*b);
		return 2;
	}
	float length1=length(a);
	if(length1==0)
	{
		free((*b)->ptr);
		free(*b);
		return 3;
	}
	int i;
	for(i=0;i<a->size;i++)
	{
		*((*b)->ptr+i)=*(a->ptr+i)/length1;
	}
	(*b)->size=a->size;
	(*b)->capacity=a->size;
	return 0;
}
