void printInt(int x)
{

}

void printSpace()
{

}

void printNewline()
{

}

int main()
{
    int A[3][3];
    int B[3][3];
    int C[3][3];
    int i, j, k;

    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            A[i][j] = i + j;
            printInt(A[i][j]);
            printSpace();
        }
        printNewline();
    }
    printNewline();

    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            B[i][j] = A[i][j];
            printInt(B[i][j]);
            printSpace();
        }
        printNewline();
    }
    printNewline();

    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            C[i][j] = 0;
            for (k = 0; k < 3; ++k)
            {
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
            }
            printInt(C[i][j]);
            printSpace();
        }
        printNewline();
    }

    return 0;
}
