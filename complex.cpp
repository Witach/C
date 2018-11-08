#include<iostream>
#include<string.h>
#include<cstdlib>
using namespace std;
bool validate(string number)
	{
		int kropki=0;
		int znaki=0;
		bool czy_dwa=false;
		int i=0;
		for(int a=0;number[a]!='\0';a++)
		{
			switch(number[a])
			{
				case '.':
					kropki++;
					break;
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					break;
				case '-':
				case '+':
					if(kropki==2)
					{
						return false;
					}
					if(a>=1&&(number[a-1]>='0'&&number[a-1]<='9')&&(number[a+1]>='0'&&number[a+1]<='9'))
					{
						czy_dwa=true;
					}
					znaki++;
					break;
				case 'i':
					i++;
					if(a==0)
					{
						return false;
					}
					break;
				default:
					return false;	
			}
		}	
		if(i>1||kropki>2||znaki>2)
		{
			return false;
		}
		else if(i==1&&czy_dwa&&znaki<1)
		{
			return false;
		}
		else if(i==0&&czy_dwa)
		{
			return false;
		}
		else if((!czy_dwa)&&(znaki>1||kropki==2))
		{
			return false;
		}
		for(int a=0;number[a]!='\0';a++)
		{
			if((number[a]=='+'||number[a]=='-')&&!((number[a+1]>='0'&&number[a+1]<='9')))
			{
				
				return false;
			}
			if(number[a]=='.')
			{
				if(!((number[a-1]>='0'&&number[a-1]<='9')&&(number[a+1]>='0'&&number[a+1]<='9')))
				{
					return false;
				}
						
			}
			if(number[a]=='i'&&!(number[a-1]>='0'&&number[a-1]<='9'))
			{
				return false;
			}
		}
		return true;
	}
class Complex
{
	private:
	float Re;
	float Im;
	public:
	Complex(float a=0,float b=0)
	{
		Re=a;
		Im=b;
	}
	Complex operator+(Complex b)
	{
		Complex c(Re+b.Re,Im+b.Im);
		return c;
	}
	Complex operator+(double a)
	{
		Complex c(Re+a,Im);
		return c;
	}
	void operator+=(Complex b)
	{
		Re=Re+b.Re;
		Im=Im+b.Im;
	}
	void operator+=(double a)
	{
		Re=Re+a;
	}
	Complex operator-(Complex b)
	{
		Complex c(Re-b.Re,Im-b.Im);
		return c;
	}
	Complex operator-(double a)
	{
		Complex c(Re-a,Im);
		return c;
	}
	void operator-=(Complex b)
	{
		Re=Re-b.Re;
		Im=Im-b.Im;	
	}
	void operator-=(double a)
	{
		Re=Re-a;	
	}
	Complex operator*(Complex b)
	{
		if(b.Im==0)
		{
			Complex c(Re*b.Re,Im*b.Re);
			return c;	
		}	
		Complex c(Re*b.Re-Im*b.Im,Re*b.Im+b.Re*Im);
		return c;
	}
	Complex operator*(double a)
	{
		Complex c(Re*a,Im*a);
		return c;	
	
	}
	void operator*=(Complex b)
	{
		if(b.Im==0)
		{
			Re=Re*b.Re;
			Im=Im*b.Re;	
		}
		else
		{
			Re=Re*b.Re-Im*b.Im;
			Im=Re*b.Im+b.Re*Im;
		}	
	}
	void operator*=(double a)
	{
		Re=Re*a;
		Im=Im*a;	

	}
	Complex operator/(Complex b)
	{
		float x,y,z;
		x=Re*b.Re-Im*b.Im;	
		y=Im*b.Re+Re*b.Im;
		z=b.Re*b.Re+b.Im*b.Im;	
		Complex c((x*1.0)/(z*1.0),(y*1.0)/(z*1.0));
		return c;
	}
	Complex operator/(double a)
	{
		Complex c(Re/a,Im/a);
		return c;
	}
	void operator/=(Complex b)
	{
		float x,y,z;
		x=Re*b.Re-Im*b.Im;
		y=Im*b.Re+Re*b.Im;
		z=b.Re*b.Re+b.Im*b.Im;
		Re=x/z;
		Im=y/z;
	}
	void operator/=(double a)
	{
		Re=Re/a;
		Im=Im/a;
	}
	float abs()
	{
		return sqrt(Re*Re+Im*Im);
	}
	float phase()
	{
		if(Re!=0)
		{
		
			if(Re>0)
			{
				return acos(Re/this->abs());
			}
			else if(Re<0)
			{
				return acos(Re/this->abs())+3.14;
			}	
		}
		else
		{
			if(Im>0)
			{
				return 3.14*0.5;
			}
			if(Im<0)
			{
				return -3.14*0.5;
			}
		}
		return 0;
	}
	Complex conj()
	{
		Complex c(Re,-1*Im);
		return c;
	}
	friend ostream & operator <<(ostream & out,Complex a)
	{
		string odp1;
		string odp;
		if(a.Im<0)
		{
			sprintf((char *)odp.c_str(),"%.2f%.2fi",a.Re,a.Im);
			odp1=odp.c_str();
		}
		else
		{
			sprintf((char *)odp.c_str(),"%.2f+%.2fi",a.Re,a.Im);
			odp1=odp.c_str();
		}
		return out<<odp1;
	}
	
	friend istream& operator >>(istream & in,Complex &nu)
	{
		string insert;
		in>>insert;
		cout<<insert<<endl;
		for(int a=0;insert[a]!='\0';a++)
		{
			if(insert[a]==' '||insert[a]=='\n')
			{
				for(int b=a;insert[b]!='\0';b++)
				{
					insert[b]=insert[b+1];
				}
			}	
		}
		if(validate(insert)==false)
		{
			nu.Im=0;
			nu.Re=0;
			return in;
		}
		double liczba=atof(&insert[0]);
		int znak=0;
		if(insert[0]>='0'&&insert[0]<='9')
		{
			znak++;
		}
		for(int a=0;insert[a]!='\0';a++)
		{
			if(insert[a]=='+'||insert[a]=='-')
			{
				znak++;
			}
			if(znak==2)
			{
				nu.Re=liczba;
				nu.Im=atof(&insert[a+1]);
				cout<<nu.Re<<endl<<nu.Im<<endl;
				return in;
			}
			if(insert[a]=='i')
			{
				nu.Im=liczba;
				nu.Re=0;
				return in;
			}
		}
		nu.Re=liczba;
		nu.Im=0;
		return in;

	}	
};
int main(void)
{
	Complex c1(5,5);
	Complex c2(1,1);
	cout<<c1<<endl;
	cout<<c2<<endl;
	c2=c1-c2;
	cout<<c2<<endl;
	return 0;		
}
