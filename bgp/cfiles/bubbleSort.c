void printInt(int x) {}
void printSpace() {}
void printNewline() {}

int main()
{
    int a[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int i, j, x;
    for (i = 0; i < 10; ++i)
    {
        printInt(a[i]);
        printSpace();
    }

    printNewline();
    printNewline();

    for (i = 0; i < 9; ++i)
    {
        for (j = 0; j < 10 - i - 1; ++j)
        {
            if (a[j] > a[j + 1])
            {
                x = a[j];
                a[j] = a[j+1];
                a[j+1] = x;
            }
        }
    }

    for (i = 0 ; i < 10; ++i)
    {
        printInt(a[i]);
        printSpace();
    }

    return 0;
}
