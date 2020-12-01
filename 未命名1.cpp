#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <graphics.h>

#define WIDTH 960
#define HEIGHT 640
#define STR_SIZE 20
#define STR_NUM 128
#define STR_WIDTH 15


typedef struct Rain
{
    int x;
    int y;
    int speed;
    TCHAR str[STR_SIZE];
}Rain;
Rain rain[STR_NUM];

// �������һ���ַ�
char CreateCh()
{
    char ch = 0;
    int flag = rand() % 3; // 0~2
    if (flag == 0)
        ch = rand() % 26 + 'a'; // ����Сд��ĸa~z
    else if (flag == 1)
        ch = rand() % 26 + 'A'; // ������д��ĸA~Z
    else
        ch = rand() % 10 + '0'; // ��������0~9
    
    return ch;
}
// ��ʼ���ṹ���Ա
void InitRain()
{
    // ��ʼ���ַ���λ�ú��ٶ�
    for (int i = 0; i < STR_NUM; ++i)
    {
        rain[i].x = i*STR_WIDTH;
        rain[i].y = rand() % HEIGHT;
        rain[i].speed = rand() % 5 + 5;
    }
    // ��ȡ����ַ���������
    for (int i = 0; i < STR_NUM; i++)
    {
        for (int j = 0; j < STR_SIZE; j++)
        {
            rain[i].str[j] = CreateCh();
        }
    }
}
// �����������
void DrawRain()
{
    cleardevice();
    for (int i = 0; i < STR_NUM; i++)
    {
        for (int j = 0; j < STR_SIZE; j++)
        {
            outtextxy(rain[i].x, rain[i].y-STR_WIDTH*j, rain[i].str[j]);
            settextcolor(RGB(0, 255-j*13, 0));
        }
    }
}
// �ƶ��ַ�
void MoveRain()
{
    for (int i = 0; i < STR_NUM; i++)
    {
        rain[i].y += rain[i].speed;
        if (rain[i].y- STR_WIDTH*STR_SIZE > HEIGHT)
        {
            rain[i].y = 0;
        }
    }
}
// ����ı��ַ�
void ChangeCh()
{
    for (int i = 0; i < STR_NUM; i++)
    {
        rain[rand() % STR_NUM].str[rand() % STR_SIZE] = CreateCh();
    }
}
int main()
{
    srand((unsigned int)time(NULL)); // ��ʼ�����������
    initgraph(WIDTH, HEIGHT);
    InitRain();
    DWORD t1, t2;
    t1 = GetTickCount();
    t2 = t1;
    while (1)
    {
        BeginBatchDraw(); // ˫�������
        DrawRain();
        ChangeCh();
        if (t2 - t1 > 20)
        {
            MoveRain();
            t1 = t2;
        }
        t2 = GetTickCount();
        EndBatchDraw();
    }
    getchar();
    closegraph();
    return 0;
}
