#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//eloelo
union byte
{
	unsigned int liczba;
	struct bits
{
	unsigned char a:1;
	unsigned char b:1;
	unsigned char c:1;
	unsigned char d:1;
	unsigned char e:1;
	unsigned char f:1;
	unsigned char g:1;
	unsigned char h:1;
}bit;
};
int decode(const char *filename, char *txt, int size)
{
	if(filename==0||txt==0||size<1)
	{
		return 2;
	}
	FILE *file;
	if((file=fopen(filename,"r"))==NULL)
	{
		return 1;
	}
	int k=0,stop=0;
	union byte odczyt;
	union byte znak;	
	while(feof(file)==0)
	{
		fscanf(file,"%u ",&odczyt.liczba);
		switch(k)
		{
			case 0:
				znak.bit.h=odczyt.bit.a;
				break;
			case 1:
				znak.bit.g=odczyt.bit.a;
				break;
			case 2:
				znak.bit.f=odczyt.bit.a;
				break;
			case 3:
				znak.bit.e=odczyt.bit.a;
				break;
			case 4:
				znak.bit.d=odczyt.bit.a;
				break;
			case 5:
				znak.bit.c=odczyt.bit.a;
				break;
			case 6:
				znak.bit.b=odczyt.bit.a;
				break;
		}
		if(k==7)
		{
			znak.bit.a=odczyt.bit.a;
			*txt=znak.liczba;
			if(stop+1==size)
			{
				break;
			}
			stop++;
		}
	
		if((++k)==8)
		{
			txt++;
			k=0;
		}
	}
    if(stop<size-1)
	{
		fclose(file);
		return 3;
	}
	fclose(file);
	return 0;
}
void display(char *txt)
{
	while(*txt)
	{
		putchar(*txt);
		txt++;
	}
}
int encode(const char *input, char *txt, const char *output)
{
	if(txt==NULL||output==0||input==0)
    {
        return 4;
    }
    FILE *file;
    FILE *file2;
    union byte in;
    union byte ou;
    int a,size=0;
    if((file=fopen(input,"r"))==NULL)
    {
       // printf("Error");
        return 1;
    }
    
    if((file2=fopen(output,"w"))==NULL)
    {
       // printf("Error");
        fclose(file);
        return 2;
    }
   while(1)
   {
   		if(feof(file)!=0)
   		{
	   		break;
		}
		if(fscanf(file,"%u ",(unsigned int *)&a)!=EOF)
		{
			size++;
		}
   }
   fseek(file,0,SEEK_SET);
   a=0;
   while(*(txt+a))
   {
   		a++;
   }
   if(a>size/8)
   {
   	fclose(file2);
    fclose(file);
    return 3;
   }
   int i=0;
   a=0;
   while((fscanf(file,"%u",&(in.liczba)))!=-1)
   {
   		if(fgetc(file)==' ')
   		{
   			if(fgetc(file)=='\n')
			{
				a=1;
			}	
			else
			{
				fseek(file,-1,SEEK_CUR);
			}
		}
		else
		{
			fseek(file,-1,SEEK_CUR);
		}
		switch(i)
		{
			case 0:
				ou.liczba=*txt;
				in.bit.a=ou.bit.h;
				if(a==1)
				{
					fprintf(file2,"%u ",in.liczba);
					putc('\n',file2);
				}
				else
				{
					fprintf(file2,"%u ",in.liczba);
				}
				break;
			case 1:
				in.bit.a=ou.bit.g;
				if(a==1)
				{
					fprintf(file2,"%u ",in.liczba);
					putc('\n',file2);
				}
				else
				{
					fprintf(file2,"%u ",in.liczba);
				}
				break;
			case 2:
				in.bit.a=ou.bit.f;
				if(a==1)
				{
					fprintf(file2,"%u ",in.liczba);
					putc('\n',file2);
				}
				else
				{
					fprintf(file2,"%u ",in.liczba);
				}
				break;
			case 3:
				in.bit.a=ou.bit.e;
				if(a==1)
				{
					fprintf(file2,"%u ",in.liczba);
					putc('\n',file2);
				}
				else
				{
					fprintf(file2,"%u ",in.liczba);
				}
				break;
			case 4:
				in.bit.a=ou.bit.d;
				if(a==1)
				{
					fprintf(file2,"%u ",in.liczba);
					putc('\n',file2);
				}
				else
				{
					fprintf(file2,"%u ",in.liczba);
				}
				break;
			case 5:
				in.bit.a=ou.bit.c;
				if(a==1)
				{
					fprintf(file2,"%u ",in.liczba);
					putc('\n',file2);
				}
				else
				{
					fprintf(file2,"%u ",in.liczba);
				}
				break;
			case 6:
				in.bit.a=ou.bit.b;
				if(a==1)
				{
					fprintf(file2,"%u ",in.liczba);
					putc('\n',file2);
				}
				else
				{
					fprintf(file2,"%u ",in.liczba);
				}
				break;
			case 7:
				in.bit.a=ou.bit.a;
				if(a==1)
				{
					fprintf(file2,"%u ",in.liczba);
					putc('\n',file2);
				}
				else
				{
					fprintf(file2,"%u ",in.liczba);
				}
				break;
		}
		i++;
		if(i==8)
		{
			i=0;
			txt++;
		}
		a=0;
		if(*txt=='\0')
		{
			break;
		}
		
   }
   while((fscanf(file,"%u",&(in.liczba)))!=-1)
   {
   		if(fgetc(file)==' ')
   		{
   			if(fgetc(file)=='\n')
			{
				a=1;
			}	
			else
			{
				fseek(file,-1,SEEK_CUR);
			}
		}
		else
		{
			fseek(file,-1,SEEK_CUR);
		}
		in.bit.a=0;
		if(a==1)
		{
			fprintf(file2,"%u ",in.liczba);
			putc('\n',file2);
		}
		else
		{
			fprintf(file2,"%u ",in.liczba);
		}
		a=0;
   }
    fclose(file2);
    fclose(file);
    return 0;
}
void read(char * txt)
{
    scanf("%c",txt++);
    while(*(txt-1)!='\n')
    {
        scanf("%c",txt++);
    }
    *(txt-1)='\0';
}
int main(void)
{
	char txt[1011];
	char output[50];
	char filename[50];
	char a;
	int error=0;
	printf("co chcesz zrboic");
	scanf("%c",&a);
	getchar();
	if(a=='e'||a=='E')
	{
		 printf("podaj tekst:\n");
        read(txt);
        printf("pdoaj nazwe pliku");
        scanf("%30s",filename);
      //  getchar();
        printf("pdoaj nazwe pliku");
        scanf("%30s",output);
        error=encode(filename,txt,output);
        if(error==1)
         {
            printf("File not found");
            return 1;
         }
         if(error==2)
         {
            printf("Couldn't create file");
            return 2;
         }
         if(error==3)
         {
            printf("File corrupted");
            return 3;
         }
        printf("File saved");
        return 0;
    	}
        if(a=='d'||a=='D')
    	{
        printf("pdoaj nazwe pliku");
        scanf("%30s",filename);
        error=decode(filename,txt,1010);
        if(error==1)
        {
            printf("File not found");
            return 1;
        }
        if(error==3)
        {
            printf("File corrupted");
            return 3;
        }
        	display(txt);
        	return 0;
		}
		   printf("Incorrect input");
	return 0;
}
