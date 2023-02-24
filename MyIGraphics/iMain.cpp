#include "iGraphics.h"
#include<math.h>
#include<mmsystem.h>

FILE *fp;
FILE *fp2;
FILE *savefile;
double xc1[20];
double yc1[20];
double distance[20];
int mode=1,mode2=2,flag=0,ist1=0,mode3=0;
double xa,ya,xb,yb,xa2,ya2,lineshow=1;
double gk1x=111,gk2x=1190,gk1y=330,gk2y=330,gkmv=0;
double pi=3.1416;
time_t t,t1,t2;
int r,k=0,kk,ll=1,serial=0;
double m,n;
double theta;
char team1[25];
char team2[25];
char times[5];
char goals[10]="0 - 0";
double minu=0,sec=0;
int brag=0,argg=0;
int teamnumber1,teamnumber2,stadiumnum;
char stadium[60];
char shortname1[60];
char shortname2[60];
char teamname[5][50]={"A R G E N T I N A","B R A Z I L", "F R A N C E","S P A I N"};

struct filedata
{
    int serial;
    double ballpos[2];
    double playerposx[20];
    double playerposy[20];
};

void drawplayers();
void timeshow();
void goalkeepermove();
void ornitechangeofplayer();
int dd=0;
/*
	function iDraw() is called again and again by the system.

*/
void initializeagain()
{

    brag=0;
    argg=0;
    minu=0;
    sec=0;
    k=0;
    kk=-1;
    mode2=2;
    mode3=0;
    flag=0;
    ist1=0;
    gk1x=111;
    gk2x=1190;
    gk1y=330;
    gk2y=330;
    gkmv=0;
    ll=1;
    serial=0;
    xa=gk1x;
    ya=gk1y;
    xb=xa+50;
    yb=gk1y;
    goals[0]='0';
    goals[4]='0';
    m=((yb-ya)/(xb-xa));
    theta=atan(m);
    struct filedata file5[5];
    remove("replay2.txt");
	iSetTimer(33,timeshow);
	iSetTimer(100,goalkeepermove);
    iPauseTimer(4);
}
void gameover()
{
    mode=6;

}


void timeshow()
{
    if(sec==59)
        {
        minu++;
        sec=-1;
    }
    sec++;
    times[0]=(minu/10)+48;
    times[1]=((int)minu%10)+48;
    times[2]=':';
    times[3]=(sec/10)+48;
    times[4]=((int)sec%10)+48;
    times[5]=0;
    if(minu==90)
    {
        gameover();
    }

}

void savedata()
{

    int p;
    savefile=fopen("savedfile.txt","w+");
    fprintf(savefile,"%lf %lf\n",xa,ya);
    fprintf(savefile,"%lf %lf\n",minu,sec);
    fprintf(savefile,"%d %d\n",brag,argg);
    fprintf(savefile,"%d %d\n",teamnumber1,teamnumber2);
    fprintf(savefile,"%d\n",stadiumnum);
    for(p=0;p<20;p++)
    {
        fprintf(savefile,"%lf %lf\n",xc1[p],yc1[p]);
    }
    fclose(savefile);


}

