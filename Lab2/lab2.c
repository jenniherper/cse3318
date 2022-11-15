 // Name :: Jennifer Hernandez
 //ID :: 1001916869
 //Command to compile :: gcc [filename].c
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <limits.h>
 
 int parent( int i ) { return (i-1)/2; } //where i is the index of heap
 int leftchild( int i ) {return (2*i)+1; }
 int rightchild( int i ) {return (2*i) +2; }
 void insert( int a, int heap[], char fileEntry[][50], int* n )
 {
 	*(n) = (*n) + 1;
 	int i = *(n)-1;  //inserting new index at the end
 	heap[i] = a;
 	
 	
 	while( i > 0 && strcmp( fileEntry[ heap[ parent(i) ] ], fileEntry[ heap[i] ] ) > 0 )
 	{
 		int temp = heap[i];
   		heap[i] = heap[ parent(i) ];
    		heap[parent(i)] = temp;
    		i = parent(i);
 	}
 }
 void decrease( int i, int a, int heap[], char fileEntry[][50] )
 {
 	heap[i] = a;
 	while( i>0 && strcmp( fileEntry[ heap[ parent(i) ] ], fileEntry[ heap[i] ] ) > 0 )
 	{
 		int temp = heap[i];
   		heap[i] = heap[ parent(i) ];
    		heap[parent(i)] = temp;
    		i = parent(i);
 	}
 }
 void minHeapify( int i, int heap[], char fileEntry[][50], int* n ) //idk if stops at bottom of heap
 {
 	int left = leftchild(i); //index of heap
 	int right = rightchild(i);
 	int min = i;
 	if( left < *(n) &&  strcmp( fileEntry[ heap[left] ], fileEntry[ heap[min] ] ) < 0 )
 	{
 		min = left;
 	}
 	if (  right < *(n) &&  strcmp( fileEntry[ heap[right] ], fileEntry[ heap[min] ] ) < 0 )
 	{
 		min = right;
 	}
 	if ( min != i)
 	{
 		int temp = heap[i];
   		heap[i] = heap[min];
    		heap[min] = temp;
    		minHeapify( min, heap, fileEntry, n);
 	}
 }
int removeMin( int heap[], char fileEntry[][50], int* n )  //returns index fileEntry for min
 {
 	if( (*n) <= 0 )
 	{
 		return 100; //means we are done
 	}
 	else if ( *(n) == 1)
 	{
 		*(n) = (*n) - 1;
 		return heap[0];
 	}
 	
 	int min = heap[0];
 	
 	heap[0] = heap[*(n)-1];
 	*(n) = (*n) - 1;
 	minHeapify( 0 , heap, fileEntry, n ); //minHeapify( 0, heap, fileEntry, n );
 	return min;	
 }
 void delete( int i, int heap[], char fileEntry[][50], int* n )
 {
 	decrease( i, -1, heap, fileEntry ); //makes entry go to very top of heap
 	removeMin( heap, fileEntry, n ); //removes top of heap
 }
 
 int main(void)
{
	int n;
	FILE *inPtr = fopen( "in.dat", "r"); 	//opening in.dat
	fscanf( inPtr, "%d" , &n ); 		//getting n
	
	
	int heapn = 0;
	char fname[20] = {};
	char fileEntry[n][50]; 			//array of strings for file ptrs
	int heap[n];				//minheap array of index for file entry
	
	FILE *outPtr = fopen("out.dat", "w"); 	//making out.dat
	
	
	FILE** fptrs = (FILE**)malloc( n* sizeof(FILE*) );  //opening array of file ptrs
	
	
	for( int i = 0; i < n; i++ )
	{
		fscanf( inPtr, "%s" , fname );
		fptrs[i] = fopen( fname, "r" );
		if( fptrs[i] == NULL )
		{
			printf(" fptr[%d] is null ", i  );
		}
		
	}
	for( int i = 0; i < n; i++)		
	{
		fscanf( fptrs[i], "%s", fileEntry[i] ); 
		insert( i, heap, fileEntry, &heapn );
	}
	//while exit != num files, move all ptrs, adding to heap, checking if ptrs are at eof
	//put root in buffer string, incremement count
	//check if next root is == to buffer string, 
		//if yes = increment count, 
		//if no = write to out.dat, reset count
	int exit = 0;
	char buffer[50];
	int count = 0;
	int start = 1;     		
	while( exit != n ) 
	{
		int min = removeMin( heap, fileEntry, &heapn ); //returns i for fileEntry[i] of min string
		if( start == 1 )
		{
			strcpy( buffer, fileEntry[ min ] );	//buffer = fileEntry[ min ];
			count++;
			start = 0;
			//move ptrs if not eof
			fscanf( fptrs[min], "%s", fileEntry[ min ] );
			if( exit == n-1 )
			{
				fprintf( outPtr, "%s %d\n", buffer, count ); 
				exit++;
			}
			else if( feof( fptrs[min] ) )
			{
				exit++;
			}
			else
			{
				insert( min, heap, fileEntry, &heapn );
				minHeapify( 0 , heap, fileEntry, &heapn );
			}
		}
		else if( strcmp( buffer, fileEntry[ min ] ) == 0)
		{
			count++;
			//move ptrs if not eof
			fscanf( fptrs[min], "%s", fileEntry[ min ] );
			if( exit == n-1 )
			{
				fprintf( outPtr, "%s %d\n", buffer, count );  
				exit++;
			}
			else if( feof( fptrs[min] ) )
			{
				exit++;
			}
			else
			{
				insert( min, heap, fileEntry, &heapn );
				minHeapify( 0 , heap, fileEntry, &heapn );
			}
		}
		else
		{
			fprintf( outPtr, "%s %d\n", buffer, count ); 
			count = 0;
			strcpy( buffer, fileEntry[ min ] );
			count++;
			//move ptrs if not eof
			fscanf( fptrs[min], "%s", fileEntry[ min ] );
			if( exit == n-1 )
			{
				fprintf( outPtr, "%s %d\n", buffer, count );  
				exit++;
			}
			else if( feof( fptrs[min] ) )
			{
				exit++;
			}
			else
			{
				insert( min, heap, fileEntry, &heapn );
				minHeapify( 0 , heap, fileEntry, &heapn );
			}
		}	
	}
	
	//close all open file ptrs
	fclose( inPtr );
	fclose( outPtr );
	for( int i = 0; i < n; i++ )
	{
		fclose( fptrs[i] );
	}
}
