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
char isop(const char *var);

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




#define MAX_OP_STACK_SIZE 500
#define MAX_OUTPUT_SIZE 500
#define MAX_LINE_SIZE (MAX_OUTPUT_SIZE+MAX_OP_STACK_SIZE)
#define OPERATOR_MAX_LEN 10
#define MAX_OUTPUT_LENGTH 100


typedef struct operators
{
    char pre, as;
};


struct operators _opsPrecedence[20];
void initOpsStruct()
{
    _opsPrecedence[0].pre=0; // |
    _opsPrecedence[1].pre=1; // ^
    _opsPrecedence[2].pre=2; // &
    _opsPrecedence[3].pre=3; // <<
    _opsPrecedence[4].pre=3; // >>
    _opsPrecedence[5].pre=4; // +
    _opsPrecedence[6].pre=4; // -
    _opsPrecedence[7].pre=5; // *
    _opsPrecedence[8].pre=5; // /
    _opsPrecedence[9].pre=5; // %
    _opsPrecedence[10].pre=6; // ~
    _opsPrecedence[11].pre=6; // unary minus (-u)
    _opsPrecedence[12].pre=6; // unary minus (+u)

    // Associativity (IDs are the same as presedence)
    _opsPrecedence[0].as=0;
    _opsPrecedence[1].as=0;
    _opsPrecedence[2].as=0;
    _opsPrecedence[3].as=0;
    _opsPrecedence[4].as=0;
    _opsPrecedence[5].as=0;
    _opsPrecedence[6].as=0;
    _opsPrecedence[7].as=0;
    _opsPrecedence[8].as=0;
    _opsPrecedence[9].as=0;
    _opsPrecedence[10].as=0;
    _opsPrecedence[11].as=1;
    _opsPrecedence[12].as=1;
}

struct operators opsPrecedence(const char * operator)
{
    if (!strcmp(operator,"+u"))
    {
        return _opsPrecedence[12];

    } else
    if (!strcmp(operator,"-u"))
    {
        return _opsPrecedence[11];

    } else
    if (!strcmp(operator,"~"))
    {
        return _opsPrecedence[10];

    } else
    if (!strcmp(operator,"%"))
    {
        return _opsPrecedence[9];

    } else
    if (!strcmp(operator,"/"))
    {
        return _opsPrecedence[8];

    } else
    if (!strcmp(operator,"*"))
    {
        return _opsPrecedence[7];

    } else
    if (!strcmp(operator,"-"))
    {
        return _opsPrecedence[6];

    } else
    if (!strcmp(operator,"+"))
    {
        return _opsPrecedence[5];

    } else
    if (!strcmp(operator,">>"))
    {
        return _opsPrecedence[4];

    } else
    if (!strcmp(operator,"<<"))
    {
        return _opsPrecedence[3];

    } else
    if (!strcmp(operator,"&"))
    {
        return _opsPrecedence[2];

    } else
    if (!strcmp(operator,"^"))
    {
        return _opsPrecedence[1];

    } else
    if (!strcmp(operator,"|"))
    {
        return _opsPrecedence[0];

    }


}




char *tempop;
char **opstack;
unsigned int sp;


char **output;
unsigned int outsp;



double rpn()
{
	double a;
	int i, j;
	char flag;
    for ( int _i = 0;output[_i][0]!='\0';_i++)
    {
            printf("%s ", output[_i]);


    }
        puts("\ndasad");


	for ( i = 0;output[i][0]!='\0';i++)
    {
        flag=0;

        for ( j = 0;output[i][j]!='\0';j++)
        {
            if (output[i][j] != '.' &&!isdigit(output[i][j]))
            {
                break;
            }
            else
                flag=1;

        }

        if (flag) //(a=atof(output[i]))
        {
            push(atof(output[i]));

        }
        else if(isop(output[i]))
        {

            if (!strcmp("-u",output[i]))
            {
                a=pop();
                push(a*(-1));
            }
            else
            if (!strcmp("+u",output[i]))
            {
                push(pop());
            }
            else
            if (!strcmp("+",output[i]))
            {
                printf("\np%sp\n",output[i]);
                push(pop()+pop());
            }
            else
            if (!strcmp("-",output[i]))
            {
                a=pop();
                push(pop()-a);
            }
            else
            if (!strcmp("/",output[i]))
            {
                a=pop();
                push(pop()/a);
            }
            else
            if (!strcmp("*",output[i]))
            {
                push(pop()*pop());
            }


        }
        else
            die("nanato\n");



    }



	return pop();
}




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