void loadgame()
{
    int p;
    iResumeTimer(4);
    mode3=1;
    savefile=fopen("savedfile.txt","r");
    fscanf(savefile,"%lf %lf",&xa,&ya);
    xb=xa+30;
    yb=ya+40;
    k=20;
    ll=0;
    fscanf(savefile,"%lf %lf",&minu,&sec);
    times[0]=(minu/10)+48;
    times[1]=((int)minu%10)+48;
    times[2]=':';
    times[3]=(sec/10)+48;
    times[4]=((int)sec%10)+48;
    times[5]=0;
    iResumeTimer(0);
    fscanf(savefile,"%d %d",&brag,&argg);
    fscanf(savefile,"%d %d\n",&teamnumber1,&teamnumber2);
    fscanf(savefile,"%d\n",&stadiumnum);
                     stadium[0]=stadiumnum+48;
                     stadium[1]='.';
                     stadium[2]='b';
                     stadium[3]='m';
                     stadium[4]='p';
                     stadium[5]=0;

                     team1[0]=teamnumber1+48;
                     team1[1]='p';
                     team1[2]='.';
                     team1[3]='b';
                     team1[4]='m';
                     team1[5]='p';
                     team1[6]=0;

                     team2[0]=teamnumber2+48;
                     team2[1]='p';
                     team2[2]='.';
                     team2[3]='b';
                     team2[4]='m';
                     team2[5]='p';
                     team2[6]=0;
    if(teamnumber1==1){
        shortname1[0]='A';
        shortname1[1]='R';
        shortname1[2]='G';
        shortname1[3]=0;
    }
    else if(teamnumber1==2){
        shortname1[0]='B';
        shortname1[1]='R';
        shortname1[2]='A';
        shortname1[3]=0;
    }
    else if(teamnumber1==3){
        shortname1[0]='F';
        shortname1[1]='R';
        shortname1[2]='A';
        shortname1[3]=0;
    }
    else if(teamnumber1==4){
        shortname1[0]='E';
        shortname1[1]='S';
        shortname1[2]='P';
        shortname1[3]=0;
    }
    if(teamnumber2==1){
        shortname2[0]='A';
        shortname2[1]='R';
        shortname2[2]='G';
        shortname2[3]=0;
    }
    else if(teamnumber2==2){
        shortname2[0]='B';
        shortname2[1]='R';
        shortname2[2]='A';
        shortname2[3]=0;
    }
    else if(teamnumber2==3){
        shortname2[0]='F';
        shortname2[1]='R';
        shortname2[2]='A';
        shortname2[3]=0;
    }
    else if(teamnumber2==4){
        shortname2[0]='E';
        shortname2[1]='S';
        shortname2[2]='P';
        shortname2[3]=0;
    }


    for(p=0;p<20;p++)
    {
        fscanf(savefile,"%lf %lf",&xc1[p],&yc1[p]);
    }
    goals[0]=brag+48;
    goals[1]=' ';
    goals[2]='-';
    goals[3]=' ';
    goals[4]=argg+48;
    fclose(savefile);


}

int goalkeepersave(){
    int distance;
    distance=pow((pow(((xa+15)-gk1x),2)+pow((ya-gk1y),2)),.5);
    if(distance<=13 && !ll && dd){
        ll=1;
        dd=0;
        return 1;
    }
    distance=pow((pow(((xa+15)-gk2x),2)+pow((ya-gk2y),2)),.5);
    if(distance<=13 && !ll && dd){
        ll=1;
        dd=0;
        return 2;
    }
    return 0;

}


