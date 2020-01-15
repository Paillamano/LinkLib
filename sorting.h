//SOLO ALGORITMOS DE ORDENAMIENTO

//PROTOTIPADO
int partition_double(double list[], int low, int high);
void quicksort_double(double list[],int low, int high);
//FIN PROTOTIPADO

void quicksort_double(double list[],int low, int high)//primera y ultima posicion
{
	if(low < high)
	{
		int ip = partition_double(list,low,high);
		quicksort_double(list, low, ip-1);
		quicksort_double(list, ip + 1, high);
	}
}

int partition_double(double list[], int low, int high)
{
	double pivot = list[high];
	int i = (low - 1);
	for(int j = low; j<= high-1;j++){
		if(list[j] < pivot){
			i++;
			swap(list,i,j);
		}
	}
	swap(list,i+1,high);
	return (i+1);
}

