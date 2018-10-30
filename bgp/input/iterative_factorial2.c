int factorial(int n);

int main()
{
  int i;
  for (i = 0; i < 10; i++)
  {
    printf("Factorial of %d: %d\n", i, factorial(i));
  }
  return 0;
}

int factorial(int n)
{
  if (n < 0)
  {
    printf("Cannot take the negative of a factorial.\n");
    return -1;
  }
  else if (n == 0)
  {
    return 1;
  }
  else
  {
    int acc = 1;
    int i;
    for (i = 1; i <= n; i++)
    {
      acc *= i;
    }
    return acc;
  }
}