int goalcheck()
{
    if(xa<=84-16 && (ya<433 && ya>367))
        {
        argg++;
        goals[0]=brag+48;
        goals[1]=' ';
        goals[2]='-';
        goals[3]=' ';
        goals[4]=argg+48;
        return 1;
    }

    if(xa>=1200 && (ya<433 && ya>367))
        {
        brag++;
        goals[0]=brag+48;
        goals[1]=' ';
        goals[2]='-';
        goals[3]=' ';
        goals[4]=argg+48;
        return 1;
    }
    return 0;

}
void goalkeepermove()
{
    if(k==20)
        {
        if(gkmv)
        {
            gk1y-=3;
            gk2y-=3;
            if(ll)
             {
                ya-=3;
                yb-=3;
            }
        }
        else
        {
            gk1y+=3;
            gk2y+=3;
            if(ll)
            {
                ya+=3;
                yb+=3;
            }
        }
        if(gk1y>=470)
        {
            gkmv=1;
        }
        else if(gk1y<=330)
        {
            gkmv=0;
        }
    }


}
void calculatedistance()
{
    int i;
    for(i=0;i<20;i++)
    {
        distance[i]=(pow((xc1[i]-xa),2)+pow((yc1[i]-ya),2));
    }


}
void moveball()
{
    iResumeTimer(3);
}
void moveplayer()
{
    dd=1;
    int p;
    int a=0,b=0;
    fp=fopen("replay.txt","a+");
    fp2=fopen("replay2.txt","a+");
    fprintf(fp2,"%lf %lf ",xa,ya);

    for(p=0;p<20;p++)
        {
        fprintf(fp,"%lf %lf\n",xc1[p],yc1[p]);
    }

    serial++;
    fclose(fp);
    fclose(fp2);
    int i,mini,j=0;
    calculatedistance();
    mini=distance[0];
    for(i=0;i<20;i++)
        {
        if(distance[i]<=mini)
        {
            mini=distance[i];
            j=i;
        }
    }
    kk=j;
    iResumeTimer(2);
    //xc1[j]=xa;
    //yc1[j]=ya;
}
void ornitechangeofball()
{

    int a=1,gksv;
    double ocp,cx,cy,mm;
    if((int)xa2==(int)xa && ya2>ya)
        {
            cx=0;
            cy=3.0;


    }
    else if((int)xa2==(int)xa && ya2<ya)
        {
            cx=0;
            cy=-3.0;

    }
    else if(xa2<xa && (int)ya2==(int)ya)
        {
            cx=-3.0;
            cy=0;



    }
    else if(xa2>xa && (int)ya2==(int)ya)
        {
            cx=3.0;
            cy=0;

    }
    else if(xa2>xa && ya2<ya)
        {
            cx=3.0;
            cy=-3.0*((ya-ya2)/(xa2-xa));

    }
    else if(xa2>xa && ya2>ya)
        {
            cx=3.0;
            cy=3.0*((ya2-ya)/(xa2-xa));

    }
    else if(xa2<xa && ya2<ya)
        {
            cx=-3.0;
            cy=-3.0*((ya-ya2)/(xa-xa2));

    }
    else if(xa2<xa && ya2>ya)
        {
            cx=-3.0;
            cy=3.0*((ya2-ya)/(xa-xa2));

    }

    xa+=cx;
    ya+=cy;
    gksv=goalkeepersave();
    if(gksv){
        if(gksv==1){
            xa=gk1x;
            ya=gk1y;
            xb=xa+30;
            yb=ya+40;
        }
        else if(gksv==2){
            xa=gk2x-32;
            ya=gk2y;
            xb=xa-30;
            yb=ya+40;
        }

        a=0;
        lineshow=1;
        iPauseTimer(3);
    }
    if(goalcheck()){
        PlaySound("GOAL.wav",NULL,SND_LOOP);
        xa=650;
        ya=400;
        xb=685;
        yb=435;
        iPauseTimer(3);
        mode=4;
        }

    if(xa>1200)
    {
        xa=1200;
        xb=1230;
        if(a){
            moveplayer();
    }
        iPauseTimer(3);
    }
     else if(xa<84-16)
    {
        xa=84-16;
        xb=54;
        if(a){
            moveplayer();
    }
        iPauseTimer(3);
    }
     else if(ya>737)
    {
        ya=737;
        yb=777;
        if(a){
            moveplayer();
    }
        iPauseTimer(3);
    }
    else if(ya<63)
    {
        ya=63;
        yb=23;
        if(a){
            moveplayer();
    }
        iPauseTimer(3);
    }

    else if((xa<xa2+5 && xa>xa2-5) && (ya<ya2+5 && ya>ya2-5))
        {
        if(a){
            moveplayer();

    }
    iPauseTimer(3);
    }

}
void ornitechangeofplayer()
{
    double ocp,cx,cy,mm;
    if(xa<xc1[kk] && (int)ya==(int)yc1[kk])
        {
            cx=-1.5;
            cy=0;

    }
    else if(xa>xc1[kk] && (int)ya==(int)yc1[kk])
        {
            cx=1.5;
            cy=0;

    }
    else if((int)xa==(int)xc1[kk] && ya>yc1[kk])
        {
            cx=0;
            cy=1.5;

    }
    else if((int)xa==(int)xc1[kk] && ya<yc1[kk])
        {
            cx=0;
            cy=-1.5;

    }

    else if(xa>xc1[kk] && ya<yc1[kk])
        {
            cx=1.5;
            cy=-1.5*((yc1[kk]-ya)/(xa-xc1[kk]));

    }
    else if(xa>xc1[kk] && ya>yc1[kk])
        {
            cx=1.5;
            cy=1.5*((ya-yc1[kk])/(xa-xc1[kk]));

    }
    else if(xa<xc1[kk] && ya<yc1[kk])
        {
            cx=-1.5;
            cy=-1.5*((yc1[kk]-ya)/(xc1[kk]-xa));

    }
    else if(xa<xc1[kk] && ya>yc1[kk])
        {
            cx=-1.5;
            cy=1.5*((ya-yc1[kk])/(xc1[kk]-xa));

    }
    xc1[kk]+=cx;
    yc1[kk]+=cy;
    if((xc1[kk]<xa+5 && xc1[kk]>xa-5) && (yc1[kk]<ya+5 && yc1[kk]>ya-5))
        {
        xb=(xa+50*cos(theta));
        yb=(ya+50*sin(theta));
        lineshow=1;
        iPauseTimer(2);
    }

}

