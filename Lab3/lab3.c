 // Name :: Jennifer Hernandez
 //ID :: 1001916869
 //Command to compile :: gcc [filename].c
 
 #include <stdio.h>
 #include <stdlib.h>
 
 int main( void )
 {
 	int n; 				//size of S list
 	int t1, t2; 			//target value one and two
 	scanf( "%d %d %d", &n, &t1, &t2 );
 	
 	int sumArr[n+1]; 			//arr of given S values	
 	sumArr[0] = 0;
 	for( int i = 1; i < n+1; i++)
 	{
 		scanf( "%d", &sumArr[i] );
 	}
 	
 	
 	//unsigned char costArr[t2+1][t1+1]; 	//t1 is collumn
 	
 	int *costArr[ t2+1 ];		//failed attempt to fix seg fault
 	for( int i = 0; i < t2+1; i++)
 	{
 		costArr[i] = calloc( t1+1, sizeof( int ) );
 	}
 	if ( costArr == NULL )
 	{
 		printf("calloc failed");
 	}
 	
 	
 	//filling 0 row & collumn
 	int exit =0;
 	costArr[0][0] = 0;
 	for(int i = 1; i < t1+1; i++)
 	{
 		int Sindex = 1;
 		while( exit != 1 ) // set exit =1 when C is set or Sindex is past n
 		{
 			int result = i - sumArr[ Sindex ];   //sindex = 2  i = 2
 			if( result >= 0 && costArr[0][result] < Sindex && costArr[0][result] >= 0 )
 			{
 				costArr[0][i] = Sindex;
 				exit = 1;
 			}
 			
 			Sindex++;
 			if( Sindex == n+1 && exit != 1 ) //might be n+1
 			{
 				exit = 1;
 				costArr[0][i] = n+1;
 			}
 		}
 		exit = 0;
 	}
 	for(int i = 1; i < t2+1; i++)
 	{ 
 		int Sindex = 1;
 		while( exit != 1 ) // set exit =1 when C is set or Sindex is past n
 		{
 			int result = i - sumArr[ Sindex ];
 			if( result >= 0 && costArr[result][0] < Sindex && costArr[result][0] >= 0)
 			{
 				costArr[i][0] = Sindex;
 				exit = 1;
 			}
 			
 			Sindex++;
 			if( Sindex == n+1 && exit != 1 ) 
 			{
 				exit = 1;
 				costArr[i][0] = n+1;
 			}
 		}
 		exit = 0;
 	}
 	
 	
 	//filling rest of costArr
 	for( int i = 1; i < t2+1; i++)
 	{
 		for( int j = 1; j < t1+1; j++)
 		{
 			int Sindex = 1;
 			while( exit != 1 ) //set exit to 1 if costArr is set or Sindex goes past n
 			{
 				int result = j - sumArr[ Sindex ];  // i=t2=1  j=t1=1   s=2  result =-1
 				if( result >=0 && costArr[i][result] < Sindex && costArr[i][result] >= 0 )
 				{
 					costArr[i][j] = Sindex;
 					exit =1;
 				}
 				if( exit != 1)
 				{
	 				result = i - sumArr[ Sindex ];
	 				if( result >= 0 && costArr[result][j] < Sindex && costArr[result][j] >= 0 )
	 				{
	 					costArr[i][j] = Sindex;
	 					exit =1;
	 				}
 				}
 				
 				Sindex++;
 				if( Sindex == n+1 && exit != 1)
	 			{
	 				exit = 1;
	 				costArr[i][j] = n+1;
	 			}
 			}
 			exit = 0;
 		}
 	}
 	
 	//print out costArr for viewing purposes
	/*
 	for( int i = 0; i < t2+1; i++)
 	{
 		for( int j = 0; j < t1+1; j++)
 		{
 			printf("%d ", costArr[i][j] );
 		}
 		printf("\n");
 	}
 	printf("\n\n");
	*/
 	
 	//backtrace
 	int noSol = 0;
 	int t1Solution[25];  	//will have Sindex values of solution
 	int t2Solution[25];
 	int t1ptr = t1;
 	int t2ptr = t2;
 	int t1n = 0;		//increase when add num to solution
 	int t2n = 0; 
 	if( costArr[t2][t1] != n+1 )
 	{
 		while( t1ptr > 0 || t2ptr > 0)
 		{
			while (exit != 1)
			{
				int result = 0;
				result = t1ptr - sumArr[ costArr[t2ptr][t1ptr] ];
				if( result >= 0 && costArr[t2ptr][result] < costArr[t2ptr][t1ptr] )
				{
					t1Solution[ t1n ] = costArr[t2ptr][t1ptr];
					t1n++;
					t1ptr = result;
					exit = 1;
				}
				if( exit != 1 )
				{
					result = t2ptr - sumArr[ costArr[t2ptr][t1ptr] ];
					if( result >= 0 && costArr[result][t1ptr] < costArr[t2ptr][t1ptr] )
					{
						t2Solution[ t2n ] = costArr[t2ptr][t1ptr];
						t2n++;
						t2ptr = result;
						exit = 1;
					}
				}
				
			}
			exit = 0;
		}
 	}
 	else if( costArr[t2][t1] == n+1 )
 	{
 		noSol = 1; //indicates there is no solution
 	}
 	
 	
 	printf("Targets are %d and %d\n", t1, t2);
 	printf("i\tS\n");
 	printf("-----------\n");
 	for( int i = 1; i < n+1; i++)
 	{
 		printf("%d\t%d\n", i, sumArr[i] );
 	}
 	if( noSol == 0 )
 	{
	 	printf("subsequence for %d:\n", t1);
	 	for( int i = t1n-1; i >= 0; i--)
	 	{
	 		printf("%d\t%d\n", t1Solution[i], sumArr[ t1Solution[i] ] );
	 	}
	 	printf("subsequence for %d:\n", t2);
	 	for( int i = t2n-1; i >= 0; i--)
	 	{
	 		printf("%d\t%d\n", t2Solution[i], sumArr[ t2Solution[i] ] );
	 	}
 	}
 	else
 	{
 		printf("No solution\n");
	}
 	
 	
 }
