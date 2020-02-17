#include <graphics.h>
#include "windows.h"
#include <stdio.h>
#include <time.h>
#include <iostream>
#include "stdlib.h"
#include "math.h"


using namespace std;

#define width 15
#define high 15

struct pos
{
    int x;
    int y;
};

int thinkqizi[high][width];
double thinkqizivalue[high][width];
int qizi[high][width];


int playcolour;//当前下棋棋子颜色 1黑 2 白 0 空
int qizi_x,qizi_y; // 记录当前棋子坐标
int judgeplaycolor; // 判断输赢的一方
int win;    //棋局输赢状态
int mode;//模式 1人机 2玩家先 3 人机1 电脑先 3 人机2 玩家先 4 人机2 电脑先
int xiahao; // 玩家下完棋标志

void judge() //判断输赢
{
    int lianzishu;
    int x,y;
    lianzishu=0;
    x=qizi_x;
    y=qizi_y;
    while(qizi[y][x]==judgeplaycolor && judgeplaycolor!=0 && x>=0) //横
    {
        lianzishu++;
        x--;
    }
    x=qizi_x;
    y=qizi_y;
        while(qizi[y][x+1]==judgeplaycolor && judgeplaycolor!=0 && x+1<=15)
    {
        lianzishu++;
        x++;
    }

    if(lianzishu>=5)
    {
        if(judgeplaycolor==1)
        win=1;
        else if(judgeplaycolor==2)
        win=2;
    }
    else lianzishu=0;

    x=qizi_x;
    y=qizi_y;
    while(qizi[y][x]==judgeplaycolor && judgeplaycolor!=0 && y>=0) //纵
    {
        lianzishu++;
        y--;
    }
    x=qizi_x;
    y=qizi_y;
        while(qizi[y+1][x]==judgeplaycolor && judgeplaycolor!=0 && y+1<=15)
    {
        lianzishu++;
        y++;
    }

    if(lianzishu>=5)
    {
        if(judgeplaycolor==1)
        win=1;
        else if(judgeplaycolor==2)
        win=2;
    }
    else lianzishu=0;

    x=qizi_x;
    y=qizi_y;
    while(qizi[y][x]==judgeplaycolor && judgeplaycolor!=0 && y>=0 && x>=0) //左上+右下
    {
        lianzishu++;
        y--;
        x--;
    }
    x=qizi_x;
    y=qizi_y;
        while(qizi[y+1][x+1]==judgeplaycolor && judgeplaycolor!=0 && y+1<=15 && x+1<=15)
    {
        lianzishu++;
        y++;
        x++;
    }

    if(lianzishu>=5)
    {
        if(judgeplaycolor==1)
        win=1;
        else if(judgeplaycolor==2)
        win=2;
    }
    else lianzishu=0;


    x=qizi_x;
    y=qizi_y;
    while(qizi[y][x]==judgeplaycolor && judgeplaycolor!=0 && y<=15 && x>=0) //左下+右上
    {
        lianzishu++;
        y++;
        x--;
    }
    x=qizi_x;
    y=qizi_y;
    while(qizi[y-1][x+1]==judgeplaycolor && judgeplaycolor!=0 && y-1>=0 && x+1<=15)
    {
        lianzishu++;
        y--;
        x++;
    }

    if(lianzishu>=5)
    {
        if(judgeplaycolor==1)
        win=1;
        else if(judgeplaycolor==2)
        win=2;
    }
    else lianzishu=0;
}

int scan(pos point,int length,int dir,int qi[15][15]) //0左 1 右 3 上 4 下 5 左上 6 右下  7 左下  8 右上  看定长点的棋子
{
    pos place[8];

    place[0].x=0 , place[0].y=1;  place[1].x=0 , place[1].y=-1;  place[2].x=-1 , place[2].y=0;  place[3].x=1 , place[3].y=0;
    place[4].x=1 , place[4].y=1;  place[5].x=1 , place[5].y=-1;  place[6].x=-1 , place[6].y=1;  place[7].x=-1 , place[7].y=-1; //8个方向
    if((length*place[dir].x+point.x)<=14 && (length*place[dir].x+point.x)>=0 && (length*place[dir].y+point.y)<=14 && (length*place[dir].y+point.y)>=0)
        return qi[length*place[dir].y+point.y][length*place[dir].x+point.x];
    else  return 3;

}


