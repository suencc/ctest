/**********************************************************************
宏定义------macro definition
**********************************************************************/
#define Type		  int
#define INITIAL_SIZE  30				//栈的初始化大小---initial size of the stack
#define INCREASE_SIZE 20				//栈大小的增量-----increase size of the stack
#define ROW           10				//打印栈中元素的每行个数---the number of row
//#define debug


/*************************************************************************
结构体的定义-----------struct definition
*************************************************************************/
typedef struct stack
{
	Type *data;
	int top;							//栈顶指针----top stack point
	int StackSize;						//栈的大小----size of the stack
}Stack;

/*************************************************************************
函数定义--------function definition
*************************************************************************/

/*************************************************************************
函数名称：InitStack
函数表述: 对栈进行初始化
输入值：  Stack *
返回值：  初始化成功返回0，否则退出
*************************************************************************/
int InitStack(Stack *stack);
int ReleaseStack(Stack *stack);
int ClearStack(Stack *stack);
int Push(Stack *stack,Type elem);
Type Pop(Stack *stack);
int IsEmpty(Stack *stack);
void Traversal(Stack *stack);
Type getTopElem(Stack *stack);
