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
}BI;//职工基本信息
typedef struct Basic_wage_information
{
	int basic_wage;//基本工资
	int job_wage;//岗位津贴
	int else_wage;//其他补贴
	int reward;//奖金
	double net_payroll;//实发工资
}BW;//工资基本信息
typedef struct Cost_information
{
	double tax;//所得税
	int home_rent;//住房基金
	int annuity;//养老金
	int medicare;//医疗保险
	int unemploy;//失业保险
}CI;//扣除费用信息
typedef struct information
{
	BI personal;
	BW wage;
	CI cost;
	struct information* next;
	struct information* prior;
}data1;//定义总信息
data1* create_head()
{
	data1* head = NULL;
	head = (data1*)malloc(sizeof(data1));
	head->next = NULL;
	return head;
}//初始化头结点
void title()
{
	cout << "                                         =======请选择功能列表===========\n";
	cout << "                                         ||\t1.录入职工信息         ||" << endl;
	cout << "                                         ||\t2.显示所有职工信息     ||" << endl;
	cout << "                                         ||\t3.查找职工信息         ||" << endl;
	cout << "                                         ||\t4.修改职工信息         ||" << endl;
	cout << "                                         ||\t5.删除职工信息         ||" << endl;
	cout << "                                         ||\t6.插入职工信息         ||" << endl;
	cout << "                                         ||\t7.清空职工信息         ||" << endl;
	cout << "                                         ||\t8.退出系统             ||" << endl;
	cout << "                                         ===============================\n";
}//菜单栏
void scan(data1* p)
{
	cout << "请输入职工信息：编号 姓名 职务" << endl;
	cout << "                ";
	cin >> p->personal.id >> p->personal.name >> p->personal.duty;
	cout << "请输入工资基本信息：基本工资 岗位津贴 其他补助 奖金" << endl;
	cout << "                    ";
	cin >> p->wage.basic_wage >> p->wage.job_wage >> p->wage.else_wage >> p->wage.reward;
	cout << "请输入扣除费用信息：住房基金 养老金 医疗保险 失业保险" << endl;
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
		cout << "请输入需记录的职工人数:";
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
		cout << "信息记录成功......" << endl;
		cout << "是否继续输入：1.是  0.否" << endl;
		cin >> a;
	} while (a == 1);
}//录入职工信息
void calculate(data1* p)
{
	int sum;
	sum = (p->wage.basic_wage) + (p->wage.job_wage) + (p->wage.else_wage) + (p->wage.reward);
	if (sum < 3500)
		p->cost.tax = 0;
	else
		p->cost.tax = (sum - 3500) * 0.1;
	p->wage.net_payroll = sum - (p->cost.home_rent) - (p->cost.annuity) - (p->cost.medicare) - (p->cost.unemploy) - (p->cost.tax);
}//计算实发工资
void print(data1* p)
{
	calculate(p);
	cout << "编号：" << p->personal.id <<" " << "姓名:" <<p->personal.name << " " << "职务:"<< p->personal.duty << " " << "基本工资:" << p->wage.basic_wage<< " " << "岗位津贴:" << p->wage.job_wage<< " " << "其他补助:" << p->wage.else_wage<<" " << "奖金:" << p->wage.reward<<" " << "住房基金:"<<p->cost.home_rent << " " << "养老金:" <<p->cost.annuity<< " " << "医疗保险:" <<p->cost.medicare <<" " << "失业保险:" << p->cost.unemploy <<" " << "所得税:" << p->cost.tax<<" " << "实发工资:" <<p->wage.net_payroll<< endl;
}//输出界面
void save_file(data1* head)
{
	data1* p = head;
	FILE* fp;
	fp = fopen("2.txt", "wb+");
	fprintf(fp, "编号 姓名 职务 基本工资 岗位津贴 其他补助 奖金 住房基金 养老金 医疗保险 失业保险 实发工资\n");
	while (p->next != NULL)
	{
		p = p->next;
		fprintf(fp, "%d %s %s %d %d %d %d %d %d %d %d %.2f", p->personal.id, p->personal.name, p->personal.duty, p->wage.basic_wage, p->wage.job_wage, p->wage.else_wage, p->wage.reward, p->cost.home_rent, p->cost.annuity, p->cost.medicare, p->cost.unemploy, p->wage.net_payroll);
		fprintf(fp, "\n");
	}
	printf("数据保存成功\n");
	fclose(fp);

}//把内存中的数据保存到文件
data1* search_key(data1* head)
{
	data1* p = head;
	char choose;
	cout << "选择下列关键词来查询" << endl;
	cout << "1.编号    2.姓名" << endl;
	choose = getch();
	if (choose == '1')
	{
		int num;
		cout << "请输入编号：";
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
		cout << "请输入姓名：";
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
}//用关键词查询信息
void search(data1* head)
{
	data1* p = head, * q;
	q = search_key(head);//接收关键词返回指针
	if (q != NULL)
	{
		cout << "查询结果：" << endl;
		print(q);
	}
	else
		cout << "未找到职工信息" << endl;
}//查询职工信息
void show_all(data1* head)
{
	data1* p = head;
	cout << "全部职工信息如下" << endl;
	int n = 1;
	if (p == NULL)
		cout << "尚未录入职工信息" << endl;
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
}//显示所有职工的信息
void delet(data1* head)
{
	data1* p = head, * q;
	cout << "输入您想删除资料的信息" << endl;
	q = search_key(p);//用关键词来查询删除的信息
	if (q != NULL)
	{
		cout << "您想要删除的职工信息：" << endl;
		print(q);
		cout << "1.删除  2.取消" << endl;
		char a;
		a = getch();//输入但不显示在屏幕上
		if (a == '1')
		{
			if (q == p)
			{
				head = head->next;
				free(p);
				cout << "删除成功" << endl;
			}
			else
			{
				if (q->next != NULL)
				{
					q->prior->next = q->next;
					q->next->prior = q->prior;
					free(q);
					cout << "删除成功" << endl;
				}
				else
				{
					q->prior->next = q->next;
					q->prior = NULL;
					free(q);
					cout << "删除成功" << endl;
				}
			}
		}
	}
	if (q == NULL)
		cout << "未找到职工信息" << endl;
}//删除职工信息
void insert(data1* head)
{
	data1* p = head, * q, * l;
	cout << "请输入添加信息的节点位置" << endl;
	q = search_key(p);
	if (q == NULL)
		cout << "查询无果" << endl;
	else
	{
		cout << "查询结果：" << endl;
		print(q);
		cout << "添加位置：1.结点前  2.结点后" << endl;
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
				cout << "添加成功" << endl;
			}//非最后一个的添加
			else
			{
				l = (data1*)malloc(sizeof(data1));
				scan(l);
				q->next = l;
				l->prior = q;
				l->next = NULL;
				cout << "添加成功" << endl;
			}//最后一个的添加
		}//添加后面
		else if (a == 1)
		{
			l = (data1*)malloc(sizeof(data1));
			scan(l);
			l->prior = q->prior;
			l->next = q;
			q->prior->next = l;
			q->prior = l;
			cout << "添加成功" << endl;
		}//添加前面
	}
}//插入信息
int free_list(data1* head)
{
	data1* p = head;
	int choose;
	cout << "确认清空职工信息吗？" << endl;
	cout << "1.确认  2.取消" << endl;
	cin >> choose;
	if (choose == 1)
	{
		p->next->prior = NULL;
		p->next = NULL;
		cout << "职员信息已清空。" << endl;
		return 1;
	}
	else
		return 0;
}//销毁链表
void modify(data1* head)
{
	cout << "输入要修改资料的信息" << endl;
	data1* p = head, * q = NULL;
	q = search_key(p);
	cout << "确认要修改的信息" << endl;
	print(q);
	cout << "是否修改：1.确认  2.取消" << endl;
	int a;
	cin >> a;
	if (a == 1)
	{
		if (q != NULL)
		{
			cout << "请输入修改后的信息：" << endl;
			scan(q);
			cout << "数据修改成功" << endl;
		}
		else
			cout << "未找到职工信息" << endl;
	}
}//修改信息
int main()
{
	data1* head;
	FILE* fp;
	head = create_head();
	cout << "           ==================================================================================\n";
	cout << "                                         欢迎使用职工工资信息管理系统" << endl;
	title();
	int choose, j = 0;
	while (1)
	{
		if (head->next == NULL)
			j = 0;
		else
			j = 1;
		cout << "           ==================================================================================\n";
		cout << "请输入菜单选号:";
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
				cout << "您尚未输入职工信息" << endl;
				break;
			}
			else
			{
				show_all(head);
				break;
			}
		case 3:if (j == 0)
		{
			cout << "您尚未输入职工信息" << endl;
			break;
		}
			  else
		{
			system("cls");
			title();
			search(head);
			save_file(head);
			break;
		}//若存在数据,则进行查找操作
		case 4:if (j == 0)
		{
			cout << "您尚未输入职工信息" << endl;
			break;
		}
			  else
		{
			system("cls");
			title();
			modify(head);
			save_file(head);
			break;
		}//若存在,修改数据并保存文件
		case 5:if (j == 0)
		{
			cout << "您尚未输入职工信息" << endl;
			break;
		}
			  else
		{
			system("cls");
			title();
			delet(head);
			save_file(head);
			break;
		}//若存在数据,则进行删除操作
		case 6:if (j == 0)
		{
			cout << "您尚未输入职工信息" << endl;
			break;
		}
			  else
		{
			system("cls");
			title();
			insert(head);
			save_file(head);
			break;
		}//若存在数据,则进行插入操作
		case 7:if (j == 0)
		{
			cout << "您尚未输入职工信息" << endl;
			break;
		}
			  else
		{
			system("cls");
			title();
			free_list(head);
			save_file(head);
			break;
		}//若存在数据,则进行清空操作	
		case 8:
			cout << "欢迎下次使用！" << endl;
			exit(0);//关闭所有文件，终止正在执行的进程
		default:
			cout << "您的输入有误，请重新输入！" << endl;
			break;
		}
	}
	return 0;
}





