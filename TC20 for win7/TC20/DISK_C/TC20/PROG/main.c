#include <conio.h>
#include <math.h>
#include <graphics.h>
#include <stdio.h>

const float PI=3.14159;
int H=349,W=639,xz=319,yz=169,axis=1;
float xmin,ymin,xmax,ymax;

void myopengraph(int order){
	static int drive=VGA,mode=VGAMED;
	printf("Need axis?(Y/n):");
	if(getch()=='n')axis=0;
	else axis=1;
	printf("\nThis is homework %d, press any key to continue...",order);
	getch();
	initgraph(&drive,&mode,"C:\\TC20\\BGI");
	setbkcolor(1);
	setcolor(15);
	W=getmaxx();
	H=getmaxy();
	xz=(int)(-xmin/(xmax-xmin)*W+0.5);
	yz=H-(int)(-ymin/(ymax-ymin)*H+0.5);
	printf("HOMEWORK %d\n",order);
	printf("X %.2f to %.2f\nY %.2f to %.2f\n",xmin,xmax,ymin,ymax);
	if(axis==1 && xz>=0 && xz<=W){
		line(xz,0,xz,H);
		line(xz,0,(xz-5)>0?xz-5:0,8);
		line(xz,0,(xz+5)<W?xz+5:W,8);
	}
	if(axis==1 && yz>=0 && yz<=H){
		line(0,yz,W,yz);
		line(W,yz,W-8,(yz-5)>0?yz-5:0);
		line(W,yz,W-8,(yz+5)<H?yz+5:H);
	}
	setcolor(14);
}

void myclosegraph(){
	getch();
	closegraph();
}

void myexit(){
	while(1){
		printf("Ready to exit?(y/n)\n");
		if(getch() == 'y')exit();
		if(getch() == 'n')return;
	}
}

int myLine(float x1,float y1,float x2,float y2){
	int X1,X2,Y1,Y2,Dx,Dy;
	X1=(x1-xmin)/(xmax-xmin)*W+0.5;
	Y1=H-((y1-ymin)/(ymax-ymin)*H+0.5);
	X2=(x2-xmin)/(xmax-xmin)*W+0.5;
	Y2=H-((y2-ymin)/(ymax-ymin)*H+0.5);
	Dx=abs(X1-X2);
	Dy=abs(Y1-Y2);
	if(Dx>1 && Dy>1)return 2;
	if(Dx==0 && Dy==0)return 1;
	if(X1>=0 && X1<=W && X2>=0 && X2<=W && Y1>=0 && Y1<=H && Y2>=0 && Y2<=H){
		line(X1,Y1,X2,Y2);
		return 0;
	}
	return 4;
}

void hw1(){
	float a,t0,t,dt,x0,y0,x,y;
	printf("The function is:\nx = a*sin(3*t)*cos(t)\n");
	printf("y = a*cos(3*t)*sin(t)\nt from 0 to 2*PI\n");
	printf("Please input the constant a in the function:");
	a=0;
	while(a<=0){
		scanf("%f",&a);
	}
	xmin=-a;
	ymin=-a;
	xmax=a;
	ymax=a;
	myopengraph(1);
	printf("FUNCTION:\n");
	printf("x = a*sin(3*t)*cos(t)\n");
	printf("y = a*cos(3*t)*sin(t)\nt from 0 to 2*PI\n");
	printf("a=%.2f",a);
	x0=0;
	y0=0;
	dt=0.01;
	t0=0;
	while(t0<=2*PI){
		while(1){
			int L;
			t=t0+dt;
			x=a*sin(3*t)*cos(t);
			y=a*cos(3*t)*sin(t);
			L=myLine(x0,y0,x,y);
			if(L==0 || L==4)break;
			if(L==1)dt=dt*1.3;
			if(L==2)dt=dt*0.8;
		}
		t0=t;
		x0=x;
		y0=y;
	}
	myclosegraph();
}

void hw2(){
	float a,l,t0,t,dt,x0,y0,r0,x,y,r;
	printf("The function is:\nr = a*theta\n");
	printf("Please input the constant a in the function:\n");
	a=0;
	while(a<=0){
		scanf("%f",&a);
	}
	printf("Default X axis(50*a)?(Y/n)\n");
	if(getch()=='n'){
		printf("Please input the length of X axis:\n");
		l=0;
		while(l<=0){
			scanf("%f",&l);
		}
	}
	else
	{
		l = 50*a;
	}
	xmin=-l/2;
	ymin=-l/2*H/W;
	xmax=l/2;
	ymax=l/2*H/W;
	l=sqrt(xmax*xmax+ymax*ymax);
	myopengraph(2);
	printf("FUNCTION:\n");
	printf("r = a*theta\n");
	printf("a=%.2f",a);
	x0=0;
	y0=0;
	dt=0.01;
	t0=0;
	r0=0;
	while(r0<=l){
		while(1){
			int L;
			t=t0+dt;
			r=a*t;
			x=r*cos(t);
			y=r*sin(t);
			L=myLine(x0,y0,x,y);
			if(L==0 || L==4)break;
			if(L==1)dt=dt*1.3;
			if(L==2)dt=dt*0.8;
		}
		t0=t;
		x0=x;
		y0=y;
		r0=r;
	}
	myclosegraph();
}

