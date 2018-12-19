void printInt(int x) {}
void printSpace() {}
void printNewline() {}

int factorial(int x)
{
    if (x == 0)
    {
        return 1;
    }

    return x * factorial(x - 1);
}

int main()
{
    int x = 5, y;
    y = factorial(x);
    printInt(y);
    return 0;
}
