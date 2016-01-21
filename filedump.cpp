#include <cstdio>
#include <cstdlib>
 
int filedump(char* fileName, char* outFile = NULL)
{
	FILE *inPtr = NULL;			//input file
	FILE *outPtr = NULL;			//output file
	FILE *out = stdout;			//output stream
	size_t size;				//File size
	void *buffer;				//Pointer to file in memory
	unsigned char *byte_ptr;		//Pointer to single byte
 
	//Open file
	inPtr = fopen(fileName, "rb");
	if (inPtr == NULL)
	{
		printf("Can't open file: %s", fileName);
		return 1;
	}
 
	//Create output file
	if (outFile != NULL)
	{
		outPtr = fopen(outFile, "w");
		if (outPtr == NULL)
		{
			printf("Can't create output file: %s", fileName);
			return 2;
		}
		out = outPtr;
	}
 
	//Calculate file size (in bytes)
	fseek(inPtr, 0, SEEK_END);
	size = ftell(inPtr);
	fseek(inPtr, 0, SEEK_SET);
 
	//Copy file to memory and close file
	buffer = malloc(size);
	if (buffer == NULL)
	{
		printf("Can't alloc memory for file");
		fclose(inPtr);
		if (outFile != 0)
			fclose(outPtr);
		return 3;
	}
	fread(buffer, 1, size, inPtr);
	fclose(inPtr);
 
	//Set byte pointer to first byte of file in memory
	byte_ptr = (unsigned char*)buffer;
 
	//Write file (byte by byte)
	for (int i = 1; i <= size; i++)
	{
		//Write byte offset
		if ((i % 16) == 1) fprintf(out, "0x%08X: ", (i - 1));
 
		//Write actual byte and set pointer to the next byte
		fprintf(out, "%02X", *byte_ptr);
		byte_ptr += 1;
 
		//double spaces after every 4 bytes
		if ((i % 4) == 0) fprintf(out, " ");
 
		//new line after every 16 bytes
		if ((i % 16) == 0) fprintf(out, "\n");
	}
 
	//Exit
	free(buffer);
	if (outFile != 0)
		fclose(outPtr);
 
	return 0;
}
 
 
int main(int argc, char* argv[])
{
	if (argc == 2 )
		filedump(argv[1]);
	else if (argc == 3)
		filedump(argv[1], argv[2]);
	else
		printf("Use: filedump.exe <in> <out>");
 
	return 0;
}