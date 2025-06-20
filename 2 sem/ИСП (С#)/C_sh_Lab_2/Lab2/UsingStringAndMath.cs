using System;

namespace Lab2
{
    class UsingStringAndMath
    {
        public UsingStringAndMath()
        {
            Console.WriteLine("Enter a real number (use . or ,)");
            Input(out string str, out bool checkMinus); //ввод числа с точкой (как строка)
            int index = 0;
            str = str.Replace("-", ""); //удаление -
            // нахождение индекса знака(. или ,) и удаление его из строки
            for (int i = 0; i < str.Length; i++)
            {
                if (str[i] == '.' || str[i] == ',')
                {
                    index = i;
                    str = str.Replace(".", "");
                    str = str.Replace(",", "");
                    break;
                }
            }
            int digit = 0;
            decimal number = 0;
            //посимвольное конвертирование символов строки в int 
            for (int i = 0; i < str.Length; i++)
            {
                switch (str[i])
                {
                    case '0':
                        {
                            digit = 0;
                            break;
                        }
                    case '1':
                        {
                            digit = 1;
                            break;
                        }
                    case '2':
                        {
                            digit = 2;
                            break;
                        }
                    case '3':
                        {
                            digit = 3;
                            break;
                        }
                    case '4':
                        {
                            digit = 4;
                            break;
                        }
                    case '5':
                        {
                            digit = 5;
                            break;
                        }
                    case '6':
                        {
                            digit = 6;
                            break;
                        }
                    case '7':
                        {
                            digit = 7;
                            break;
                        }
                    case '8':
                        {
                            digit = 8;
                            break;
                        }
                    case '9':
                        {
                            digit = 9;
                            break;
                        }
                }
                //подсчет double с помощью позиции каждого символа                         
                number += (decimal)(digit * Math.Pow(10, (index - 1 - i)));
            }
            if (checkMinus == true)
            {
                number *= (decimal)(-1);
            }
            Console.WriteLine("This is a real number of decimal type (converted without Parse/TryParse):");
            Console.WriteLine(number);
            Console.WriteLine("Be careful! Too long lines are rounded");
        }

        static void Input(out string str, out bool checkMinus)   //функция ввода с проверкой необходимых ошибок
        {
            bool checkInput;
            int amountPoints, amountMinus;
            do
            {
                checkMinus = false;
                checkInput = true;
                amountPoints = 0;
                amountMinus = 0;
                str = Console.ReadLine();
                for (int i = 0; i < str.Length; i++)
                {
                    //проверка на ввод недопустимых знаков
                    if ((str[i] < '0' || str[i] > '9') && str[i] != '.' && str[i] != ',' && str[i] != '-')
                    {
                        Console.WriteLine("Wrong input. Try again");
                        checkInput = false;
                        break;
                    }
                    if (str[i] == '.' || str[i] == ',')
                    {
                        amountPoints++;   //проверка на наличие одной .(,)
                    }
                    if (str[i] == '-')
                    {
                        if (i == 0)
                        {
                            checkMinus = true;
                        }
                        amountMinus++;
                    }
                }
                if ((amountPoints != 1 || amountMinus > 1) && checkInput)
                {
                    Console.WriteLine("Wrong amount of points or minuses. Try again");
                }
                if (!checkMinus && amountMinus == 1)
                {
                    Console.WriteLine("Wrong location of minus. Try again");
                }
            } while (!checkInput || amountPoints != 1 || amountMinus > 1 || (!checkMinus && amountMinus == 1));
        }
    }
}
