#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 100
void IToPfix(char *ifix,
             char *pfix);   // Make infix expression into postfix with a stack
int priority(char);         // Set operators priority
double pfix_parser(char *); // Use another stack to parse the postfix expression
double calculate(char, double, double);

int main() {
    char ifix[MAX] = {'\0'};
    scanf("%s", ifix);
    printf("%f", pfix_parser(ifix));

    return 0;
}

void IToPfix(char *ifix, char *pfix) {
    char stack[MAX] = {'\0'};
    int i, j, top;
    for (i = 0, j = 0, top = 0; ifix[i] != '\0'; i++)
        switch (ifix[i]) {
        case '(': // If meet ( then push it to stack
            stack[++top] = ifix[i];
            break;
        case '+':
        case '-':
        case '*':
        case '/':
            while (priority(stack[top]) >=
                   priority(ifix[i])) { // If meet an op then pop ops which
                                        // priority >= current op
                pfix[j++] = stack[top--];
            }
            stack[++top] = ifix[i];
            break;
        case ')':
            while (stack[top] !=
                   '(') { // If meet ) then pop all ele from stack until meet (
                pfix[j++] = stack[top--];
            }
            top--; // Dispose ) directly
            break;
        default: // If meet a number then set a char n to locate the cut point
                 // of the number(So it support more then a single digits)
            while (isdigit(ifix[i]))
                pfix[j++] = ifix[i++];
            pfix[j++] = 'n';
            i--;
        }
    while (top > 0) {
        pfix[j++] = stack[top--];
    }
}

int priority(char op) {
    switch (op) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}

double pfix_parser(char *ifix) {
    char pfix[MAX] = {'\0'};
    double stack[MAX] = {0.0};

    IToPfix(ifix, pfix);

    int top, i;
    for (top = 0, i = 0; pfix[i] != '\0'; i++)
        switch (pfix[i]) {
        case '+':
        case '-':
        case '*':
        case '/':
            stack[top - 1] = calculate(pfix[i], stack[top - 1], stack[top]);
            top--;
            break;
        default:
            if (isdigit(pfix[i])) {
                stack[++top] = atof(pfix + i);
                while (pfix[i + 1] != 'n')
                    i++;
            }
        }

    return stack[top];
}

double calculate(char op, double a, double b) {
    switch (op) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    }
    return 0;
}