#include <stdlib.h>


int main(int argc,char *argv[])
{

	if (argc != 2)
	{
		printf("Need only 1 argument: path of mp3 file\n");
		exit(-1);
	}
	const char* file_name = argv[1];
	audioTest(file_name);

	return 0;
}

