#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct student
{
	char name[20];
	int number[12];
	char borrowBook[50];
	
};
struct bookInfo
{
	char name[20];
	float price;
	int num;
};
struct Node
{
    struct bookInfo data;
    struct Node* next;
};
struct Node* list=NULL;
struct Node* createHead()
{
    struct Node* headNode = (struct Node*)malloc(sizeof(struct Node));
    headNode->next = NULL;
    return headNode;
}
struct Node* cerateNode(struct bookInfo data)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
struct Node*searchByName(struct Node* headNode,char* bookName)
{
	struct Node* posNode = headNode->next;
	while(posNode!=NULL&&strcmp(posNode->data.name,bookName))
	{
		posNode = posNode->next;
	}
	return posNode;
}
void printfList(struct Node* headNode)
{
    struct Node* pMove = headNode->next;
    printf("书名\t价格\t数量\n");
    while(pMove!=NULL)
	{
        printf("%s\t%.1f\t%d\n",pMove->data.name,pMove->data.price,pMove->data.num);
        pMove = pMove->next;
    }
}
void insertNodeByHead(struct Node* headNode,struct bookInfo data)
{
    struct Node* newNode = cerateNode(data);
    newNode->next = headNode->next;
    headNode->next = newNode;
}
void deleteNodeByData(struct Node* headNode,char *bookName)
{
    struct Node* posLeftNode = headNode;
    struct Node* posNode = headNode->next;
    while(posNode!=NULL&&strcmp(posNode->data.name,bookName))
	{
    	posLeftNode=posNode;
    	posNode=posLeftNode->next;
	}
    if(posNode==NULL)return;
    else
	{
    	printf("删除成功！");
        posLeftNode->next = posNode->next;
        free(posNode);
        posNode = NULL;
    }
}
void mackMenu()
{
    printf("------------------------------------\n");
    printf("       图书管理系统\n");
    printf("\t0.退出系统\n");
    printf("\t1.登记书籍\n");
    printf("\t2.浏览书籍\n");
    printf("\t3.借阅书籍\n");
    printf("\t4.归还书籍\n");
    printf("\t5.书籍排列\n");
    printf("\t6.删除书籍\n");
    printf("\t7.查找书籍\n");
    printf("------------------------------------\n");
    printf("请输入数字0到7\n");
}
void saveInfoToFile(const char* fileName,struct Node*headNode)
{
	FILE *fp = fopen(fileName,"w");
	struct Node* pMove = headNode->next;
	while(pMove!=NULL)
	{
		fprintf(fp,"%s\t%.1f\t%d\n",pMove->data.name,pMove->data.price,pMove->data.num);
		pMove = pMove->next;
	}
	fclose(fp);
}
void readInfoToFile(const char* fileName,struct Node*headNode)
{
	FILE *fp = fopen(fileName,"r");
	if(fp==NULL)
	{
		fp = fopen(fileName,"w+");
	}
	struct bookInfo tempData;
	while(fscanf(fp,"%s\t%.1f\t%d\n",tempData.name,&tempData.price,&tempData.num)!=EOF)
	{
		insertNodeByHead(list,tempData);
	}
	fclose(fp);
}
void bubbleSortList(struct Node*headNode)
{
	for(struct Node* p = headNode->next;p!=NULL;p=p->next)
	{
		for(struct Node* q = headNode->next;q!=NULL;q=q->next)
		{
			if(q->data.price>q->data.price)
			{
				struct bookInfo tempData = q->data;
				q->data = q->next->data;
				q->next->data=tempData;
			}
		}
	}
	printfList(headNode);
}

void keyDown()
{
    int userkey = 0;
    struct bookInfo tempBook; 
    struct Node* result = NULL;
    scanf("%d",&userkey);
    switch(userkey)
	{
        case 0:
        printf("【 退出 】\n");
        printf("退出成功\n");
        system("pause");
        exit(0);
        break;
        case 1:
        printf("【 登记 】\n");
        printf("输入书籍的信息(name,price,num):");
        scanf("%s%f%d",tempBook.name,&tempBook.price,&tempBook.num);
        insertNodeByHead(list,tempBook);
        saveInfoToFile("bookinfo.txt",list);
		break;
		case 2:
        printf("【 浏览 】\n");
        printfList(list);
		break;
        case 3:
        printf("【 借阅 】\n");
		printf("请输入借阅的书名：");
		scanf("%s",tempBook.name);
		result = searchByName(list,tempBook.name);
		if(result==NULL)
		{
			printf("没有相关书籍无法借阅！\n");
		}
		else
		{
			if(result->data.num>=1)
			{
				result->data.num--;
				printf("借阅成功！\n"); 
			}
			else
			{
				printf("当前书籍无库存，借阅失败"); 
			}
		}
		break;
        case 4:
        printf("【 归还 】\n");
        printf("请输入归还书名：");
        result = searchByName(list,tempBook.name);
		if(result==NULL)
		{
			printf("兄弟是不是找错图书馆了！\n");
		}
		else
		{
				result->data.num++;
				printf("归还成功！\n"); 
		}
		break; 
        case 5:
        printf("【 排序 】\n");
		bubbleSortList(list);
		break;
        case 6:
        printf("【 删除 】\n");
        printf("请输入要删除书籍书名：");
        scanf("%s",tempBook.name);
		deleteNodeByData(list,tempBook.name);
		saveInfoToFile("bookinfo.txt",list);
		break;
        case 7:
        printf("【 查找 】\n");
		printf("请输入要查询的书名");
		scanf("%s",tempBook.name);
		result = searchByName(list,tempBook.name);
		if(result==NULL) 
		{
			printf("未找到相关信息！\n");
		}
		else
		{
			printf("书名\t价格\t数量\n");
			printf("%s\t%.1f\t%d\n",result->data.name,result->data.price,result->data.num);
		}
		break;
        default:
        printf("【 error 】\n");break;
    }
}
int main()
{
	list = createHead();
	readInfoToFile("bookinfo.txt",list);
    while(1)
	{
        mackMenu();
        keyDown();
    }
    return 0;
}
