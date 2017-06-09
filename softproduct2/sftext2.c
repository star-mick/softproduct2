#include<stdio.h>
#include<math.h>
#include<Windows.h>
#include<graphics.h>
#include<time.h>

#define mixnum 10000//圆最多数目
//四个边界线
#define leftline 1001
#define rightline 1002
#define upline 1002
#define downline 1001
#define ki 100

int head = 0;//结构体数组右侧
int tail = 0;//结构体数组左侧

//下面为主要内容
int pnum = 4;
int anum = 5;//记录矩形个数
int bnum = 0;//记录方形个数
float points[2][20];//记录所有点的位置，上限为20个点
int counts = 80;

struct Circle
{
	double r;//圆的半径
	double x;//横坐标
	double y;//纵坐标
	int serial;//序号
	int a[3];//关联圆或线
};
struct Area0  //定义可填充区域
{
	float longth;
	float wide;
	float x1, x2, y1, y2;
};
struct Area1  //定义可填充区域
{
	float d;//方形的边长
	float x1, x2, y1, y2;
};

struct  Area0 area0[100] = { 0 };//记录矩形域的数组
struct  Area1 area1[1000] = { 0 };//记录方形域的数组
struct Circle circles[mixnum] = {0};//为什么不能用mixnum??//因为多了分号
struct Circle temp;

void sort();//给新生圆排序
void creat();//创建新生圆
void draw();//画圆
void mainfunc();


