void bubbleSort(int arr[], int n);
void swap(int* i, int* j);

int main()
{
  int arr[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  int i;
  bubbleSort(arr, 10);
  for (i = 0; i < 10; i++)
  {
    //printyboi
  }

  return 0;
}

void bubbleSort(int arr[], int n)
{
  int i, j;
  for (i = 0; i < n - 1; i++)
  {
    for (j = i + 1; j < n; j++)
    {
      if (arr[i] > arr[j])
      {
        swap(&arr[i], &arr[j]);
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