int getpointvalue(pos point,int thinker,int qi[15][15])  //取点值
{
    int value=0;
    int opponent;

    thinker==1 ? opponent=2 : opponent=1;

    for(int i=0;i<8;i++)
    {
        if(scan(point,1,i,qi)== thinker && scan(point,2,i,qi)==  thinker && scan(point,3,i,qi)== thinker && scan(point,4,i,qi)== thinker   ) // *11110
            value+=70000;
        //if(scan(point,1,i,qi)== thinker && scan(point,2,i,qi)==  thinker && scan(point,3,i,qi)== thinker && scan(point,4,i,qi)== thinker  && scan(point,5,i,qi)== opponent) // *11112
           // value+=70000;
        if(scan(point,-1,i,qi)== thinker && scan(point,-2,i,qi)==  thinker && scan(point,1,i,qi)== thinker && scan(point,2,i,qi)== thinker ) // 11*11
            value+=70000;
        if(scan(point,-1,i,qi)== thinker && scan(point,1,i,qi)==  thinker && scan(point,2,i,qi)== thinker && scan(point,3,i,qi)== thinker ) // 1*111
            value+=70000;

        if(scan(point,1,i,qi)== thinker && scan(point,2,i,qi)==  thinker && scan(point,3,i,qi)== thinker && scan(point,4,i,qi)== 0 ) //*1110
            value+=30000;
        if(scan(point,-2,i,qi)== 0 && scan(point,-1,i,qi)==  thinker && scan(point,1,i,qi)== thinker && scan(point,2,i,qi)== thinker  && scan(point,3,i,qi)== 0) //01*110
            value+=30000;

        if(scan(point,-1,i,qi)== 0 && scan(point,1,i,qi)==  thinker && scan(point,2,i,qi)== thinker && scan(point,3,i,qi)== thinker  && scan(point,4,i,qi)== opponent) //0*1112
            value+=8000;

        if(scan(point,1,i,qi)== thinker && scan(point,2,i,qi)==  thinker && scan(point,3,i,qi)== 0) // *110
            value+=10000;
        if(scan(point,-4,i,qi)== 0 && scan(point,-3,i,qi)==  thinker && scan(point,-2,i,qi)== thinker && scan(point,-1,i,qi)== 0 && scan(point,1,i,qi)== 0)  // 0110*0
            value+=5000;

        if(scan(point,-1,i,qi)== thinker && scan(point,1,i,qi)==  0 && scan(point,2,i,qi)== 0 && scan(point,3,i,qi)== thinker) //1*001
            value+=10;

         value+=((scan(point,1,i,qi)== thinker) +(scan(point,1,i,qi)== opponent)) *5;


    }



    return value;
}

pos valuate(int thinker,int qi[15][15])  //遍历取最大值
{
    int max1=0;
    int max2=0;
    int value=0;
    int opponent;
    pos best;
    pos best1;
    pos best2;

    thinker==1 ? opponent=2 : opponent=1;

    for(int i=0;i<high;i++)
    {
        for(int j=0;j<width;j++)
        {
           if(qi[i][j]==0)
            {
                pos attack;
                attack.x=j;attack.y=i;
                value=getpointvalue(attack,thinker,qi);
                if(value>max1)
                {
                    max1=value;
                    best1.x=j;
                    best1.y=i;
                }

            }
        }

    }

    for(int i=0;i<high;i++)
    {
        for(int j=0;j<width;j++)
        {
            if(qizi[i][j]==0)
            {

                pos defence;
                defence.x=j;defence.y=i;
                value=getpointvalue(defence,opponent,qi);
                if(value>max2)
                {
                    max2=value;
                    best2.x=j;
                    best2.y=i;
                }

            }
        }
    }
    if(max1>=max2)
    {
        best=best1;
    }
    else best=best2;

    return best;
}


int distance(int x1, int y1, int x2, int y2)
{
	return (int)(sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))+.3);
}

void draw()
{
    for(int i=50;i<high*50+50;i=i+50)
        {
            line(50,i,15*50,i);
        }

    for(int j=50;j<width*50+50;j=j+50)
        {
            line(j,50,j,15*50);
        }
    for(int h=0;h<high;h++)
    {
        for(int w=0;w<width;w++)
            {
                if(qizi[h][w]==1)
                    pieslice((w+1)*50,(h+1)*50,0,360,20);
                if(qizi[h][w]==2)
                    {
                        setfillcolor(WHITE);
                        setcolor(WHITE);
                        pieslice((w+1)*50,(h+1)*50,0,360,20);
                        setfillcolor(BLACK);
                        setcolor(BLACK);
                    }
            }
    }
}

void Datainit()
{
    playcolour=1;
    judgeplaycolor=0;
    win=-1;
    for(int i=0;i<high;i++)
    {
        for(int j=0;j<width;j++)
        {
            qizi[i][j]=0;
        }
    }

}

