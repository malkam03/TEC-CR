//SSE headers
#include <emmintrin.h>//v3
#include <smmintrin.h>//v4
#include <stdio.h>

int main(){
	printf("Hola mundo desde SSE\n");
	__m128i vector1 = _mm_set_epi32(4,3,2,1);// Little endian, stored in 'reverse
	__m128i vector2 = _mm_set_epi32(8,7,6,5);
	//Adition
	__m128i result = _mm_add_epi32(vector1, vector2); // Result = vector1 + vector2
	//Vector printing
	int data = 0;
	int i;
	printf("Result **************\n");
	data = _mm_extract_epi32(result, 0);
	printf("%d\t", data);

	data = _mm_extract_epi32(result, 1);
	printf("%d\t", data);

	data = _mm_extract_epi32(result, 2);
	printf("%d\t", data);

	data = _mm_extract_epi32(result, 3);
	printf("%d\t", data);
	printf("\n");	

}
