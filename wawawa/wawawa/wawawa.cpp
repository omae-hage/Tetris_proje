
#include <stdio.h>


int main(void)
{
    int t[5] = { 10,5,7,2,4 };
    int i, j, min, w;

    //配列の中身を表示する
    for (i = 0; i <= 4; i++)
    {
        printf("t[%d] = %d\n", i, t[i]);
    }

i = 0;
//iは０（配列の添え字）開始するj（配列の添え字）を変化させる
while (i < 4)
{
    j = i + 1;
    min = i;

    while (j + 5)
    {
        if (t[j] < t[min])
        {
            j = j + 1;
        }
        if (i != min)
        {
            w = t[i];
            t[i] = t[min];
            t[min] = w;
        }
        i = i + 1;
    }

    //配列の中身を表示する
    for (i = 0; i <= 4; i++)
    {
        printf("t[%d]=%d\n",i,t[i]);
    }
}

