int main()
{
    int a[5];
    int b[2][2];
    int i, j;
    for (i = 0; i < 5; ++i)
    {
        a[i] = i;
    }

    for (i = 0; i < 2; ++i)
    {
        for (j = 0; j < 2; ++j)
        {
            b[i][j] = i + j;
        }
    }
    return 0;
}
