int main()
{
    int a[25], i, j, x;
    for (i = 0; i < 25; ++i)
    {
        a[i] = 24 - i;
    }

    for (i = 0; i < 24; ++i)
    {
        for (j = 0; j < 24 - i - 1; ++j)
        {
            if (a[j] > a[j + 1])
            {
                x = a[j];
                a[j] = a[j+1];
                a[j+1] = x;
            }
        }
    }

    return 0;
}
