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
    printf("����\t�۸�\t����\n");
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
    	printf("ɾ���ɹ���");
        posLeftNode->next = posNode->next;
        free(posNode);
        posNode = NULL;
    }
}
void mackMenu()
{
    printf("------------------------------------\n");
    printf("       ͼ�����ϵͳ\n");
    printf("\t0.�˳�ϵͳ\n");
    printf("\t1.�Ǽ��鼮\n");
    printf("\t2.����鼮\n");
    printf("\t3.�����鼮\n");
    printf("\t4.�黹�鼮\n");
    printf("\t5.�鼮����\n");
    printf("\t6.ɾ���鼮\n");
    printf("\t7.�����鼮\n");
    printf("------------------------------------\n");
    printf("����������0��7\n");
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
        printf("�� �˳� ��\n");
        printf("�˳��ɹ�\n");
        system("pause");
        exit(0);
        break;
        case 1:
        printf("�� �Ǽ� ��\n");
        printf("�����鼮����Ϣ(name,price,num):");
        scanf("%s%f%d",tempBook.name,&tempBook.price,&tempBook.num);
        insertNodeByHead(list,tempBook);
        saveInfoToFile("bookinfo.txt",list);
		break;
		case 2:
        printf("�� ��� ��\n");
        printfList(list);
		break;
        case 3:
        printf("�� ���� ��\n");
		printf("��������ĵ�������");
		scanf("%s",tempBook.name);
		result = searchByName(list,tempBook.name);
		if(result==NULL)
		{
			printf("û������鼮�޷����ģ�\n");
		}
		else
		{
			if(result->data.num>=1)
			{
				result->data.num--;
				printf("���ĳɹ���\n"); 
			}
			else
			{
				printf("��ǰ�鼮�޿�棬����ʧ��"); 
			}
		}
		break;
        case 4:
        printf("�� �黹 ��\n");
        printf("������黹������");
        result = searchByName(list,tempBook.name);
		if(result==NULL)
		{
			printf("�ֵ��ǲ����Ҵ�ͼ����ˣ�\n");
		}
		else
		{
				result->data.num++;
				printf("�黹�ɹ���\n"); 
		}
		break; 
        case 5:
        printf("�� ���� ��\n");
		bubbleSortList(list);
		break;
        case 6:
        printf("�� ɾ�� ��\n");
        printf("������Ҫɾ���鼮������");
        scanf("%s",tempBook.name);
		deleteNodeByData(list,tempBook.name);
		saveInfoToFile("bookinfo.txt",list);
		break;
        case 7:
        printf("�� ���� ��\n");
		printf("������Ҫ��ѯ������");
		scanf("%s",tempBook.name);
		result = searchByName(list,tempBook.name);
		if(result==NULL) 
		{
			printf("δ�ҵ������Ϣ��\n");
		}
		else
		{
			printf("����\t�۸�\t����\n");
			printf("%s\t%.1f\t%d\n",result->data.name,result->data.price,result->data.num);
		}
		break;
        default:
        printf("�� error ��\n");break;
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
