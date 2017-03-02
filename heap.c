//IMPLEMENTATION OF MAX_HEAP
#include<stdio.h>
#include<limits.h>
#define SIZE 100
int h[SIZE];
int size=0;
//FUNCTION TO SWAP ELEMENTS BY POSITIONS
int swap(x,y)
int x;
int y;
{
	int t;
	t=h[x];
	h[x]=h[y];
	h[y]=t;
	return 0;
}
//FUNCTION THAT RETURNS INDEX OF THE PARENT
int parent(i)
int i;
{
	return (i-1)/2;
}
//FUNCTION THAT RETURNS INDEX OF THE LEFT CHILD
int leftchild(i)
int i;
{
	return 2*i+1;
}
//FUNCTION THAT RETURNS INDEX OF THE RIGHT CHILD
int rightchild(i)
int i;
{
	return 2*(i+1);
}
//FUNCTION TO MOVE AN ELEMENT UPWARDS TO ITS APPROPRIATE POSITION
int shiftUp(i)
int i;
{
	if(i>0 && h[parent(i)]<h[i])//TO CHECK IF IT IS AT ITS CORRECT POSITION
	{
		swap(i,parent(i));
		shiftUp(parent(i));
	}
	return 0;
}
//FUNCTION TO MOVE AN ELEMENT DOWNWARDS TO ITS APPROPRIATE POSITION
int shiftDown(i)
int i;
{
	int r,l,maxIndex=i;
	r=rightchild(i);
	if(r<size && h[r]>h[maxIndex])//TO CHECK IF IT SHOULD BE MOVED DOWNWARDS
	maxIndex=r;
	l=leftchild(i);
	if(l<size && h[l]>h[maxIndex])//TO CHECK IF IT SHOULD BE MOVED DOWNWARDS LEFT RATHER THAN RIGHT
	maxIndex=l;
	if(i!=maxIndex)//TO CHECK IF THE ELEMENT HAS EACHED ITS PROPER POSITON
	{
		swap(i,maxIndex);
		shiftDown(maxIndex);
	}
	return 0;
}
//FUNCTION TO INSERT A NEW ELEMENT INTO THE HEAP
int insert(k)
int k;
{
	if(size==SIZE)//TO CHECK IF ANY SPACE IS LEFT OR NOT
	{
		printf("ERROR\n");
		return 0;
	}
	h[size]=k;
	shiftUp(size);//THE ELEMENT IS GIVEN THE END POSITION THEN MOVED UPWARDS TO REACH ITS APPROPRIATE POSITION
	size++;
	return 0;
}
//FUNCTION THAT RETURNS THE LARGEST ELEMENT IN THE HEAP
int extractMax()
{
	int result=h[0];
	h[0]=h[size-1];//THE LARGEST ELEMENT IS SWAPPED WITH THE LAST ELEMENT
	size--;
	shiftDown(0);
	return result;
}
//FUNCTION TO CHANGE THE PRIORITY
int changePriority(i,p)
int i;
int p;
{
	h[i]=p;
	//TO RESTORE THE APPROPRIATE POSITION OF THE ELEMENT AFTER CHANGE IN POSITION
	if(h[i]<h[leftchild(i)] || h[i]<h[rightchild(i)])
	shiftDown(i);
	else
	shiftUp(i);
	return 0;
}
//FUNCTION TO REMOVE AN ELEMENT
int remove_(i)
int i;
{
	h[i]=INT_MAX;//THE ELEMENT IS ASSIGNED THE MAXIMUM VALUE
	shiftUp(i);
	extractMax();
	return 0;
}
//FUNCTION TO PRINT THE HEAP
int print_()
{
	int i;
	for(i=0;i<size;i++)
	printf("->%d(%d)",h[i],i);//THE INDEX IS PRINTED ALONGSIDE THE ELEMENT
	printf("\n");
	return 0;
}
//FUNCTION TO TAKE THE USER'S CHOICE AND DO THE APPROPRIATE JOB
int main()
{
	int ch,ele,in,max,i=0;
	printf("1.TO INSERT AN ELEMENT\n");
	printf("2.TO REMOVE AN ELEMENT\n");
	printf("3.TO EXTRACT THE LARGEST ELEMENT\n");
	printf("4.TO CHANGE PRIORITY OF AN ELEMENT\n");
	printf("5.TO PRINT THE HEAP\n");
	printf("6.TO STOP\n");
	while(i==0)
	{
		printf("ENTER YOUR CHOICE:");
		scanf("%d",&ch);
		switch(ch)
		{
		        case 1:printf("Enter an element:");
			       scanf("%d",&ele);
		      	       insert(ele);
			       print_();
			       break;
			case 2:printf("Enter the index of element you want to remove:");
			       scanf("%d",&in);
		               remove_(in);
		               print_();
			       break;
			case 3:max=extractMax();
		               printf("%d\n",max);
			       print_();
			       break;
			case 4:printf("Enter the index of the element and its new priority:");
			       scanf("%d%d",&in,&ele);
		               changePriority(i,ele);
			       print_();
			       break;
			case 5:print_();
			       break;
			case 6:i++;
			       break;
		}
	}
	return 0;
}
//END OF PROGRAM