void showup()
{

    setbkcolor(0xFCFC54);
    cleardevice();
    setlinewidth(3);
    setcolor(BLACK);
   if(win==-1)
    {
        setfont(20,0,"黑体");
        outtextrect(450,300,100,100,"双人模式");
        outtextrect(450,330,100,100,"人机模式");
   }

    if(win==0 && mode==1)
    {
        outtextrect(450,300,100,100,"难度一");
        outtextrect(450,330,100,100,"难度二");
    }

    else if(win==0 && mode!=0 && mode!=1)
    {
        draw();
        outtextrect(800,240,100,100,"玩家先手");
        outtextrect(800,270,100,100,"电脑先手");
        outtextrect(800,300,100,100,"返回主菜单");
        outtextrect(800,330,100,100,"重新开始");
    }
    else if(win==0 && mode==0)
    {
        draw();
        outtextrect(800,300,100,100,"返回主菜单");
        outtextrect(800,330,100,100,"重新开始");
    }
    else if(win==1)
    {
        draw();
        outtextxy(350,25,"黑方胜利!");
        outtextrect(800,300,100,100,"返回主菜单");
        outtextrect(800,330,100,100,"重新开始");
    }
    else if(win==2)
    {
        draw();
        outtextxy(350,25,"白方胜利！");
        outtextrect(800,300,100,100,"返回主菜单");
        outtextrect(800,330,100,100,"重新开始");
    }


}

void updatewithoutshubiao()
{
    judge();
    if(mode==2 && xiahao==1 && win==0)
    {
        pos judgeplace;
        judgeplace=valuate(2,qizi);
        qizi[judgeplace.y][judgeplace.x]=playcolour;
        judgeplaycolor=playcolour;
        qizi_x=judgeplace.x;
        qizi_y=judgeplace.y;
        if(playcolour==1)
        playcolour=2;
        else if(playcolour==2)
        playcolour=1;
        judge();
    }
    else if(mode==3 && xiahao==1 && win==0)
    {

        pos judgeplace;
        judgeplace=valuate(1,qizi);
        qizi[judgeplace.y][judgeplace.x]=playcolour;
        judgeplaycolor=playcolour;
        qizi_x=judgeplace.x;
        qizi_y=judgeplace.y;
        if(playcolour==1)
        playcolour=2;
        else if(playcolour==2)
        playcolour=1;
        judge();


    }
   else if((mode==4 || mode==5) && xiahao ==1 && win==0)
    {
        pos judgeplace;
        pos best;
        int thinker, oponent;
        double point_value=0;
        double maxvalue=0;

        if(playcolour==1)
        {
            thinker=1;
            oponent=2;
        }
        else if(playcolour==2)
        {
            thinker=2;
            oponent=1;
        }

        for(int a=0;a<15;a++)
        {
            for(int b=0;b<15;b++)
            {
                thinkqizi[a][b]=qizi[a][b];
            }
        }

        for(int i=0;i<15;i++)
        {
           for(int j=0;j<15;j++)
           {
            if(thinkqizi[i][j]==0)
              {

                pos point1;
                pos point_third;
                point1.x=j;
                point1.y=i;
                thinkqizivalue[i][j]=getpointvalue(point1,thinker,thinkqizi)+getpointvalue(point1,oponent,thinkqizi);
                thinkqizi[i][j]=playcolour;
                judgeplace=valuate(oponent,thinkqizi);
                thinkqizi[judgeplace.y][judgeplace.x]=oponent;

                for(int c=0;c<15;c++)
                {
                        for(int d=0;d<15;d++)
                            {
                                if(thinkqizi[c][d]==0)
                                  {

                                        pos point2;
                                        point2.x=d;
                                        point2.y=c;
                                        point_value=point_value+((getpointvalue(point2,2,thinkqizi))*0.00007-(getpointvalue(point2,2,thinkqizi))*0.00005);
                                  }
                            }

                }



                point_third=valuate(thinker,thinkqizi);
                thinkqizi[point_third.y][point_third.x]=thinker;


                for(int c=0;c<15;c++)
                {
                        for(int d=0;d<15;d++)
                            {
                                if(thinkqizi[c][d]==0)
                                  {

                                        pos point2;
                                        point2.x=d;
                                        point2.y=c;
                                        point_value=point_value+((getpointvalue(point2,2,thinkqizi))*0.00007-(getpointvalue(point2,2,thinkqizi))*0.00005);
                                  }
                            }

                }

                thinkqizivalue[i][j]=thinkqizivalue[i][j]+point_value;
                thinkqizi[i][j]=0;
                thinkqizi[judgeplace.y][judgeplace.x]=0;
                thinkqizi[point_third.y][point_third.x]=0;
           }
           }
        }


        for(int i=0;i<15;i++)
        {
            for(int j=0;j<15;j++)
           {
               if(thinkqizi[i][j]==0)
              {

               if(thinkqizivalue[i][j]>maxvalue)
                {
                    maxvalue=thinkqizivalue[i][j];
                    best.x=j;
                    best.y=i;
                }
              }
           }

        }
        qizi[best.y][best.x]=playcolour;
        judgeplaycolor=playcolour;
        qizi_x=best.x;
        qizi_y=best.y;
        if(playcolour==1)
        playcolour=2;
        else if(playcolour==2)
        playcolour=1;
        judge();



    }

}

