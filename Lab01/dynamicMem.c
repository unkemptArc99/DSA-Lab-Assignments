#include <stdio.h>
#include <stdlib.h>
//These are all function prototype
//---------------------------------------------------------------------------------------------------------------------------------------
int** create_D (int r, int c );
void display_D ( int **,int r,int c) ;
int** matadd_D ( int **, int **, int r, int c) ;
int** transpose_D (int **, int r, int c) ;
int** init_2d (int r, int c);
//Main Function
//---------------------------------------------------------------------------------------------------------------------------------------
int main( )
{
        int r,c;//rows and columns
	int **mat1a,**mat2a,**mat3a;//matrix pointers
	system ( "clear" ) ; //System command used to clear the screen
	printf ( "Please enter row and column : \n\n" ) ;
	scanf("%d %d",&r,&c);
	printf ( "Enter elements for first array:\n\n" ) ;
	mat1a=create_D (r,c) ; //This is function calling
        printf ( "Enter elements for second array:\n\n" ) ;
	mat2a=create_D (r,c) ;
        //Display the arrays
	printf ( "First Array:\n" ) ;
	display_D (mat1a,r,c) ;
	printf ( "Second Array:\n" ) ;
	display_D ( mat2a,r,c ) ;
        //Adding the arrays
        mat3a=matadd_D (mat1a,mat2a,r,c) ;
        printf ( "Printing Addition of both Array:\n" ) ;
	display_D ( mat3a,r,c ) ;
        //Transposing the arrays
        printf ( "Transposing and Printing First Array:\n" ) ;
	mat3a=transpose_D (mat1a,r,c) ;
        display_D ( mat3a,c,r ) ;
        printf ( "Transposing and Printing Second Array:\n" ) ;
	mat3a=transpose_D (mat2a,r,c) ;
        display_D ( mat3a,c,r ) ;
	return 0 ;
}
//These are all function definition
//---------------------------------------------------------------------------------------------------------------------------------------
int ** init_2d (int r, int c) //Initialize the matrix (allocate the memory for matrix)
{
	int **x, i, j;//x is a matrix pointer
        x = (int **) malloc(r * sizeof(int));// Allocating the space for r row pointers x[0],x[1],----x[r-1]

        for (i=0; i<r; i++)
         x[i] = (int *) malloc(c * sizeof(int));// Now Allocate space for c elements in each row and assign go its pointer 

return(x);
}
/* creates matrix mat */
int** create_D (int r, int c )
{
	int **x,i,j;
        x=init_2d(r,c);//Matrix Allocation
	for ( i = 0 ; i < r ; i++ )
	{
		for ( j = 0 ; j < c ; j++ )
		{
			printf ( "Enter the element: " ) ;
			scanf ( "%d", &x[i][j] ) ;// Polpulating Matrix 
		}
	}
	printf ( "\n" ) ;
        return(x);
}
void display_D ( int **mat,int r,int c)
{
	int i, j ;
	for ( i = 0 ; i < r ; i++ )
	{
		for ( j = 0 ; j < c ; j++ )
			printf ( "%d\t", mat[i][j] ) ;
		printf ( "\n" ) ;
	}
}
int ** matadd_D ( int **m1, int **m2, int r, int c)
{
	int **m3, i, j;
        m3=init_2d(r,c);
	for ( i = 0 ; i < r ; i++ )
	{
		for ( j = 0 ; j < c ; j++ )
			m3[i][j] = m1[i][j] + m2[i][j] ;
        }
return(m3);
}
/* obtains transpose of matrix m1 */
int ** transpose_D ( int **m1, int r, int c)
{
	int **m2, i, j;
        m2=init_2d(c,r);
	for ( i = 0 ; i < c ; i++ )
	{
		for ( j = 0 ; j < r ; j++ )
			m2[i][j] = m1[j][i] ;
	}
return(m2);
}
