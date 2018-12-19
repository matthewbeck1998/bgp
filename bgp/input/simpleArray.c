void printInt(int x)
{

}

int main()
{
    int i;
    int a[5];
    for (i = 0; i < 5; ++i)
    {
        a[i] = i;
    }

    for (i = 0; i < 5; ++i)
    {
        printInt(a[i]);
    }
}
