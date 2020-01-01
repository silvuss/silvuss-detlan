#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

// Important: There is the assumption that sizeof(char) == 1; if this assumption
//	is expected to be wrong, the script needs to be changed

// Note: If the script is expected to be used in the future, it may be
//	reasonable to replace memcpy calls with strcpy calls

int silvLinesCount(FILE *const fp);
int silvMin(const int i1, const int i2);
bool silvStrEq(const char *const s1, const char *const s2);
char *silvGetLine(FILE *fp);
char *silvConcat(const char *const s1, const char *const s2);
char *silvItos(const int i);
char *silvSubstr(const char *const s, const int from, const int to);

int main(int argc, char *argv[])
{
	printf("debug: 'main' is running...\n");

	if (argc < 3)
	{
		fprintf(stderr, "Error: main: there are less arguments than 2");
		return -1;
	}

	FILE *inFp = fopen(argv[1], "r");

	bool isContent = NULL;
	FILE *outFp = NULL;
	int fileNumber = 0;
	int linesCount = silvLinesCount(inFp);

	double loopTime = 0;
	clock_t start, end;
	start = clock();

	printf("Number of files created so far: ");

	for (int i = 0; i < linesCount; ++i)
	{

		const char *const line = silvGetLine(inFp);
		const char *filenameSuffix = NULL;
		const char *outFilePath = NULL;

		const char *const expectedStart = "      <text xml";
		const char *const actualStart = silvSubstr(
			line,
			0,
			silvMin(strlen(line), strlen(expectedStart)));
		// printf("\tdebug: actualStart == %s\n", actualStart);

		const char *const expectedEnd = "</text>";
		const char *const actualEnd = strlen(line) > strlen(expectedEnd)
										  ? silvSubstr(
												line,
												strlen(line) - strlen(expectedEnd),
												strlen(line))
										  : strdup(line);

		if (silvStrEq(actualStart, expectedStart))
		{
			isContent = true;
			++fileNumber;
			filenameSuffix = silvItos(fileNumber);
			outFilePath = silvConcat(argv[2], filenameSuffix);
			outFp = fopen(outFilePath, "a");
		}

		if (isContent == true)
		{
			fputs(line, outFp);
		}

		if (silvStrEq(actualEnd, expectedEnd))
		{
			isContent = false;
			fclose(outFp);
		}

		printf("%6d\b\b\b\b\b\b", fileNumber);

		free((char *)actualStart);
		free((char *)actualEnd);
		free((char *)line);
		free((char *)filenameSuffix);
		free((char *)outFilePath);
	}

	end = clock();
	loopTime = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("\nLoop execution time: %fs\n", loopTime);

	fclose(inFp);

	return 0;
}

int silvLinesCount(FILE *const fp)
{
	if (fp == NULL)
	{
		fprintf(stderr, "Error: silvLinesCount: fp == NULL");
	}

	char c;
	int lineCount = 0;
	while ((c = fgetc(fp)) != EOF)
	{
		if (c == '\n')
		{
			++lineCount;
		}
	}
	fseek(fp, 0, SEEK_SET);

	return lineCount;
}

int silvMin(const int i1, const int i2)
{
	if (i1 <= i2)
	{
		return i1;
	}
	else
	{
		return i2;
	}
}

bool silvStrEq(const char *const s1, const char *const s2)
{
	if (s1 == NULL || s2 == NULL)
	{
		fprintf(stderr, "Error: silvStrEq: either s1 == NULL or s2 == NULL");
	}

	if (strcmp(s1, s2) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Needs a corresponding call for "free" by the user
char *silvGetLine(FILE *fp)
{
	if (fp == NULL)
	{
		fprintf(stderr, "Error: silvGetLine: fp == NULL");
	}

	int c; // changed from 'char c' thanks to https://4programmers.net/Forum/C_i_C++/334473-free_double_free_detected_in_tcache_2#comment-556329
	int lineSize = 0;
	while (true)
	{
		c = getc(fp);
		if (c == EOF || c == '\n')
		{
			break;
		}
		++lineSize;
	}

	char *line = malloc(lineSize + 1);  // +1 for NULL character
	fseek(fp, -lineSize - 1, SEEK_CUR); // -1 because getc has also read the newline
	fgets(line, lineSize + 1, fp);		// +1 because fgets reads "count - 1" bytes
	fseek(fp, 1, SEEK_CUR);				// jump over the newline (the necessity of it was really hard to notice)

	return line;
}

// Needs a corresponding call for "free" by the user
char *silvConcat(const char *const s1, const char *const s2)
{
	if (s1 == NULL || s2 == NULL)
	{
		fprintf(stderr, "Error: silvConcat: either s1 == NULL or s2 == NULL");
	}

	char *const result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for NULL character
	memcpy(result, s1, strlen(s1));
	memcpy(result + strlen(s1), s2, strlen(s2));
	memcpy(result + strlen(s1) + strlen(s2), "\0", 1); // +1 for NULL character

	return result;
}

// Needs a corresponding call for "free" by the user
char *silvItos(const int i)
{
	if (i < 0)
	{
		fprintf(stderr, "Error: silvItos: i < 0");
	}

	int charactersNumber = (int)(floor(log10(i)) + 1); // +1 cause there's floor
	char *const result = malloc(charactersNumber + 1); // +1 for NULL character
	sprintf(result, "%d", i);

	if (result == NULL)
	{
		fprintf(
			stderr,
			"Warning: silvItos: something went wrong, result == NULL");
	}

	return result;
}

// Needs a corresponding call for "free" by the user
char *silvSubstr(const char *const s, const int from, const int to)
{
	if (s == NULL)
	{
		fprintf(stderr, "Error: silvSubstr: s == NULL");
	}

	if (from > to)
	{
		fprintf(stderr, "Error: silvSubstr: from > to");
	}

	int substrSize = to - from;
	char *const result = malloc(substrSize + 1); // +1 for NULL character
	memcpy(result, s + from, substrSize);
	memcpy(result + substrSize, "\0", 1);

	return result;
}