char isop(const char *var)
{
    return (!strcmp(var,"-u") || !strcmp(var,"+") ||!strcmp(var,"/") || !strcmp(var,"-") || !strcmp(var,"*") || !strcmp(var,"^"));
}



void do_it()
{
    int len, i, j = 0;
    double val = 0.0,power = 1.0;
    char line[MAX_LINE_SIZE];

    while ((len = get_line(line)) >= 1 )
    {
        for(i = 0;i<len && line[i] != '\0';)
        {
            j=0;




            if (isdigit(line[i]))
            {


                while (isdigit(line[i]))
                {
                    output[outsp][j] = line[i];
                    j++;
                    i++;
                }

                if (line[i]=='.')
                    {
                        output[outsp][j++] = line[i++];
                        while (isdigit(line[i]))
                        {
                            output[outsp][j++] = line[i++];
                        }

                    }



                output[outsp][j] = '\0';
                outsp++;




            }
            else
            if (line[i]!='(' && line[i]!=')')
                {


                    while ( !isdigit(line[i]) && line[i]!='\0' && line[i]!='(' && line[i]!=')')
                    {
                        tempop[j] = line[i];
                        i++;
                        j++;

                    }

                    tempop[j] = '\0';



                    if (isop(tempop))
                    {
                        if (i==1||(i>1 && line[i-2]=='('))
                        {
                            strcat(tempop,"u");

                        }


                        while (sp > 0 && (opsPrecedence(opstack[sp-1]).pre > opsPrecedence(tempop).pre || (opsPrecedence(opstack[sp-1]).pre == opsPrecedence(tempop).pre && opsPrecedence(tempop).as == 0 )) && opstack[sp-1] != '(' )
                        {
                            strcpy(output[outsp],opstack[sp-1]);
                            outsp++;
                            sp--;
                        }


                    strcpy(opstack[sp],tempop);

                    sp++;

                    }
                    else{

                        continue;
                    }


                }
                else
                if (line[i] == '(')
                {
                   opstack[sp][j] = line[i];
                   j++;
                   opstack[sp][j] = '\0';
                   sp++;
                   i++;

                }
                else
                if (line[i] == ')')
                {
                    while (opstack[sp-1][0] != '(')
                    {

                        strcpy(output[outsp],opstack[sp-1]);
                        outsp++;

                        sp--;

                        if (sp<=0)
                        {
                            fprintf(stderr,"Error mismatched paranthesis");
                            return ;
                        }
                    }

                    if (opstack[sp-1][0] == '(')
                    {
                        sp--;
                    }

                    i++;
                }


        }

        while (sp>0)
        {

            strcpy(output[outsp],opstack[sp-1]);
            outsp++;
            sp--;
        }

        output[outsp][0]='\0';
        return;

    }

}

void initStacks()
{
        opstack = (char **) malloc(MAX_OP_STACK_SIZE);
        output = (char **) malloc(MAX_OUTPUT_SIZE);
        tempop = (char *) malloc(OPERATOR_MAX_LEN);

        for (int _i = 0;_i<=MAX_OP_STACK_SIZE;_i++)
        {
            opstack[_i] = (char *) malloc(OPERATOR_MAX_LEN);
        }

        for (int _i = 0;_i<=MAX_OUTPUT_SIZE;_i++)
        {
            output[_i] = (char *) malloc(MAX_OUTPUT_LENGTH);
        }

}


int main(void)
{
    initStacks();
    initOpsStruct();

    while(1){
        do_it();

        printf("%g", rpn());

        puts("\n");

        outsp=0;

    }
}
