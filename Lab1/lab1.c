// Name :: Jennifer Hernandez
// ID :: 1001916869
// Command to compile :: gcc [filename].c

#include <stdio.h>
#include <stdlib.h>
int binSearchLast(int *a,int n,int key)
{
// Input: int array a[] with n elements in ascending order.
//        int key to find.
// Output: Returns subscript of the last a element <= key.
//         Returns -1 if key<a[0].
// Processing: Binary search.
  int low,high,mid;
  low=0;
  high=n-1;
// subscripts between low and high are in search range.
// size of range halves in each iteration.
// When low>high, low==high+1 and a[high]<=key and a[low]>key.
  while (low<=high)
  {
    mid=(low+high)/2;
    if (a[mid]<=key)
      low=mid+1;
    else
      high=mid-1;
  }
  return high;
}
int binSearchFirst(int *a,int n,int key)
// Input: int array a[] with n elements in ascending order.
//        int key to find.
// Output: Returns subscript of the first a element >= key.
//         Returns n if key>a[n-1].
// Processing: Binary search.
{
  int low,high,mid;
  low=0;
  high=n-1;
// Subscripts between low and high are in search range.
// Size of range halves in each iteration.
// When low>high, low==high+1 and a[high]<key and a[low]>=key.
  while (low<=high)
  {
    mid=(low+high)/2;
    if (a[mid]<key)
      low=mid+1;
    else
      high=mid-1;
  }
  return low;
}



int main( void )
{
	int n;  //num of values
	int input = 6; //command set to 1 so loop can start
	scanf( "%d", &n );  //first line of input is num values
	
	int* map = (int*)malloc( n* sizeof(int) );
	int* index = (int*)malloc( n* sizeof(int) );
	int* count = (int*)malloc( n*sizeof(int) );
	if( map == NULL )
	{
		printf("malloc error");
		return 0;
	}
	for( int i = 0; i < n; i++ )
	{
		map[i] = i;
		index[i] = i;
		count[i] = 0;
	}
	
	
	while( input != 0 )
	{
		scanf( "%d", &input );
		if( input == 1 )  //print counters in ascending index value order ( index, count ) pairs
		{
			printf("print by index\n");
			for ( int i = 0; i < n; i++ )
			{
				printf("%d %d\n", i, count[ map[i] ] );
			}
			printf("------------\n");
		}
		else if ( input == 2 ) //print counters in ascending counter value order as pairs
		{
			printf("print by count\n");
			for ( int i = 0; i < n; i++ )
			{
				printf("%d %d\n", index[i], count[i] );
			}
			printf("------------\n");
		}
		else if ( input == 3 ) //add one to specified counter
		{
			int counter;
			scanf( "%d", &counter ); //get specified counter
			// map[counter] is original index of counter we want to swap
			//count[ map[counter] ] gives the value of the specified counter 
			int i = binSearchLast( count, n, count[ map[counter] ] ); //gives us index of swap
			
			//save original values temporarily for swap
			int tempindex = index[i];
			int tempcount = count[i];
			int tempmap = map[ index[i] ];
			
			map[ index[i] ] = map[counter];
			index[i] = index[ map[counter] ];
			count[i] = count[ map[counter] ];
			
			index[ map[counter] ] = tempindex;
			count[ map[counter] ] = tempcount;
			map[counter] = tempmap;
			
			count[i] = count[i] + 1;
			
		}
		else if ( input == 4 ) //subtract one to specified counter
		{
			int counter;
			scanf( "%d", &counter ); //get specified counter
			// map[counter] is original index of counter we want to swap
			//count[ map[counter] ] gives the value of the specified counter 
			int i = binSearchFirst( count, n, count[ map[counter] ] ); //gives us index of swap
			
			//save original values temporarily for swap
			int tempindex = index[i];
			int tempcount = count[i];
			int tempmap = map[ index[i] ];
			
			map[ index[i] ] = map[counter];
			index[i] = index[ map[counter] ];
			count[i] = count[ map[counter] ];
			
			index[ map[counter] ] = tempindex;
			count[ map[counter] ] = tempcount;
			map[counter] = tempmap;
			
			count[i] = count[i] - 1;
		}
		else if ( input == 5 ) //determine # of counters with values between specified 
		{
			int countOne;
			scanf( "%d", &countOne );
			int countTwo;
			scanf( "%d", &countTwo );
			
			
			int i = binSearchFirst( count, n, countOne );
			int j = binSearchLast( count, n, countTwo );
			printf("%d counters valued between %d and %d\n", j-i + 1, countOne, countTwo );
		}
	}
} 







