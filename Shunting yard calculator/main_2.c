#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void die(const char *msg)
{
	fprintf(stderr, "%s", msg);
	abort();
}

#define MAX_D 256
double stack[MAX_D];
int depth;

void push(double v)
{
	if (depth >= MAX_D) die("stack overflow\n");
	stack[depth++] = v;
}

double pop()
{
	if (!depth) die("stack underflow\n");
	return stack[--depth];
}

double rpn(char *s)
{
	double a, b;
	int i;
	char *e, *w = " \t\n\r\f";

	for (s = strtok(s, w); s; s = strtok(0, w)) {
		a = strtod(s, &e);
		if (e > s)		printf(" :"), push(a);
#define binop(x) printf("%c:", *s), b = pop(), a = pop(), push(x)
		else if (*s == '+')	binop(a + b);
		else if (*s == '-')	binop(a - b);
		else if (*s == '*')	binop(a * b);
		else if (*s == '/')	binop(a / b);
		else if (*s == '^')	binop(pow(a, b));
#undef binop
		else {
			fprintf(stderr, "'%c': ", *s);
			die("unknown oeprator\n");
		}
		for (i = depth; i-- || 0 * putchar('\n'); )
			printf(" %g", stack[i]);
	}

	if (depth != 1) die("stack leftover\n");

	return pop();
}


#define MAX_OP_STACK_SIZE 500
#define MAX_OUTPUT_SIZE 500
#define MAX_LINE_SIZE MAX_OUTPUT_SIZE+MAX_OP_STACK_SIZE
#define NOPS 4

typedef struct operators
{
    char pre, as;
};


struct operators opsPrecedence[255];
void initOpsStruct()
{
     // Associativity
     opsPrecedence['|'].as=0;
     opsPrecedence['^'].as=0;
     opsPrecedence['&'].as=0;
     opsPrecedence['<' + '<'].as=0;
     opsPrecedence['>' + '>'].as=0;
     opsPrecedence['+'].as=0;
     opsPrecedence['-'].as=0;
     opsPrecedence['*'].as=0;
     opsPrecedence['/'].as=0;
     opsPrecedence['%'].as=0;
     opsPrecedence['~'].as=0;


     opsPrecedence['|'].pre=0;
     opsPrecedence['^'].pre=1;
     opsPrecedence['&'].pre=2;
     opsPrecedence['<' + '<'].pre=3;
     opsPrecedence['>' + '>'].pre=3;
     opsPrecedence['+'].pre=4;
     opsPrecedence['-'].pre=4;
     opsPrecedence['*'].pre=5;
     opsPrecedence['/'].pre=5;
     opsPrecedence['%'].pre=5;
     opsPrecedence['~'].pre=6;
}


char *opstack;
unsigned int sp;

char *output;
unsigned int outsp;


int get_line(char line[])
{
    int i = 0, c;

    while (i<MAX_LINE_SIZE && (c = getchar()) != EOF && c != '\n')
    {
        if (c != ' ' && c != '\t')
        {
            line[i] = c;
            i++;

        }
    }
    line[i]='\0';

    return i;
}


char isop(int var)
{

    return (var=='+' || var=='/' || var=='-' || var=='*' || var=='^');
}


void do_it()
{
    int len, i, j;
    double val = 0.0,power = 1.0;
    char line[MAX_LINE_SIZE];

    while ((len = get_line(line)) >= 1 )
    {
        for(i = 0;i<len && line[i] != '\0';)
        {


            puts("debugs");
            if (isdigit(line[i]))
            {
                while (isdigit(line[i]))
                {
                    output[outsp] = line[i];
                    outsp++;

                    i++;
                }
                output[outsp] = ' ';
                outsp++;
            }
            else
            if (isop(line[i]))
                {

                    while (sp > 0 && (opsPrecedence[opstack[sp-1]].pre > opsPrecedence[line[i]].pre  || (opsPrecedence[opstack[sp-1]].pre == opsPrecedence[line[i]].pre && opsPrecedence[line[i]].as==0 ) ) && opstack[sp-1] != '(' )
                    {
                        output[outsp] = opstack[(sp-1)];
                        outsp++;
                        output[outsp] = ' ';
                        outsp++;


                        sp--;
                    }


                    opstack[sp++] = line[i];
                    puts("\n----\n");
                 putchar(opstack[(sp-1)]);
                 puts("\n----\n");

                    i++;
                }
                else
                if (line[i] == '(')
                {
                   opstack[sp] = line[i];
                   sp++;
                   i++;
                }
                else
                if (line[i] == ')')
                {
                    while (opstack[sp-1] != '(')
                    {
                        output[outsp++] = opstack[sp-1];
                        output[outsp++] = ' ';
                        sp--;

                        if (sp<=0)
                        {
                            fprintf(stderr,"Error mismatched paranthesis");
                            return ;
                        }
                    }

                    if (opstack[sp-1] == '(')
                    {
                        sp--;
                    }
                    i++;
                }


        }

        while (sp>0)
        {
            output[outsp] = opstack[sp-1];
            outsp++;
            output[outsp++] = ' ';
            sp--;
        }

        return ;

    }

}


int main(void)
{
    opstack = (char *) malloc(MAX_OP_STACK_SIZE);
    output = (char *) malloc(MAX_OUTPUT_SIZE);
    initOpsStruct();

    while(1){

        do_it();
        printf("%s\n", rpn(output));
        for (int _i = 0 ; _i<=outsp;_i++)
        {
            output[_i] = 0;
        }

        outsp=0;

    }
}
