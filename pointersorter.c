
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>


int countw(char *Beer);
void complete(char **string, char *At, int strsize);
void shifter(char ** string, int now, int next);
void allocation(char ** string, int strsize);
void newplace(char ** string, int i, int j);
void output(char ** string, int val);

void shifter(char **string, int now, int next)
{
	int former;
	int latter;

	if (now >= next)
		return;
	newplace(string, now, (now+next)/2);
	latter = now;

	for (former = now + 1; former <= next; former++){
		if (strcmp(string[former], string[now]) < 0)
			newplace(string, ++latter, former);
	}

	newplace(string, now, latter);

	shifter(string, now, latter -1);
	shifter(string, latter + 1, next);
}


//how many different methods are we going to need to use??
void complete(char **string, char *At, int strsize)
{
	int j;
	int recall;
	int i=0;
	int beginning=0;
	int number=0;

	while(At[i] != '\0')              //When we don’t have a null value in s[i]
		{
		while (!(isalpha(At[i])) && At[i] != '\0')//can we remove the &&
			{
			i++;
			}
		if (At[i] == '\0')
		{					//Do we need this?
			break;
		}
		recall = i;         //counter for delimiter
		while (isalpha(At[i]) && At[i] != '\0')
		{
			number++;    //count for the words
			i++;
		}
		char *rick = (char *) malloc((number + 1) *sizeof(char));
		if (rick == NULL)
		{
			printf("Error!!!");
			exit(1);
		}
		for (j = 0; j < number; j++)
		{
			rick[j] = At[recall];  //move contents of s char array into p char array
			recall++;
		}
		rick[j] = '\0';
		string[beginning] = rick;  //allows us to store our word to array
		beginning++;
		number = 0;
		rick = NULL;
		}

	shifter(string, 0, strsize - 1);
	output(string, strsize);
	allocation(string,strsize);

}

void output(char **string, int val)
{
	int x;
	for(x = 0; x < val; x++)
	{
		printf("%s\n", string[x]);
	}
}

int countw(char *Beer)
{
	int word = 0;
	int incre = 0;
	while (Beer[word] != '\0')
	{  //when our value is not a null  val
		while (!isalpha(Beer[word]) && Beer[word] != '\0')
		{//separator not at the end of the string, just simply increment i
			word++;
		}
		//Are separators null values?
		if(Beer[word] == '\0')
		{					//if we have n number of characters towards the end of the string
			break;
		}
		while (isalpha(Beer[word]) && Beer[word] != '\0')
		{ //seek out every word in the char array
			word++;
		}
		incre++;
	}
	return incre;
}


void allocation(char **string, int strsize)
{
	int y;
	for( y = 0; y < strsize; y++)
	{
		free(string[y]);
		string[y] = NULL;
	}
}

//The easiest code right here
void newplace(char ** string, int now, int next)
{
	char *ptr;
	ptr = string[now];
	string[now] = string[next];
	string[next] = ptr;
}


int main(int argc, char *argv[])
{
	int minW;
	if (argc != 2)
	{
		printf("Error! Wrong Number of Arguments!\n");
		exit(1);
	}
	char *newCA = argv[1];
	if (newCA == NULL)
	{
		printf("Error! No vals.\n");
		exit(1);
	}
	minW = countw(newCA);
	if (minW == 0)
	{
		printf("Error! No words typed.");
		exit(1);
	}
	char *stan[minW];
	complete(stan, newCA, minW);

	return 0;
}