void drawfield()
{
    iFilledCircle(xa+15,ya,2,100);
    iSetColor(255,0,0);
    if(lineshow)
    {
    iLine(xa+15,ya,xb+15,yb);
    }
    iFilledCircle(xa+15,ya,5,100);
    iSetColor(0,204,102);
    iFilledCircle(gk2x,gk2y,13,100);
    iSetColor(102,102,255);
    iFilledCircle(gk1x,gk1y,13,100);
    iSetColor(178,102,255);
    iFilledRectangle(84,752,124,40);
    iSetColor(0,0,255);
    iFilledRectangle(208,752,247,40);
    iSetColor(0,0,0);
    iText(100,768, times,GLUT_BITMAP_HELVETICA_18);
    iText(235,768,shortname1,GLUT_BITMAP_HELVETICA_18);
    iText(390,768,shortname2,GLUT_BITMAP_HELVETICA_18);
    iSetColor(255,0,0);
    iText(310,768,goals,GLUT_BITMAP_HELVETICA_18);

}
void drawplayers()
{
    int i=0;
    iSetColor(255, 255, 0);
    if(k<10)
    {
        iSetColor(255,0,0);
        iText(300,400,"TURN FOR ",GLUT_BITMAP_HELVETICA_18);
        iText(400,400,teamname[teamnumber1-1],GLUT_BITMAP_HELVETICA_18);
    }
     for(i=0;i<k;i++)
        {

        iShowBMP(xc1[i],yc1[i],team1);
    }
    iSetColor(204,255,255);
    if(k<20 && k>9){
        iSetColor(0,0,255);
        iText(795,400,"TURN FOR ",GLUT_BITMAP_HELVETICA_18);
        iText(895,400,teamname[teamnumber2-1],GLUT_BITMAP_HELVETICA_18);
    }
    for(i=10;i<k;i++){

        iShowBMP(xc1[i],yc1[i],team2);
    }
    }


void drawreplayplayers()

{

    int p;
    double a,b;
    fp2=fopen("replay2.txt","r");
    for(p=0;p<serial-5;p++)
        {
        fscanf(fp2,"%lf %lf ",&a,&b);

    }

    fscanf(fp2,"%lf %lf ",&a,&b);
    iFilledCircle(a,b,5,100);

    fscanf(fp2,"%lf %lf ",&a,&b);
    iFilledCircle(a,b,5,100);

    fscanf(fp2,"%lf %lf ",&a,&b);
    iFilledCircle(a,b,5,100);

    fscanf(fp2,"%lf %lf ",&a,&b);
    iFilledCircle(a,b,5,100);


    fclose(fp2);


}



