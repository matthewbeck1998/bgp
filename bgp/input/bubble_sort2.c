void bubbleSort(int arr[], int n);



int main()
{
  int arr[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  bubbleSort(arr, 10);

  return 0;
}

void bubbleSort(int arr[], int n)
{
  int i, j, temp;
  for (i = 0; i < n - 1; i++)
  {
    for (j = i + 1; j < n; j++)
    {
      if (arr[i] > arr[j])
      {
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }
}

void swap(int* i, int* j)
{
  int temp = *i;
  *i = *j;
  *j = temp;
}
