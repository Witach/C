#include<iostream>
#include<cstdlib>
using namespace std;
class Stack
{	
	private:
	int size;
	int *array;
	int T;
	public:
	Stack(int size=10)
	{
		if(size<=0)
		{
			size=10;	
		}
		array=(int *)malloc(sizeof(int)*size);
		if(array==NULL)
		{
			printf("Field to allocate memory\n");
			size=0;
		}
		T=-1;
	}
	~Stack()
	{
		free(array);
	}
	void top(int x)
	{
		if(array!=NULL)
		{
			T+=1;
			if(T>=size)
			{
				int *array2=(int *)malloc(sizeof(int)*size*2);
				for(int a=0;a<size;a++)
				{
					array2[a]=array[a];
				}
				free(array);
				array=array2;
				array2=NULL;
				size*=2;
			}
			if(array!=NULL)
			{
				printf("-%d-\n",T);
				array[T]=x;
			}
			else
			{
				T=-1;
			}	

		}
	}
	int pop()
	{
		if(array!=NULL&&T!=-1)
		{
			T-=1;
			printf("%d*",T+1);
			return array[T+1];		
		}
		printf("Stack is Empty");
		return 0;
	}

};
int main(void)
{
	Stack s1(5);
	int a;
	for(a=-3;a<20;a++)
	{
		s1.top(a);
	}
	for(a=0;a<12;a++)
	{
		printf("%d\n",s1.pop());
	}
	s1.~Stack();	
}
