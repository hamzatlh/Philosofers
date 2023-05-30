# include <pthread.h>
# include <stdio.h>

int a = 0;

void *Function( void* ignore )
{
    a = 1;
	return NULL;
}

int main( void )
{
    pthread_t id;
    pthread_create( &id ,NULL, Function , NULL);

	printf( "%d\n" , a);
    int b = a;
	printf( "%d\n" , b);
    pthread_join( id , NULL );
	printf( "%d\n" , b);
}