void updatewithshubiao()
{

    int i,j;

    xiahao=0;
    mouse_msg mousem=getmouse();


    if(win==-1)
    {

        if(mousem.msg == mouse_msg_down)
            {

                if(mousem.x>=450 && mousem.x<=530 && mousem.y>=300 && mousem.y<=320)
                {

                    win=0;
                    mode=0;
                }
             else   if(mousem.x>=450 && mousem.x<=530 && mousem.y>=330 && mousem.y<=350)
                {

                    mode=1;
                    win=0;
                }

            }

    }

    else if(win==0 && mode==1)
    {
            if(mousem.msg == mouse_msg_down)
            {

                if(mousem.x>=450 && mousem.x<=530 && mousem.y>=300 && mousem.y<=320)
                {

                    win=0;
                    mode=2;
                }
              else  if(mousem.x>=450 && mousem.x<=530 && mousem.y>=330 && mousem.y<=350)
                {
                    win=0;
                    mode=4;

                }
            }
    }

        else  if(win==0 && mode!=1)
        {

            if(mousem.msg == mouse_msg_down)
            {

                for(i=0;i<high;i++)
                {
                    for(j=0;j<width;j++)
                    {
                        if(distance(mousem.x, mousem.y, (j+1)*50,(i+1)*50) <= 10)
                        {

                          if(qizi[i][j]==0)
                          {

                                qizi[i][j]=playcolour;
                                judgeplaycolor=playcolour;
                                xiahao=1;
                                qizi_y=i;
                                qizi_x=j;

                                if(playcolour==1)
                                playcolour=2;
                                else if(playcolour==2)
                                playcolour=1;
                          }


                       }
                    }
                }
                if(mousem.x>=800 && mousem.x<=900 && mousem.y>=300 && mousem.y<=320) // 返回主菜单
                      {
                        Datainit();

                      }
                else if(mousem.x>=800 && mousem.x<=900 && mousem.y>=330 && mousem.y<=350) //重新开始
                {
                    playcolour=1;
                    judgeplaycolor=0;
                    for(int i=0;i<high;i++)
                    {
                        for(int j=0;j<width;j++)
                        {
                            qizi[i][j]=0;
                        }
                    }
                    win=0;
                }
             else  if(mode!=0 && mode!=1)
               {

                 if(mousem.x>=800 && mousem.x<=900 && mousem.y>=240 && mousem.y<=260)  //玩家先手
                {
                    playcolour=1;
                    judgeplaycolor=0;
                    for(int i=0;i<high;i++)
                    {
                        for(int j=0;j<width;j++)
                        {
                            qizi[i][j]=0;
                        }
                    }

                    if(mode==3)
                    {
                        mode=2;
                    }
                    else if(mode==5)
                    {
                        mode=4;
                    }

                }
               else  if(mousem.x>=800 && mousem.x<=900 && mousem.y>=270 && mousem.y<=290) //电脑先手
                {
                    playcolour=1;
                    judgeplaycolor=0;
                    for(int i=0;i<high;i++)
                    {
                        for(int j=0;j<width;j++)
                        {
                            qizi[i][j]=0;
                        }
                    }
                    qizi[7][7]=1;
                    playcolour=2;
                    if(mode==2)
                    {
                        mode=3;
                    }
                   else if(mode==4)
                    {
                        mode=5;
                    }

                }
               }


            }




        }
        else if (win==1 || win==2)
        {
            if(mousem.msg == mouse_msg_down)
            {

            if(mousem.x>=800 && mousem.x<=900 && mousem.y>=300 && mousem.y<=320)
            Datainit();
            else if(mousem.x>=800 && mousem.x<=900 && mousem.y>=330 && mousem.y<=350)
            {
                Datainit();
                win=0;
            }
            }
        }


}



int main()
{


    Datainit();
    initgraph(1000, 800,INIT_RENDERMANUAL);
    setcaption("AI-M");
    setrendermode(RENDER_MANUAL);
    while(1)
    {
        showup();
        updatewithshubiao();
        updatewithoutshubiao();

    }



    return 0;
}
