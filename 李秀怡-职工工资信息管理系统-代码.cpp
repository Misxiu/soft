#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <conio.h>
using namespace std;
#pragma warning (disable:4996)
typedef struct Basic_information
{
	int id;
	char name[50];
	char duty[50];
}BI;//ְ��������Ϣ
typedef struct Basic_wage_information
{
	int basic_wage;//��������
	int job_wage;//��λ����
	int else_wage;//��������
	int reward;//����
	double net_payroll;//ʵ������
}BW;//���ʻ�����Ϣ
typedef struct Cost_information
{
	double tax;//����˰
	int home_rent;//ס������
	int annuity;//���Ͻ�
	int medicare;//ҽ�Ʊ���
	int unemploy;//ʧҵ����
}CI;//�۳�������Ϣ
typedef struct information
{
	BI personal;
	BW wage;
	CI cost;
	struct information* next;
	struct information* prior;
}data1;//��������Ϣ
data1* create_head()
{
	data1* head = NULL;
	head = (data1*)malloc(sizeof(data1));
	head->next = NULL;
	return head;
}//��ʼ��ͷ���
void title()
{
	cout << "                                         =======��ѡ�����б�===========\n";
	cout << "                                         ||\t1.¼��ְ����Ϣ         ||" << endl;
	cout << "                                         ||\t2.��ʾ����ְ����Ϣ     ||" << endl;
	cout << "                                         ||\t3.����ְ����Ϣ         ||" << endl;
	cout << "                                         ||\t4.�޸�ְ����Ϣ         ||" << endl;
	cout << "                                         ||\t5.ɾ��ְ����Ϣ         ||" << endl;
	cout << "                                         ||\t6.����ְ����Ϣ         ||" << endl;
	cout << "                                         ||\t7.���ְ����Ϣ         ||" << endl;
	cout << "                                         ||\t8.�˳�ϵͳ             ||" << endl;
	cout << "                                         ===============================\n";
}//�˵���
void scan(data1* p)
{
	cout << "������ְ����Ϣ����� ���� ְ��" << endl;
	cout << "                ";
	cin >> p->personal.id >> p->personal.name >> p->personal.duty;
	cout << "�����빤�ʻ�����Ϣ���������� ��λ���� �������� ����" << endl;
	cout << "                    ";
	cin >> p->wage.basic_wage >> p->wage.job_wage >> p->wage.else_wage >> p->wage.reward;
	cout << "������۳�������Ϣ��ס������ ���Ͻ� ҽ�Ʊ��� ʧҵ����" << endl;
	cout << "                    ";
	cin >> p->cost.home_rent >> p->cost.annuity >> p->cost.medicare >> p->cost.unemploy;

}
void input(data1* head)
{
	int n, i, a;
	data1* p = NULL, * q = NULL;
	p = head;
	do
	{
		cout << "���������¼��ְ������:";
		cin >> n;
		for (i = 0; i < n; i++)
		{
			
			q = (data1*)malloc(sizeof(data1));
			scan(q);
			p->next = q;
			q->prior = p;
			p = q;
			p->next = NULL;
		}
		cout << "��Ϣ��¼�ɹ�......" << endl;
		cout << "�Ƿ�������룺1.��  0.��" << endl;
		cin >> a;
	} while (a == 1);
}//¼��ְ����Ϣ
void calculate(data1* p)
{
	int sum;
	sum = (p->wage.basic_wage) + (p->wage.job_wage) + (p->wage.else_wage) + (p->wage.reward);
	if (sum < 3500)
		p->cost.tax = 0;
	else
		p->cost.tax = (sum - 3500) * 0.1;
	p->wage.net_payroll = sum - (p->cost.home_rent) - (p->cost.annuity) - (p->cost.medicare) - (p->cost.unemploy) - (p->cost.tax);
}//����ʵ������
void print(data1* p)
{
	calculate(p);
	cout << "��ţ�" << p->personal.id <<" " << "����:" <<p->personal.name << " " << "ְ��:"<< p->personal.duty << " " << "��������:" << p->wage.basic_wage<< " " << "��λ����:" << p->wage.job_wage<< " " << "��������:" << p->wage.else_wage<<" " << "����:" << p->wage.reward<<" " << "ס������:"<<p->cost.home_rent << " " << "���Ͻ�:" <<p->cost.annuity<< " " << "ҽ�Ʊ���:" <<p->cost.medicare <<" " << "ʧҵ����:" << p->cost.unemploy <<" " << "����˰:" << p->cost.tax<<" " << "ʵ������:" <<p->wage.net_payroll<< endl;
}//�������
void save_file(data1* head)
{
	data1* p = head;
	FILE* fp;
	fp = fopen("2.txt", "wb+");
	fprintf(fp, "��� ���� ְ�� �������� ��λ���� �������� ���� ס������ ���Ͻ� ҽ�Ʊ��� ʧҵ���� ʵ������\n");
	while (p->next != NULL)
	{
		p = p->next;
		fprintf(fp, "%d %s %s %d %d %d %d %d %d %d %d %.2f", p->personal.id, p->personal.name, p->personal.duty, p->wage.basic_wage, p->wage.job_wage, p->wage.else_wage, p->wage.reward, p->cost.home_rent, p->cost.annuity, p->cost.medicare, p->cost.unemploy, p->wage.net_payroll);
		fprintf(fp, "\n");
	}
	printf("���ݱ���ɹ�\n");
	fclose(fp);

}//���ڴ��е����ݱ��浽�ļ�
data1* search_key(data1* head)
{
	data1* p = head;
	char choose;
	cout << "ѡ�����йؼ�������ѯ" << endl;
	cout << "1.���    2.����" << endl;
	choose = getch();
	if (choose == '1')
	{
		int num;
		cout << "�������ţ�";
		cin >> num;
		while (p != NULL)
		{
			if (p->personal.id == num)
			{
				return p;
			}
			p = p->next;
		}
		if (p == NULL)
			return NULL;
	}
	if (choose == '2')
	{
		char nam[80];
		cout << "������������";
		cin >> nam;
		while (p != NULL)
		{
			if (!strcmp(nam, p->personal.name))
			{
				return p;
			}
			p = p->next;
		}
		if (p == NULL)
			return NULL;
	}
}//�ùؼ��ʲ�ѯ��Ϣ
void search(data1* head)
{
	data1* p = head, * q;
	q = search_key(head);//���չؼ��ʷ���ָ��
	if (q != NULL)
	{
		cout << "��ѯ�����" << endl;
		print(q);
	}
	else
		cout << "δ�ҵ�ְ����Ϣ" << endl;
}//��ѯְ����Ϣ
void show_all(data1* head)
{
	data1* p = head;
	cout << "ȫ��ְ����Ϣ����" << endl;
	int n = 1;
	if (p == NULL)
		cout << "��δ¼��ְ����Ϣ" << endl;
	else
	{
		while (p->next != NULL)
		{
			p = p->next;
			cout << "(" << n << ")";
			n++;
			print(p);
		}
	}
}//��ʾ����ְ������Ϣ
void delet(data1* head)
{
	data1* p = head, * q;
	cout << "��������ɾ�����ϵ���Ϣ" << endl;
	q = search_key(p);//�ùؼ�������ѯɾ������Ϣ
	if (q != NULL)
	{
		cout << "����Ҫɾ����ְ����Ϣ��" << endl;
		print(q);
		cout << "1.ɾ��  2.ȡ��" << endl;
		char a;
		a = getch();//���뵫����ʾ����Ļ��
		if (a == '1')
		{
			if (q == p)
			{
				head = head->next;
				free(p);
				cout << "ɾ���ɹ�" << endl;
			}
			else
			{
				if (q->next != NULL)
				{
					q->prior->next = q->next;
					q->next->prior = q->prior;
					free(q);
					cout << "ɾ���ɹ�" << endl;
				}
				else
				{
					q->prior->next = q->next;
					q->prior = NULL;
					free(q);
					cout << "ɾ���ɹ�" << endl;
				}
			}
		}
	}
	if (q == NULL)
		cout << "δ�ҵ�ְ����Ϣ" << endl;
}//ɾ��ְ����Ϣ
void insert(data1* head)
{
	data1* p = head, * q, * l;
	cout << "�����������Ϣ�Ľڵ�λ��" << endl;
	q = search_key(p);
	if (q == NULL)
		cout << "��ѯ�޹�" << endl;
	else
	{
		cout << "��ѯ�����" << endl;
		print(q);
		cout << "���λ�ã�1.���ǰ  2.����" << endl;
		int a;
		cin >> a;
		if (a == 2)
		{
			if (q->next != NULL)
			{
				l = (data1*)malloc(sizeof(data1));
				scan(l);
				l->next = q->next;
				l->prior = q;
				q->next->prior = l;
				q->next = l;
				cout << "��ӳɹ�" << endl;
			}//�����һ�������
			else
			{
				l = (data1*)malloc(sizeof(data1));
				scan(l);
				q->next = l;
				l->prior = q;
				l->next = NULL;
				cout << "��ӳɹ�" << endl;
			}//���һ�������
		}//��Ӻ���
		else if (a == 1)
		{
			l = (data1*)malloc(sizeof(data1));
			scan(l);
			l->prior = q->prior;
			l->next = q;
			q->prior->next = l;
			q->prior = l;
			cout << "��ӳɹ�" << endl;
		}//���ǰ��
	}
}//������Ϣ
int free_list(data1* head)
{
	data1* p = head;
	int choose;
	cout << "ȷ�����ְ����Ϣ��" << endl;
	cout << "1.ȷ��  2.ȡ��" << endl;
	cin >> choose;
	if (choose == 1)
	{
		p->next->prior = NULL;
		p->next = NULL;
		cout << "ְԱ��Ϣ����ա�" << endl;
		return 1;
	}
	else
		return 0;
}//��������
void modify(data1* head)
{
	cout << "����Ҫ�޸����ϵ���Ϣ" << endl;
	data1* p = head, * q = NULL;
	q = search_key(p);
	cout << "ȷ��Ҫ�޸ĵ���Ϣ" << endl;
	print(q);
	cout << "�Ƿ��޸ģ�1.ȷ��  2.ȡ��" << endl;
	int a;
	cin >> a;
	if (a == 1)
	{
		if (q != NULL)
		{
			cout << "�������޸ĺ����Ϣ��" << endl;
			scan(q);
			cout << "�����޸ĳɹ�" << endl;
		}
		else
			cout << "δ�ҵ�ְ����Ϣ" << endl;
	}
}//�޸���Ϣ
int main()
{
	data1* head;
	FILE* fp;
	head = create_head();
	cout << "           ==================================================================================\n";
	cout << "                                         ��ӭʹ��ְ��������Ϣ����ϵͳ" << endl;
	title();
	int choose, j = 0;
	while (1)
	{
		if (head->next == NULL)
			j = 0;
		else
			j = 1;
		cout << "           ==================================================================================\n";
		cout << "������˵�ѡ��:";
		cin >> choose;
		switch (choose)
		{
		case 1:
			input(head);
			save_file(head);
			break;

		case 2:
			system("cls");
			title();
			if (j == 0)
			{
				cout << "����δ����ְ����Ϣ" << endl;
				break;
			}
			else
			{
				show_all(head);
				break;
			}
		case 3:if (j == 0)
		{
			cout << "����δ����ְ����Ϣ" << endl;
			break;
		}
			  else
		{
			system("cls");
			title();
			search(head);
			save_file(head);
			break;
		}//����������,����в��Ҳ���
		case 4:if (j == 0)
		{
			cout << "����δ����ְ����Ϣ" << endl;
			break;
		}
			  else
		{
			system("cls");
			title();
			modify(head);
			save_file(head);
			break;
		}//������,�޸����ݲ������ļ�
		case 5:if (j == 0)
		{
			cout << "����δ����ְ����Ϣ" << endl;
			break;
		}
			  else
		{
			system("cls");
			title();
			delet(head);
			save_file(head);
			break;
		}//����������,�����ɾ������
		case 6:if (j == 0)
		{
			cout << "����δ����ְ����Ϣ" << endl;
			break;
		}
			  else
		{
			system("cls");
			title();
			insert(head);
			save_file(head);
			break;
		}//����������,����в������
		case 7:if (j == 0)
		{
			cout << "����δ����ְ����Ϣ" << endl;
			break;
		}
			  else
		{
			system("cls");
			title();
			free_list(head);
			save_file(head);
			break;
		}//����������,�������ղ���	
		case 8:
			cout << "��ӭ�´�ʹ�ã�" << endl;
			exit(0);//�ر������ļ�����ֹ����ִ�еĽ���
		default:
			cout << "���������������������룡" << endl;
			break;
		}
	}
	return 0;
}





