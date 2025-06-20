/* длина строки */
int Length(char *string)
{
    int i = 0;
    while(string[i] != '\0')
    {
        i++;
    }
    return i;
}

/* замена скобочек на следующий вид: ( [ { { } } ] ) */
void Replace(char *string)
{
    int i, len, current_level = 0;

    for (i = 0, len = Length(string); i < len; i++)
        {
            if (string[i] == '{')
            {
                current_level++;
                if (current_level == 1)
                    string[i] = '(';
                if (current_level == 2)
                    string[i] = '[';
            }
            if (string[i] == '}')
            {
                if (current_level == 1)
                    string[i] = ')';
                if (current_level == 2)
                    string[i] = ']';
                current_level--;
            }
        }
}

/* предварительная замена всех скобок на {} и проверка на соответсвие скобок */
void CheckParentheses(char *string)
{
    int i, len, current_level = 0;

    for (i = 0, len = Length(string); i < len; i++)
    {
        if (string[i] == '(')
        {
            string[i] = '{';
            current_level++;
        }
        if (string[i] == ')')
        {
            string[i] = '}';
            current_level--;
        }
    }
    if (current_level != 0)
    {
        printf("Parentheses are wrong");
        exit(0);
    }
}
