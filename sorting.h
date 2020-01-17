//SOLO ALGORITMOS DE ORDENAMIENTO

//PROTOTIPADO
int partition_double(double list[], int low, int high);
void quicksort_double(double list[],int low, int high);

void merge_double(double array[], int start, int m, int end);
void mergesort_double(double array[],int start,int end);
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

/*MergeSort(arr[], l,  r)
If r > l
     1. Find the middle point to divide the array into two halves:  
             middle m = (l+r)/2
     2. Call mergeSort for first half:   
             Call mergeSort(arr, l, m)
     3. Call mergeSort for second half:
             Call mergeSort(arr, m+1, r)
     4. Merge the two halves sorted in step 2 and 3:
             Call merge(arr, l, m, r) */

void mergesort_double(double array[],int start,int end){
	if(start < end ){
		int m = (start+end)%2==0?(start+end)/2: (start+1+end)/2;
		mergesort_double(array,start,m);
		mergesort_double(array,m+1,end);
		merge_double(array, start,m,end);
	} 
}

void merge_double(double array[], int start, int m, int end){
	int i = start, j = m+1, k=0;
	double temp_array[end-start+1];
	for(int c = start; c<=end; c++){
		if(i > m){
			temp_array[k++] = array[j++];
		}else if(j > end){
			temp_array[k++] = array[i++];
		}else if(array[i] < array[j]){
			temp_array[k++] = array[i++];
		}else{
			temp_array[k++] = array[j];
		}
	}
	for(int t = 0; t<k;t++){
		array[i++] = temp_array[t];
	}
}






