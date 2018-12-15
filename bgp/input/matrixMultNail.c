int main()
{
    int A[3][3];
    int B[3][3];
    int C[3][3];
    int i, j, k;

    A[0][0] = 1;
    A[0][1] = 2;
    A[0][2] = 3;
    A[1][0] = 4;
    A[1][1] = 5;
    A[1][2] = 6;
    A[2][0] = 7;
    A[2][1] = 8;
    A[2][2] = 9;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            B[i][j] = A[i][j];
        }
    }

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            C[i][j] = 0;
            for (k = 0; k < 3; k++)
            {
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
            }
        }
    }

    return 0;
}