void iDraw()
 {

	//place your drawing codes here
	iClear();
	if(mode==1)
        {
        iShowBMP(0,0,"Start.bmp");

        iSetColor(255,0,0);
        iText(600,450,"NEW GAME",GLUT_BITMAP_HELVETICA_18);
        iText(600,400,"LOAD GAME",GLUT_BITMAP_HELVETICA_18);
        iText(600,350,"INSTRUCTIONS",GLUT_BITMAP_HELVETICA_18);
        iText(600,300,"CREDITS",GLUT_BITMAP_HELVETICA_18);
        iText(600,250,"QUIT",GLUT_BITMAP_HELVETICA_18);
	}

	else if(mode==2)
        {
        iShowBMP(0,0,stadium);
	    drawplayers();
        drawfield();
	}
	else if(mode==3){
        iShowBMP(0,0,"ins.bmp");
        iSetColor(0,0,0);
        iFilledRectangle(10,700,240,35);
        iSetColor(255,0,0);
        iText(30,710,"BACK TO MAIN MENU",GLUT_BITMAP_HELVETICA_18);
	}

     else if(mode==4)
        {
        drawfield();
        iShowBMP(0,0,stadium);
        drawreplayplayers();

     }

     else if(mode==5)
        {
        iShowBMP(0,0,"escape.bmp");
        iSetColor(0,0,0);
        iFilledRectangle(580,390,140,35);
        iFilledRectangle(580,340,150,35);
        iFilledRectangle(580,240,100,35);
        iFilledRectangle(580,290,240,35);
        iSetColor(255,0,0);
        iText(600,350,"SAVE GAME",GLUT_BITMAP_HELVETICA_18);
        iText(600,300,"BACK TO MAIN MENU",GLUT_BITMAP_HELVETICA_18);
        iText(600,400,"CONTINUE",GLUT_BITMAP_HELVETICA_18);
        iText(600,250,"QUIT",GLUT_BITMAP_HELVETICA_18);

     }

	else if(mode==6)
        {

            if(brag>argg)
                {
                iShowBMP(0,0,"win.bmp");
                iSetColor(0,0,0);
                iFilledRectangle(580,290,240,35);
                iFilledRectangle(580,240,100,35);
                iSetColor(255,0,0);
                iText(600,300,"BACK TO MAIN MENU",GLUT_BITMAP_HELVETICA_18);
                iText(600,250,"QUIT",GLUT_BITMAP_HELVETICA_18);
                iText(400,600,"GAME OVER !!!!",GLUT_BITMAP_HELVETICA_18);
                iText(400,550,teamname[teamnumber1-1],GLUT_BITMAP_HELVETICA_18);
                iText(500,520,"W O N  B Y ",GLUT_BITMAP_HELVETICA_18);
                iText(600,490,goals,GLUT_BITMAP_HELVETICA_18);
            }

            else if(argg>brag)
                {
                iShowBMP(0,0,"win.bmp");
                iSetColor(0,0,0);
                iFilledRectangle(580,290,240,35);
                iFilledRectangle(580,240,100,35);
                iSetColor(255,0,0);
                iText(600,300,"BACK TO MAIN MENU",GLUT_BITMAP_HELVETICA_18);
                iText(600,250,"QUIT",GLUT_BITMAP_HELVETICA_18);
                iText(400,600,"GAME OVER !!!!",GLUT_BITMAP_HELVETICA_18);
                iText(400,550,teamname[teamnumber2-1],GLUT_BITMAP_HELVETICA_18);
                iText(500,520,"W O N  B Y",GLUT_BITMAP_HELVETICA_18);
                iText(600,490,goals,GLUT_BITMAP_HELVETICA_18);
            }

            else
                {
                iShowBMP(0,0,"draw.bmp");
                iSetColor(0,0,0);
                iFilledRectangle(580,290,240,35);
                iFilledRectangle(580,240,100,35);
                iSetColor(255,0,0);
                iText(600,300,"BACK TO MAIN MENU",GLUT_BITMAP_HELVETICA_18);
                iText(600,250,"QUIT",GLUT_BITMAP_HELVETICA_18);
                iText(600,600,"GAME OVER !!!!",GLUT_BITMAP_HELVETICA_18);
                iText(600,550,"DRAW BY ",GLUT_BITMAP_HELVETICA_18);
                iText(700,550,goals,GLUT_BITMAP_HELVETICA_18);
            }
	}
	else if(mode==7){
        iShowBMP(0,0,"teamselect.bmp");
        iSetColor(0,0,0);
        iFilledRectangle(280,440,180,35);
        iFilledRectangle(280,390,130,35);
        iFilledRectangle(280,340,130,35);
        iFilledRectangle(280,290,110,35);
        iSetColor(255,0,0);
        iText(300,500,"SELECT FIRST TEAM !!",GLUT_BITMAP_HELVETICA_18);
        iText(300,450,"A R G E N T I N A",GLUT_BITMAP_HELVETICA_18);
        iText(300,400,"B R A Z I L",GLUT_BITMAP_HELVETICA_18);
        iText(300,350,"F R A N C E",GLUT_BITMAP_HELVETICA_18);
        iText(300,300,"S P A I N",GLUT_BITMAP_HELVETICA_18);

	}
	else if(mode==8){
        iShowBMP(0,0,"teamselect.bmp");
        iSetColor(0,0,0);
        iFilledRectangle(880,440,180,35);
        iFilledRectangle(880,390,130,35);
        iFilledRectangle(880,340,130,35);
        iFilledRectangle(880,290,110,35);
        iSetColor(255,0,0);
        iText(900,500,"SELECT SECOND TEAM !!",GLUT_BITMAP_HELVETICA_18);
        iText(900,450,"A R G E N T I N A",GLUT_BITMAP_HELVETICA_18);
        iText(900,400,"B R A Z I L",GLUT_BITMAP_HELVETICA_18);
        iText(900,350,"F R A N C E",GLUT_BITMAP_HELVETICA_18);
        iText(900,300,"S P A I N",GLUT_BITMAP_HELVETICA_18);

	}
	else if(mode==9){
        iShowBMP(0,0,"stadium_back.bmp");

        iText(550,700,"S E L E C T  S T A D I U M !!",GLUT_BITMAP_HELVETICA_18);
        iText(290,475,"M A R I O  A L B E R T O  K E M P E S",GLUT_BITMAP_HELVETICA_18);
        iText(720,475,"M A R A C A N A  S T A D I U M",GLUT_BITMAP_HELVETICA_18);
        iText(400,250,"C A M P  N O U",GLUT_BITMAP_HELVETICA_18);
        iText(750,250,"E T I H A D  S T A D I U M",GLUT_BITMAP_HELVETICA_18);
        iShowBMP(300,500,"arg_stadium.bmp");
        iShowBMP(700,500,"brazil_stadium.bmp");
        iShowBMP(300,300,"camp_nou.bmp");
        iShowBMP(700,300,"Etihad.bmp");

	}
	else if (mode==10)
    {
        iShowBMP(0,0,"credit.bmp");
        iSetColor(0,0,0);
        iFilledRectangle(10,740,240,35);
        iSetColor(255,0,0);
        iText(30,750,"BACK TO MAIN MENU",GLUT_BITMAP_HELVETICA_18);
    }
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my) {
	//printf("x = %d, y= %d\n",mx,my);
	//place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my)
 {
    int i;

    if(mode==1)
        {
         if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
          {
            if((mx>=600 && mx<=700)&& (my>=450 && my<=464))
            {
                mode=7;

                }
            else if((mx>=600 && mx<=745)&& (my>=350 && my<=364))
            {
                mode=3;
                mode3=1;
                iResumeTimer(4);
            }
            else if((mx>=600 && mx<=710)&& (my>=400 && my<=414))
                 {
                  loadgame();
                  mode=2;
                  mode2=3;
                 }
             if((mx>=600 && mx<=680)&& (my>=300 && my<=320))
            {
                mode=10;

                }
            else if((mx>=600 && mx<=645)&& (my>=250 && my<=264))
                 {
                     exit(0);

                 }
         }


    }
    if (mode2==2 && mode==2)
        {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
		//printf("x = %d, y= %d\n",mx,my);
            xc1[k]=mx;
            yc1[k]=my;
            k++;
            if(k==20)
            {
            mode2=3;
            iResumeTimer(0);
            }
	}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        {
		//place your codes here

	}
	if(mode==3){
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
            if((mx>=10 && mx<=250)&& (my>=700 && my<=735)){
                mode=1;
            }
        }
	}
	if(mode==4)
        {
        	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        	{
                mode=2;
                moveplayer();
                remove("replay2.txt");
                serial=0;
        	}

	}

    if(mode==5)
        {
         if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
          {
            if((mx>=600 && mx<=700)&& (my>=400 && my<=414))
            {
                mode=2;
                iResumeTimer(0);
                mode3=1;
                iResumeTimer(4);
                }
            else if((mx>=600 && mx<=710)&& (my>=350 && my<=364))
            {
                    savedata();
            }
            else if((mx>=600 && mx<=800)&& (my>=300 && my<=314))
                 {
                     mode=1;
                     initializeagain();

                 }
            else if((mx>=600 && mx<=650)&& (my>=250 && my<=264))
                 {
                     exit(0);

                 }
         }


    }
      if(mode==6)
        {
         if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
          {
            if((mx>=600 && mx<=800)&& (my>=300 && my<=314))
                 {
                     mode=1;
                     initializeagain();

                 }
            else if((mx>=600 && mx<=650)&& (my>=250 && my<=264))
                 {
                     exit(0);

                 }
         }


    }
    if(mode==7){
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
          {
            if((mx>=280 && mx<=460)&& (my>=440 && my<=475))
                 {
                     team1[0]='1';
                     team1[1]='p';
                     team1[2]='.';
                     team1[3]='b';
                     team1[4]='m';
                     team1[5]='p';
                     team1[6]=0;
                     shortname1[0]='A';
                     shortname1[1]='R';
                     shortname1[2]='G';
                     shortname1[3]=0;
                     teamnumber1=1;
                     mode=8;

                 }
            else if((mx>=280 && mx<=410)&& (my>=390 && my<=425))
                 {
                     team1[0]='2';
                     team1[1]='p';
                     team1[2]='.';
                     team1[3]='b';
                     team1[4]='m';
                     team1[5]='p';
                     team1[6]=0;
                     shortname1[0]='B';
                     shortname1[1]='R';
                     shortname1[2]='A';
                     shortname1[3]=0;
                     teamnumber1=2;
                     mode=8;

                 }
            else if((mx>=280 && mx<=410)&& (my>=340 && my<=375))
                 {
                     team1[0]='3';
                     team1[1]='p';
                     team1[2]='.';
                     team1[3]='b';
                     team1[4]='m';
                     team1[5]='p';
                     team1[6]=0;
                     shortname1[0]='F';
                     shortname1[1]='R';
                     shortname1[2]='A';
                     shortname1[3]=0;
                     teamnumber1=3;
                     mode=8;

                 }
            else if((mx>=280 && mx<=390)&& (my>=290 && my<=325))
                 {
                     team1[0]='4';
                     team1[1]='p';
                     team1[2]='.';
                     team1[3]='b';
                     team1[4]='m';
                     team1[5]='p';
                     team1[6]=0;
                     shortname1[0]='E';
                     shortname1[1]='S';
                     shortname1[2]='P';
                     shortname1[3]=0;
                     teamnumber1=4;
                     mode=8;

                 }

          }
    }
   if(mode==8){
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
          {
            if((mx>=880 && mx<=1060)&& (my>=440 && my<=475))
                 {
                     team2[0]='1';
                     team2[1]='q';
                     team2[2]='.';
                     team2[3]='b';
                     team2[4]='m';
                     team2[5]='p';
                     team2[6]=0;
                     shortname2[0]='A';
                     shortname2[1]='R';
                     shortname2[2]='G';
                     shortname2[3]=0;
                     teamnumber2=1;
                     mode=9;

                 }
            else if((mx>=880 && mx<=1010)&& (my>=390 && my<=425))
                 {
                     team2[0]='2';
                     team2[1]='q';
                     team2[2]='.';
                     team2[3]='b';
                     team2[4]='m';
                     team2[5]='p';
                     team2[6]=0;
                     shortname2[0]='B';
                     shortname2[1]='R';
                     shortname2[2]='A';
                     shortname2[3]=0;
                     teamnumber2=2;
                     mode=9;

                 }
            else if((mx>=880 && mx<=1010)&& (my>=340 && my<=375))
                 {
                     team2[0]='3';
                     team2[1]='q';
                     team2[2]='.';
                     team2[3]='b';
                     team2[4]='m';
                     team2[5]='p';
                     team2[6]=0;
                     shortname2[0]='F';
                     shortname2[1]='R';
                     shortname2[2]='A';
                     shortname2[3]=0;
                     teamnumber2=3;
                     mode=9;

                 }
            else if((mx>=880 && mx<=990)&& (my>=290 && my<=325))
                 {
                     team2[0]='4';
                     team2[1]='q';
                     team2[2]='.';
                     team2[3]='b';
                     team2[4]='m';
                     team2[5]='p';
                     team2[6]=0;
                     shortname2[0]='E';
                     shortname2[1]='S';
                     shortname2[2]='P';
                     shortname2[3]=0;
                     teamnumber2=4;
                     mode=9;

                 }

          }
    }
    else if(mode==9){

        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
            if((mx>=300 && mx<=600)&& (my>=500 && my<=658))
                 {
                     stadiumnum=1;
                     stadium[0]='1';
                     stadium[1]='.';
                     stadium[2]='b';
                     stadium[3]='m';
                     stadium[4]='p';
                     stadium[5]=0;
                     mode=2;
                     //k--;
                     mode3=1;
                     iResumeTimer(4);
                     iResumeTimer(5);
                 }
            else if((mx>=700 && mx<=1000)&& (my>=500 && my<=658))
                 {
                     stadiumnum=2;
                     stadium[0]='2';
                     stadium[1]='.';
                     stadium[2]='b';
                     stadium[3]='m';
                     stadium[4]='p';
                     stadium[5]=0;
                     mode=2;
                     //k--;
                     mode3=1;
                     iResumeTimer(4);
                     iResumeTimer(5);

                 }
            else if((mx>=300 && mx<=600)&& (my>=300 && my<=458))
                 {
                     stadiumnum=3;
                     stadium[0]='3';
                     stadium[1]='.';
                     stadium[2]='b';
                     stadium[3]='m';
                     stadium[4]='p';
                     stadium[5]=0;
                     mode=2;
                     //k--;
                     mode3=1;
                     iResumeTimer(4);
                     iResumeTimer(5);

                 }
            else if((mx>=700 && mx<=1000)&& (my>=300 && my<=458))
                 {
                     stadiumnum=4;
                     stadium[0]='4';
                     stadium[1]='.';
                     stadium[2]='b';
                     stadium[3]='m';
                     stadium[4]='p';
                     stadium[5]=0;
                     mode=2;
                     //k--;
                     mode3=1;
                     iResumeTimer(4);
                     iResumeTimer(5);

                 }

        }

    }
    if(mode==10)
    {
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            if((mx>=30 && mx<=270)&& (my>=740 && my<=775))
            {
                mode=1;
            }
        }
    }
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key) {
    char ch;

	if (key == 'a' || key == 'A')
        {
		t1=time(NULL);
		flag=1;
	}
	if ((key == 'd' || key == 'D') && flag)
	 {
        ll=0;
		t2=time(NULL);
        t=difftime(t2,t1);
        if(t==0) t=1;
        if(t>5) t=5;
        r=t*100;
        if(xb!=xa)
            {

            if(((yb-ya)>0)&&((xb-xa)<0))
                {
                n=((yb-ya))/((xa-xb));
                theta=pi-atan(n);
            }

            else if(((yb-ya)<0)&&((xb-xa)>0))
            {
                n=((ya-yb))/((xb-xa));
                theta=-atan(n);
            }

            else if(((yb-ya)>0)&&((xb-xa)>0))
            {
                n=((yb-ya))/((xb-xa));
                theta=atan(n);
            }

            else if(((yb-ya)<0)&&((xb-xa)<0))
                {
                n=((ya-yb))/((xa-xb));
                theta=-pi+atan(n);
            }
            }
        else
        {
            theta=(pi/2);
        }

        xa2=xa+(r*cos(theta));
        ya2=ya+(r*sin(theta));
        lineshow=0;
        flag=0;
        moveball();



	}
	if(key==27)
        {
        mode=5;
        iPauseTimer(0);
	}
	}
	//place your codes for other keys here


