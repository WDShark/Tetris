#include <graphics.h>
#include <conio.h>
#include "Tetris.h"
#include <math.h>
#define Width 640
#define Height 480
#define PI 3.14159
int main()
{
    Tetris tetris(262,622,133,853);
    tetris.play();



    //// ��ʼ����ͼ����
    //initgraph(640, 480, SHOWCONSOLE);
    ////������ʼ����
    //int center_x = Width / 2, center_y = Height / 2;
    ////�����յ�����
    //int secondEnd_x, secondEnd_y;
    ////�����յ�����
    //int minuteEnd_x, minuteEnd_y;
    ////ʱ���յ�����
    //int hourEnd_x, hourEnd_y;
    ////���볤��
    //int secondLength = Width / 4;
    ////���볤��
    //int minuteLength = Width / 5.5;
    ////ʱ�볤��
    //int hourLength = Width / 7;
    ////�����Ӧת���Ƕ�
    //float secondAngle = 0;
    ////�����Ӧת���Ƕ�
    //float minuteAngle = 0;
    ////ʱ���Ӧת���Ƕ�
    //float hourAngle = 0;
    ////��������洢ϵͳʱ��
    //SYSTEMTIME ti;
    //BeginBatchDraw();
    //while (1)
    //{
    //    setfillcolor(YELLOW);
    //    setlinestyle(PS_DASHDOTDOT, 5);
    //    setlinecolor(0x555555);
    //    circle(center_x, center_y, secondLength + 30);
    //    setcolor(0xAAAAAA);
    //    setlinestyle(PS_DOT | PS_ENDCAP_SQUARE, 2);
    //    circle(center_x, center_y, secondLength + 15);
    //    for (int i = 0; i < 12; i++)
    //    {
    //        int x = center_x + cos(i * 30.0 / 360 * 2 * PI) * (secondLength + 15.0);
    //        int y = center_y - sin(i * 30.0 / 360 * 2 * PI) * (secondLength + 15.0);
    //        fillcircle(x, y, 5);
    //    }
    //    GetLocalTime(&ti);
    //    secondAngle = (ti.wSecond / 60.0) * (2 * PI);
    //    minuteAngle = (ti.wMinute / 60.0) * (2 * PI);
    //    hourAngle = ((ti.wHour % 12) / 12.0) * (2 * PI) + (ti.wMinute / 60.0) * (2 * PI / 12.0);
    //    secondEnd_x = center_x + secondLength * sin(secondAngle);
    //    secondEnd_y = center_y - secondLength * cos(secondAngle);
    //    minuteEnd_x = center_x + minuteLength * sin(minuteAngle);
    //    minuteEnd_y = center_y - minuteLength * cos(minuteAngle);
    //    hourEnd_x = center_x + hourLength * sin(hourAngle);
    //    hourEnd_y = center_y - hourLength * cos(hourAngle);
    //    //������
    //    setlinestyle(PS_SOLID, 1);
    //    setcolor(WHITE);
    //    line(center_x, center_y, secondEnd_x, secondEnd_y);
    //    //������
    //    setlinestyle(PS_SOLID, 2);
    //    setcolor(GREEN);
    //    line(center_x, center_y, minuteEnd_x, minuteEnd_y);
    //    //��ʱ��
    //    setlinestyle(PS_SOLID, 5);
    //    setcolor(RED);
    //    line(center_x, center_y, hourEnd_x, hourEnd_y);
    //    FlushBatchDraw();
    //    setlinestyle(PS_SOLID, 1);
    //    setcolor(BLACK);
    //    line(center_x, center_y, secondEnd_x, secondEnd_y);
    //    setlinestyle(PS_SOLID, 2);
    //    setcolor(BLACK);
    //    line(center_x, center_y, minuteEnd_x, minuteEnd_y);
    //    setlinestyle(PS_SOLID, 5);
    //    setcolor(BLACK);
    //    line(center_x, center_y, hourEnd_x, hourEnd_y);
    //}
    //EndBatchDraw();
    //system("pause");
    //closegraph();
    //return 0;


    
}