void init()//初始化
{
	double r = 0, x = 0, y = 0;
	tail = 0;
	circles[tail].x = 0;
	circles[tail].y = 0;
	circles[tail].r = ki;
	circles[tail].serial = 0;
	//circles[tail].a = { 0 };
	//draw();
	if (tail == 0)
	{
		//printf("the first %d circle\n", tail);
		tail++;

		head++;
		r = (3 - 2 * sqrt((double)2))*ki;
		x = ki - r;
		y = ki - r;
		circles[head].r = r;
		circles[head].x = x;
		circles[head].y = y;
		circles[head].serial = head;
		circles[head].a[0] = upline;
		circles[head].a[1] = rightline;
		circles[head].a[3] = 0;
		//printf("the child %d circle\n", head);

		head++;
		circles[head].r = r;
		circles[head].x = -x;
		circles[head].y = y;
		circles[head].serial = head;
		circles[head].a[0] = upline;
		circles[head].a[1] = leftline;
		circles[head].a[3] = 0;
		//printf("the child %d circle\n", head);

		head++;
		circles[head].r = r;
		circles[head].x = x;
		circles[head].y = -y;
		circles[head].serial = head;
		circles[head].a[0] = downline;
		circles[head].a[1] = rightline;
		circles[head].a[3] = 0;
		printf("the child %d circle\n", head);

		head++;
		circles[head].r = r;
		circles[head].x = -x;
		circles[head].y = -y;
		circles[head].serial = head;
		circles[head].a[0] = downline;
		circles[head].a[1] = leftline;
		circles[head].a[3] = 0;
		//printf("the child %d circle\n", head);
		return;
	}
}
void type1(int i1, int i2, int i3)//角形,i1是父代，i2是上下，i3是左右
{
	double x, y, r;
	double R = 0;
	R = circles[i1].r;
	r = (3 - 2 * sqrt((double)2))*R;
	if (i3 == leftline)
		x = (-1)*(ki - r);
	else
		x = ki - r;
	if (i2 == downline)
		y = (-1)*(ki - r);
	else
		y = ki - r;
	head++;
	circles[head].r = r;
	circles[head].x = x;
	circles[head].y = y;
	circles[head].serial = head;
	circles[head].a[0] = i2;
	circles[head].a[1] = i3;
	circles[head].a[2] = i1;
	//printf("the child %d circle and banjing %f\n", circles[head].serial, r);
}
void type2(int i1, int i2, int i3)//y线性
{
	double x1, x2, y1, y2, r1, r2, x, y, r;
	x1 = circles[i1].x;
	y1 = circles[i1].y;
	r1 = circles[i1].r;
	x2 = circles[i3].x;
	y2 = circles[i3].y;
	r2 = circles[i3].r;
	r = r1*r2 / (r1 + r2 + 2 * sqrt(r1*r2));
	if (i2 == downline)
		y = r - ki;
	else
		y = ki - r;
	if (x1 < x2)
		x = x1 + sqrt(((r1 + r)*(r1 + r) - (y1 - y)*(y1 - y)));
	else
		x = x2 + sqrt(((r2 + r)*(r2 + r) - (y2 - y)*(y2 - y)));
	head++;
	circles[head].r = r;
	circles[head].x = x;
	circles[head].y = y;
	circles[head].serial = head;
	circles[head].a[0] = i2;
	circles[head].a[1] = i3;
	circles[head].a[2] = i1;
	//printf("the child %d circle and banjing %f\n", circles[head].serial, r);
}
void type3(int i1, int i2, int i3)//x线性
{
	double x1, x2, y1, y2, r1, r2, x, y, r;
	x1 = circles[i1].x;
	y1 = circles[i1].y;
	r1 = circles[i1].r;
	x2 = circles[i2].x;
	y2 = circles[i2].y;
	r2 = circles[i2].r;
	r = r1*r2 / (r1 + r2 + 2 * sqrt(r1*r2));
	if (i3 == leftline)
		x = r - ki;
	else
		x = ki - r;
	if (y1 < y2)
		y = y1 + sqrt(((r1 + r)*(r1 + r) - (x1 - x)*(x1 - x)));
	else
		y = y2 + sqrt(((r2 + r)*(r2 + r) - (x2 - x)*(x2 - x)));
	head++;
	circles[head].r = r;
	circles[head].x = x;
	circles[head].y = y;
	circles[head].serial = head;
	circles[head].a[0] = i2;
	circles[head].a[1] = i3;
	circles[head].a[2] = i1;
	//printf("the child %d circle and banjing %f\n", circles[head].serial, r);
}
void creat()
{
	double r = 0, x = 0, y = 0;
	int b[3] = { 0 };
	int i = 0;
	for (; i < 3; i++)
		b[i] = circles[tail].a[i];
	if (circles[tail].a[0] < 1000 && circles[tail].a[1] < 1000)
	{
		//type4(tail, b[0], b[1]);
		//type4(tail, b[0], b[2]);
		//type4(tail, b[2], b[1]);
		return;
	}
	if (circles[tail].a[0] > 1000 && circles[tail].a[1] < 1000)
	{
		type2(tail, b[0], b[1]);
		type2(tail, b[0], b[2]);
		//type4(tail, b[2], b[1]);
		return;
	}
	if (circles[tail].a[0] < 1000 && circles[tail].a[1] > 1000)
	{
		type3(tail, b[0], b[1]);
		type3(tail, b[2], b[1]);
		//type4(tail, b[2], b[0]);
		return;
	}
	if (circles[tail].a[0] > 1000 && circles[tail].a[1] > 1000)
	{
		type1(tail, b[0], b[1]);
		type2(tail, b[0], b[2]);
		type3(tail, b[2], b[1]);
		return;
	}
}
void sort()//采取插入排序算法
{
	int m = head - tail;
	int t = tail;
	int i = 0;
	int j = 0;
	//printf("m=%d\n",m);
	while (m--)
	{
		i = t;
		temp = circles[t];
		for (; i <= head; i++)
		{
			if (circles[i].r>temp.r)
				temp = circles[i];
		}
		j = temp.serial;
		//printf("j=%d\n",j);

		//circles[j] = circles[t];//结构体赋值咋回事？？
		
		circles[j].a[0] = circles[t].a[0];
		circles[j].a[1] = circles[t].a[1];
		circles[j].a[2] = circles[t].a[2];
		circles[j].r = circles[t].r;
		//circles[j].serial = circles[t].serial;
		circles[j].x = circles[t].x;
		circles[j].y= circles[t].y;

		circles[j].serial = j;
		circles[t] = temp;
		circles[t].serial = t;
		t++;
	}
	//printf("进行一次排序\n");
}
void draw(int i)
{
	printf("画出现在最大的圆%d\n", i);
	printf("圆的半径%f\n", circles[i].r);
	printf("圆的x坐标%f\n", circles[i].x);
	printf("圆的y坐标%f\n", circles[i].y);

	setcolor(RED);
	circle(circles[i].x + 2 * ki, circles[i].y + 2 * ki, circles[i].r);

}
void mainfunc()//主题 一次输出
{
	creat();
	tail++;
	sort();
}
void debug()
{
	int i = 0;
	printf("验证排序\n");
	for (; i <= tail-1; i++)
	{
		printf("%d号圆的半径是%f\n", i, circles[i].r);
	}
}
void drawpoint()
{
	int i = 0;
	setcolor(BLUE);
	for (; i < pnum; i++)
	{
		rectangle(points[0][i] + 2 * ki - 1, points[1][i] + 2 * ki - 1, points[0][i] + 2 * ki + 1, points[1][i] + 2 * ki + 1);
	}
}
void creatplot()//根据数目随机产生点
{
	srand((unsigned)time(NULL)); /*随机种子*/
	int i=0;
	for (; i < pnum; i++)
	{
        points[0][i] = rand() % (2 * (ki-2)) - ki+2; //产生点的x 坐标
		points[1][i] = rand() % (2 * (ki-2)) - ki+2; //产生点的y 坐标
		putpixel(points[0][i] + 2 * ki, points[1][i] + 2 * ki, YELLOW);
	}	
	//printf("creat points");
}
void sort2()//给点排序
{
	int i = 0, j = 0;
	while (i < pnum)
	{
		int s = 0;
		float x, y;
		for (j = i, s = i; j < pnum; j++)//用于画右面的线
		{
			if (points[0][j] >= points[0][s])
				s = j;
		}
		//交换顺序
		x = points[0][i]; y = points[1][i];
		points[0][i] = points[0][s]; points[1][i] = points[1][s];
		points[0][s] = x; points[1][s] = y;
		i++;
		if (i == pnum)
			break;

		for (j = i, s = i; j < pnum; j++)//用于画下面的线
		{
			if (points[1][j] <= points[1][s])
				s = j;
		}
		//交换顺序
		x = points[0][i]; y = points[1][i];
		points[0][i] = points[0][s]; points[1][i] = points[1][s];
		points[0][s] = x; points[1][s] = y;
		i++;
		if (i == pnum)
			break;

		for (j = i, s = i; j < pnum; j++)//用于画左面的线
		{
			if (points[0][j] <= points[0][s])
				s = j;
		}
		//交换顺序
		x = points[0][i]; y = points[1][i];
		points[0][i] = points[0][s]; points[1][i] = points[1][s];
		points[0][s] = x; points[1][s] = y;
		i++;
		if (i == pnum)
			break;

		for (j = i, s = i; j < pnum; j++)//用于画上面的线
		{
			if (points[1][j] >= points[1][s])
				s = j;
		}
		//交换顺序
		x = points[0][i]; y = points[1][i];
		points[0][i] = points[0][s]; points[1][i] = points[1][s];
		points[0][s] = x; points[1][s] = y;
		i++;
		if (i == pnum)
			break;
	}
}
void divide1()//根据点划分矩形区域
{
	int i = 0;
	float x3, x4, y3, y4;//记录空白区域的范围
	while (i < pnum)
	{
		if (i < 4)
		{
			area0[i].longth = ki - points[0][i];
			area0[i].wide = 2 * ki;
			area0[i].x1 = points[0][i];
			area0[i].y1 = -ki;
			area0[i].x2 = ki;
			area0[i].y2 = ki;
			i++;
			x4 = points[0][i-1];
			if (i == pnum)
				break;

			area0[i].longth = ki + points[0][i-1];
			area0[i].wide = ki + points[1][i];
			area0[i].x1 = -ki;
			area0[i].y1 = -ki;
			area0[i].x2 = points[0][i-1];
			area0[i].y2 = points[1][i];
			i++;
			y3 = points[1][i-1];
			if (i == pnum)
				break;

			area0[i].longth = ki + points[0][i];
			area0[i].wide = ki - points[1][i-1];
			area0[i].x1 = -ki;
			area0[i].y1 = points[1][i-1];
			area0[i].x2 = points[0][i];
			area0[i].y2 = ki;
			i++;
			x3 = points[0][i-1];
			if (i == pnum)
				break;

			area0[i].longth = points[0][i-3] - points[0][i-1];
			area0[i].wide = ki - points[1][i];
			area0[i].x1 = points[0][i-1];
			area0[i].y1 = points[1][i];
			area0[i].x2 = points[0][i-3];
			area0[i].y2 = ki;
			i++;
			y4 = points[1][i-1];
			if (i == pnum)
				break;
		}
		else
		{
			area0[i].longth = points[0][i-4] - points[0][i];
			area0[i].wide = points[1][i-1]-points[1][i-3];
			area0[i].x1 = points[0][i];
			area0[i].y1 = points[1][i-3];
			area0[i].x2 = points[0][i-4];
			area0[i].y2 = points[1][i-1];
			i++;
			x4 = points[0][i-1];
			if (i == pnum)
				break;

			area0[i].longth = points[0][i-1] - points[0][i - 3];
			area0[i].wide = points[1][i] - points[1][i - 4];
			area0[i].x1 = points[0][i - 3];
			area0[i].y1 = points[1][i - 4];
			area0[i].x2 = points[0][i - 1];
			area0[i].y2 = points[1][i];
			i++;
			y3 = points[1][i-1];
			if (i == pnum)
				break;

			area0[i].longth = points[0][i]-points[0][i - 4];
			area0[i].wide = points[1][i-3] - points[1][i-1];
			area0[i].x1 = points[0][i - 4];
			area0[i].y1 = points[1][i - 1];
			area0[i].x2 = points[0][i];
			area0[i].y2 = points[1][i - 3];
			i++;
			x3 = points[0][i-1];
			if (i == pnum)
				break;

			area0[i].longth = points[0][i - 3] - points[0][i - 1];
			area0[i].wide = points[1][i - 4] - points[1][i];
			area0[i].x1 = points[0][i - 1];
			area0[i].y1 = points[1][i];
			area0[i].x2 = points[0][i - 3];
			area0[i].y2 = points[1][i - 4];
			i++;
			y4 = points[1][i-1];
			if (i == pnum)
				break;
		}
	}
	//添加剩余区域信息
	area0[i].x1 = x3;
	area0[i].y1 = y3;
	area0[i].x2 = x4;
	area0[i].y2 = y4;
	area0[i].longth = x4 - x3;
	area0[i].wide = y4 - y3;
}
void sort3()//方形按边长排序
{
	int i = 0, j = 0, t=0;
	struct Area1 temp = {0};
	for (i = 0; i < bnum; i++)
	{
		for (t=i,j = i; j < bnum; j++)
		{
			if (area1[j].d > area1[t].d)
				t = j;
		}
		temp = area1[i];
		area1[i] = area1[t];
		area1[t] = temp;
		//printf("第%d个方形的边长是%f\n,", i, area1[i].d);
	}
}
void debug3()//测试矩形
{
	int i;
	for (i = 0; i < anum; i++)
	{
		printf("juxing %d longth=%f\n",i,area0[i].longth);
		printf("juxing %d wide=%f\n", i, area0[i].wide);
	}
}
void divide()//根据矩形域划分方形域，只进行一次划分
{
	int i = 0,j = 0;//j记录方形个数
	while (i < anum)
	{	
		printf("divide  %d \n",i);
		if (area0[i].longth == 0 || area0[i].wide == 0)
		{
			printf("矩形%d有0边\n",i);
			i++;
			continue;
		}
		//每个矩形不断分化成方形和矩形，并由所得矩形替代
		if (area0[i].longth > area0[i].wide)
		{
			while (area0[i].longth > area0[i].wide)//只分化出一个方形，直至矩形长宽大小关系变化
			{
				if (area0[i].wide < 0)
				{
					printf("wide error\n");
					break;
				}
				
				//产生新的方形
				area1[bnum].x1 = area0[i].x1;
				area1[bnum].y1 = area0[i].y1;
				area1[bnum].x2 = area1[bnum].x1 + area0[i].wide;
				area1[bnum].y2 = area0[i].y2;
				area1[bnum].d = area0[i].wide;

				rectangle(area1[bnum].x1 + 2 * ki, area1[bnum].y1 + 2 * ki, area1[bnum].x2 + 2 * ki, area1[bnum].y2 + 2 * ki);
				bnum++;
				//printf("creat %d fangs\n", bnum);

				//继承新的矩形
				area0[i].longth = area0[i].longth - area0[i].wide;
				area0[i].x1 += area0[i].wide;
				printf("继承新的%d\n矩形\n",i);
			}
		}
		else
			if (area0[i].longth < area0[i].wide)
			{
			while (area0[i].longth < area0[i].wide)
			{
				if (area0[i].longth < 0)
				{
					printf("longth error\n");
					break;
				}
				//产生新的方形
				area1[bnum].x1 = area0[i].x1;
				area1[bnum].y1 = area0[i].y1;
				area1[bnum].x2 = area0[i].x2;
				area1[bnum].y2 = area0[i].y1 + area0[i].longth;
				area1[bnum].d = area0[i].longth;
				rectangle(area1[bnum].x1 + 2 * ki, area1[bnum].y1 + 2 * ki, area1[bnum].x2 + 2 * ki, area1[bnum].y2 + 2 * ki);
				
				bnum++;
				//printf("creat %d fangs\n", bnum);

				//继承新的矩形
				area0[i].wide = area0[i].wide - area0[i].longth;
				area0[i].y1 += area0[i].longth;
				printf("继承新的%d\n矩形\n", i);
			}
			}
			else if (area0[i].longth == area0[i].wide)
			{
				area1[bnum].x1 = area0[i].x1;
				area1[bnum].y1 = area0[i].y1;
				area1[bnum].x2 = area0[i].x2;
				area1[bnum].y2 = area0[i].y2;
				area1[bnum].d = area0[i].longth;
				rectangle(area1[bnum].x1 + 2 * ki, area1[bnum].y1 + 2 * ki, area1[bnum].x2 + 2 * ki, area1[bnum].y2 + 2 * ki);

				bnum++;
				//printf("creat %d fangs\n", bnum);
				printf("无法继承\n");
				//anum--;//无法继承新的方形
				area0[i].longth=0;
				area0[i].wide = 0;
			}
		i++;
		//printf("creat %d fangs\n", bnum);
	}
}
void debug2()
{

	//如果矩形的短边大于现有的方形（上限counts）最小的边长，则再次划分
	int i,type=1;
	while (type)
	for (i = 0 , type = 0; i <= anum; i++)
	{		
		sort3();
		if (bnum > counts)
			bnum = counts;//限定所需的方形数目
		if (area0[i].longth > area1[bnum - 1].d && area0[i].wide > area1[bnum - 1].d)
		{
			divide();
			type = 1;
		}
	}

	for ( i = 0; i < bnum; i++)
	{
		printf("第%d个方形的边长是%f\n,", i, area1[i].d);
	}
	/*for (i = 0; i < anum; i++)
	{
		printf("第%d个矩形的宽是%f\n,", i, area0[i].wide);
		printf("第%d个矩形的长是%f\n,", i, area0[i].longth);
	}*/
}
void draw2()//输出圆，使每个正方形产生所要求数目的圆形，再在所有圆形排序，输出所要求的个数
{
	int count=counts-1;//产生多少个圆
	init();
	while (count--)
	{	  
		mainfunc();	
	}
	head = counts-1;
	debug();
	int i = 0, j = head, k = 0;
	//printf("bnum=%d\n",bnum);
	//printf("d=%d\n", area1[bnum-2].d);
	
	for (i=0; i < counts; i++)//为每个方形产生圆，采取相似和平移的方式，为前counts个方形生产原
	{ 	
		k = j;
		while (k--)//为每个圆做变化
		{
			head++;
			//printf("d=%d,",area1[i].d);
			circles[head].r = circles[k].r*area1[i].d / ki / 2;
			circles[head].serial = head;
			circles[head].a[0] = 0;
			circles[head].a[1] = 0;
			circles[head].a[2] = 0;
			circles[head].x = circles[k].x*area1[i].d / ki / 2 + area1[i].x1 + area1[i].d / 2;
			circles[head].y = circles[k].y*area1[i].d / ki / 2 + area1[i].y1 + area1[i].d / 2;
			
			if (head >= mixnum)
			{
				printf("数组越界\n"); break;
			}
		}
	   //printf("head=%d\n", head);
       tail = j+1;
	   //printf("tail= %d   head=%d\n", tail, head);
	   sort();
	   head = j + counts;
	}
	
	count = counts;
	for (i = 0; i < count; i++)
	{
		//printf("draw\n");
		draw(tail);
		tail++;
	}
}
void draw3()//输出矩形
{
	int i = 0;
	for (i=0 ; i <= anum; i++)
		rectangle(area0[i].x1 + 2 * ki, area0[i].y1 + 2 * ki, area0[i].x2 + 2 * ki, area0[i].y2 + 2 * ki);
}
void draw4()//输出方形
{
	int i = 0;
	for (i=0 ; i < bnum; i++)
		rectangle(area1[i].x1 + 2 * ki, area1[i].y1 + 2 * ki, area1[i].x2 + 2 * ki, area1[i].y2 + 2 * ki);
	printf("bnum=%d\n",bnum);
}
void setnum()
{
	printf("\nplease enter blocks num:");
	scanf_s("%d", &pnum);
	printf("\nplease enter circles num:");
	scanf_s("%d", &counts);
	anum = pnum + 1;
	printf("anum=%d,bnum=%d,pnum=%d\n", anum, bnum, pnum);
}
int main()
{

	int driver, mode;
	driver = DETECT;
	mode = 0;
	initgraph(&driver, &mode, "");

	setcolor(WHITE);
	rectangle(ki, ki, 3 * ki, 3 * ki);
	//line(2 * ki, 0, 2 * ki, 4 * ki);
	//line(0, 2 * ki, 4 * ki, 2 * ki);
	setnum();
	
	creatplot();
	sort2();
	//drawpoint();
	divide1();
	draw3();
	//debug3();
	divide();
	//sort3();
	debug2();
	draw4();
	drawpoint();
	draw2();
	//draw3();

	system("pause");
	return 0;
}