/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
	*/
void iSpecialKeyboard(unsigned char key) {

	if (key == GLUT_KEY_LEFT)
        {
        theta+=((2*3.14)/100);
		xb=xa+(50*cos(theta));
        yb=ya+(50*sin(theta));
	}
		if (key == GLUT_KEY_RIGHT)
		{
        theta-=((2*3.14)/100);
		xb=xa+(50*cos(theta));
        yb=ya+(50*sin(theta));
	}

	//place your codes for other keys here
}
void music()
{
    if(mode3==1 && mode==2)
    {
        PlaySound("music2.wav",NULL, SND_LOOP | SND_ASYNC);
    }

}

int main()
  {
    xa=gk1x;
    ya=gk1y;
    xb=xa+50;
    yb=gk1y;
    m=((yb-ya)/(xb-xa));
    theta=atan(m);
    struct filedata file5[5];
    remove("replay2.txt");
	//place your own initialization codes here.
	iSetTimer(33,timeshow);
	iPauseTimer(0);
	iSetTimer(100,goalkeepermove);
	iSetTimer(1,ornitechangeofplayer);
	iPauseTimer(2);
	iSetTimer(1,ornitechangeofball);
	iPauseTimer(3);
	iSetTimer(5000,music);
	iPauseTimer(4);
	iInitialize(1300,800, "FIFA 18");
	return 0;
}
