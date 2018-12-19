printInt(int i)
{}
int main()
{
    int a[3][3][3];
    int i = 0, j = 0, k = 0, fill = 0;
    do{
        j = 0;
        while(j < 3)
        {
            k = 0;
            for(;k < 3;++k)
            {
                a[i][j][k] = ++fill;
            }
            ++j;
        }
    }while(++i < 3);

    i = j = k = 0;
    do{
        j = 0;
        while(j < 3)
        {
            for(k = 0;k < 3;++k)
            {
                if( a[i][j][k] % 3 != 0 )
                {
                    printInt( a[i][j][k] );
                }
            }
            ++j;
        }
    }while(++i < 3);
}