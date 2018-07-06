#include <stdio.h>

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int partition(int *ar, int size)
{
	int wall = 0;
	int pivot = ar[size - 1];
	for (int i = 0; i < size; i++)
	{
		while(i < size && ar[i] > pivot)
			i++;
		if (ar[i] < pivot)
		{
			swap(&ar[wall], &ar[i]);
			wall++;
		}
	}
	swap(&ar[wall], &ar[size - 1]);
	return(wall);
}

void sorting(int *ar, int size)
{
	if (size < 2)
		return;
	int new_size = partition(ar, size);
	sorting(ar, new_size);
	sorting(ar + new_size + 1, size - new_size - 1);
}

int main(void)
{
	int ar[] = {5,1,0,6,30,29,17,4,2,15};
	printf("BEFORE SORTING:\n\n");
	int size = sizeof(ar) / 4;

	int i = 0;
	while (i < size)
	{
		printf("%i\n", ar[i]);
		i++;
	}

	sorting(ar, size);
	printf("\nSORTED:\n\n");
	
	i = 0;
	while (i < size)
	{
		printf("%i\n", ar[i]);
		i++;
	}
	return (0);
}