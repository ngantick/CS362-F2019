#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
	//rand() % (max_num + 1 - min_num) + min_num
    int i = rand() % (126 - 32 +1) + 32;	//generates a random number between 32 - 126 (printable ascii range)
	char c = (char)i;			//cast above num to a random char with that value
	
    return c;
}

char *inputString()
{
	int i = 6;
	int m = 0;
	char *str[i];
	str[i-1] = '\0';
	int k = rand() % 50;
	
	for( int j = 0; j < i-1; j++) {
		m = rand() % (126 - 32 +1) + 32;
		str[j] = (char)m;
	}
	
	
	if (k == 0) {
		strcpy(str, "reset");
	}
	
    return str;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