void hw3(){
	float a,t0,t,dt,x0,y0,r0,x,y,r;
	printf("The function is:\nr = a*(1-cos(theta))\n");
	printf("Please input the constant a in the function:\n");
	a=0;
	while(a<=0){
		scanf("%f",&a);
	}
	xmin=-2.2*a;
	ymin=-1.5*a;
	xmax=0.5*a;
	ymax=1.5*a;
	myopengraph(3);
	printf("FUNCTION:\n");
	printf("r = a*theta\n");
	printf("a=%.2f",a);
	x0=0;
	y0=0;
	dt=0.01;
	t0=0;
	r0=0;
	while(t0<=2*PI){
		while(1){
			int L;
			t=t0+dt;
			r=a*(1-cos(t));
			x=r*cos(t);
			y=r*sin(t);
			L=myLine(x0,y0,x,y);
			if(L==0 || L==4)break;
			if(L==1)dt=dt*1.3;
			if(L==2)dt=dt*0.8;
		}
		t0=t;
		x0=x;
		y0=y;
		r0=r;
	}
	myclosegraph();
}

void hw4(){
	float a,l,t0,t,dt,x0,y0,x,y;
	printf("The function is:\nx = a*(t-sin(t))\ny = a(1-cos(t))\n");
	printf("Please input the constant a in the function:\n");
	a=0;
	while(a<=0){
		scanf("%f",&a);
	}
	printf("Default X axis(30*a)?(Y/n)\n");
	if(getch()=='n'){
		printf("Please input the length of X axis:\n");
		l=0;
		while(l<=0){
			scanf("%f",&l);
		}
	}
	xmin=-l/2;
	ymin=-0.2;
	xmax=l/2;
	ymax=2*a+0.2;
	myopengraph(4);
	printf("FUNCTION:\n");
	printf("x = a*(t-sin(t))\ny = a(1-cos(t))\n");
	printf("a=%.2f",a);
	x0=0;
	y0=0;
	dt=0.01;
	t0=0;
	while(x0<=xmax){
		while(1){
			int L;
			t=t0+dt;
			x=a*(t-sin(t));
			y=a*(1-cos(t));
			L=myLine(x0,y0,x,y);
			if(L==0 || L==4)break;
			if(L==1)dt=dt*1.3;
			if(L==2)dt=dt*0.8;
		}
		t0=t;
		x0=x;
		y0=y;
	}
	x0=0;
	y0=0;
	dt=-0.01;
	t0=0;
	while(x0>=xmin){
		while(1){
			int L;
			t=t0+dt;
			x=a*(t-sin(t));
			y=a*(1-cos(t));
			L=myLine(x0,y0,x,y);
			if(L==0 || L==4)break;
			if(L==1)dt=dt*1.3;
			if(L==2)dt=dt*0.8;
		}
		t0=t;
		x0=x;
		y0=y;
	}
	myclosegraph();
}

void hw5(){
	float a,l,t0,t,dt,x0,y0,r0,x,y,r;
	printf("The function is:\nx = a*(cos(t)+t*sin(t))\ny = a*(sin(t)-t*cos(t))\n");
	printf("Please input the constant a in the function:\n");
	a=0;
	while(a<=0){
		scanf("%f",&a);
	}
	printf("Default X axis(50*a)?(Y/n)\n");
	if(getch()=='n'){
		printf("Please input the length of X axis:\n");
		l=0;
		while(l<=0){
			scanf("%f",&l);
		}
	}
	else
	{
		l = 50*a;
	}
	xmin=-l/2;
	ymin=-l/2*H/W;
	xmax=l/2;
	ymax=l/2*H/W;
	l=sqrt(xmax*xmax+ymax*ymax);
	myopengraph(5);
	printf("FUNCTION:\n");
	printf("x = a*(cos(t)+t*sin(t))\ny = a*(sin(t)-t*cos(t))\n");
	printf("a=%.2f",a);
	x0=0;
	y0=0;
	dt=0.01;
	t0=0;
	r0=0;
	while(r0<=l){
		while(1){
			int L;
			t=t0+dt;
			x = a*(cos(t)+t*sin(t));
			y = a*(sin(t)-t*cos(t));
			r = sqrt(x*x+y*y);
			L=myLine(x0,y0,x,y);
			if(L==0 || L==4)break;
			if(L==1)dt=dt*1.3;
			if(L==2)dt=dt*0.8;
		}
		t0=t;
		x0=x;
		y0=y;
		r0=r;
	}
	myclosegraph();
}

int main(void)
{
	while(1){
		printf("Input 0 to EXIT the program.\nInput the order of homework(1-5):\n");
		switch (getch())
		{
			case '1':
				hw1();
				break;
			case '2':
				hw2();
				break;
			case '3':
				hw3();
				break;
			case '4':
				hw4();
				break;
			case '5':
				hw5();
				break;
			case '0':
				myexit();
				break;
			default:
				break;
		}
	}
	return 0;
}