//SOLO ALGORITMOS DE ORDENAMIENTO

//PROTOTIPADO
int partition_double(double list[], int low, int high);
void quicksort_double(double list[],int low, int high);

void merge_double(double array[], int l, int m, int r);
void MergeSort_double(double array[],int l,int r);
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

void MergeSort_double(double array[],int l,int r){
	if(r>l){
		int m = (l+r)%2==0?(l+r)/2: (l+r+1)/2;
		MergeSort_double(array,l,m);
		MergeSort_double(array,m+1,r);
		merge_double(array, l,m,r);
	} 
}

void merge_double(double array[], int l, int m, int r){
	int i,j,k;
	int n1 = m-l+1;
	int n2 = r-m;
	double L[n1],R[n2];
	printf("Union de listas\n");
	for(i =0; i<n1;i++){
		L[i] = array[l+i];
	}
	for(j = 0; j<n2;j++){
		R[j] = array[m+1+j];
	}
	i=0;
	j=0;
	k=l;
	while(i<n1 && j<n2){
		if(L[i]<=R[j]){
			array[k] = L[i];
			i++;
		}else{
			array[k] = R[j];
			j++;
		}
		k++;
	}
	while(i<n1){
		array[k] = L[i];
		i++;
		k++;
	}
	while(j<n1){
		array[k] = R[j];
		j++;
		k++;
	}
}






