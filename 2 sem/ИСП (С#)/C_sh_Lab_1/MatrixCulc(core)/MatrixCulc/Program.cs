using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MatrixCalculator
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Write("Введите количество строк матрицы (>0): ");
            int lines;
            while (Int32.TryParse(Console.ReadLine(), out lines) == false || lines <= 0) //проверка ввода на число
            {
                Console.Write("Неверный ввод. Попробуйте снова. Введите количество строк матрицы: ");
            }
            Console.Write("Введите количество столбцов матрицы (>0): ");
            int columns;
            while (Int32.TryParse(Console.ReadLine(), out columns) == false || columns <= 0) //проверка ввода на число
            {
                Console.Write("Неверный ввод. Попробуйте снова. Введите количество столбцов матрицы: ");
            }
            int[,] matrix;
            Input(lines, columns, out matrix); //ввод исходной матрицы
            Console.WriteLine("Исходная матрица:");
            Output(lines, columns, matrix); //вывод исходной матрицы

            //меню операций с матрицами
            int choose;
            do
            {
                Console.WriteLine("\n1 - транспонирование\n2 - умножение на число");
                Console.WriteLine("3 - сложение матриц\n4 - вычитание матриц\n5 - умножение матриц");
                Console.Write("6 - возведение матрицы в степень\n7 - выход\nВыберите операцию: ");
                while (Int32.TryParse(Console.ReadLine(), out choose) == false) //проверка ввода на число
                {
                    Console.Write("Неверный ввод. Попробуйте снова. Выберите операцию: ");
                }
                Console.WriteLine();
                switch (choose)
                {
                    case 1:
                        {
                            Transpose(lines, columns, matrix); //транспонирование
                            break;
                        }
                    case 2:
                        {
                            MultiplicationByNumber(lines, columns, matrix); //умножение матрицы на число
                            break;
                        }
                    case 3:
                        {
                            Sum(lines, columns, matrix); //сложение матриц
                            break;
                        }
                    case 4:
                        {
                            Difference(lines, columns, matrix); //вычитание матриц
                            break;
                        }
                    case 5:
                        {
                            Multiplication(lines, columns, matrix); //умножение матриц
                            break;
                        }
                    case 6:
                        {
                            Power(lines, columns, matrix); //возведение исходной матрицы в степень
                            break;
                        }
                    case 7:
                        {
                            break;
                        }
                    default:
                        {
                            Console.WriteLine("Данной операции не существует");
                            break;
                        }
                }
            } while (choose != 7);

            Console.ReadKey();
        }

        static void Output(int lines, int columns, int[,] matrix)
        {
            for (int i = 0; i < lines; i++)
            {
                for (int j = 0; j < columns; j++)
                {
                    Console.Write($"{matrix[i, j]} \t");
                }
                Console.WriteLine();
            }
        }

        static void Input(int lines, int columns, out int[,] matrix)
        {
            matrix = new int[lines, columns];
            string[] helpStr = new string[100]; //массив для ввода элементов матрицы в строку             
            bool error = true; //индикатор проверки на ввод не цифр
            //чтение матрицы с клавиатуры
            while (error == true)
            {
                error = false;
                do
                {
                    Console.Write($"Введите элементы матрицы (через пробел, {lines * columns} шт): ");
                    helpStr = Console.ReadLine().Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                    if (helpStr.Length != (lines * columns))
                    {
                        Console.WriteLine("Неверное количество элементов матрицы");
                    }
                } while (helpStr.Length != (lines * columns));
                int x = 0; //счетчик для массива строк               
                for (int i = 0; i < lines; i++)
                {
                    for (int j = 0; j < columns; j++)
                    {
                        if (Int32.TryParse(helpStr[x++], out matrix[i, j]) == false) //проверка ввода на число
                        {
                            error = true;
                        }
                    }
                }
                if (error == true)
                {
                    Console.WriteLine("Неверный ввод. Попробуйте снова.");
                }
            }
        }

        static void Transpose(int lines, int columns, int[,] matrix)
        {
            Console.WriteLine("Транспонированная матрица:");
            for (int j = 0; j < columns; j++)
            {
                for (int i = 0; i < lines; i++)
                {
                    Console.Write($"{matrix[i, j]} \t");
                }
                Console.WriteLine();
            }
        }

        static void MultiplicationByNumber(int lines, int columns, int[,] matrix)
        {
            int number;
            Console.Write("Введите число: ");
            while (Int32.TryParse(Console.ReadLine(), out number) == false) //проверка ввода на число
            {
                Console.Write("Неверный ввод. Попробуйте снова. Введите число: ");
            }
            Console.WriteLine($"Матрица, умноженная на {number}:");
            for (int i = 0; i < lines; i++)
            {
                for (int j = 0; j < columns; j++)
                {
                    Console.Write($"{number * matrix[i, j]} \t");
                }
                Console.WriteLine();
            }
        }

        static void Sum(int lines, int columns, int[,] matrix)
        {
            int[,] matrix2;
            Console.WriteLine($"Ввод второй матрицы размера {lines}x{columns}");
            Input(lines, columns, out matrix2); //ввод 2 матрицы для сложения
            Console.WriteLine("Сумма матриц:");
            for (int i = 0; i < lines; i++)
            {
                for (int j = 0; j < columns; j++)
                {
                    Console.Write($"{matrix[i, j] + matrix2[i, j]} \t");
                }
                Console.WriteLine();
            }
        }

        static void Difference(int lines, int columns, int[,] matrix)
        {
            int[,] matrix2;
            Console.WriteLine($"Ввод второй матрицы размера {lines}x{columns}");
            Input(lines, columns, out matrix2); //ввод 2 матрицы для вычитания
            Console.WriteLine("Разность матриц:");
            for (int i = 0; i < lines; i++)
            {
                for (int j = 0; j < columns; j++)
                {
                    Console.Write($"{matrix[i, j] - matrix2[i, j]} \t");
                }
                Console.WriteLine();
            }
        }

        static void Multiplication(int lines, int columns, int[,] matrix)
        {
            int[,] matrix2;
            Console.Write("Введите количество столбцов второй матрицы (>0): ");
            int columns2;
            while (Int32.TryParse(Console.ReadLine(), out columns2) == false || columns2 <= 0) //проверка ввода на число
            {
                Console.Write("Неверный ввод. Попробуйте снова. Введите количество столбцов второй матрицы: ");
            }
            Console.WriteLine($"Ввод второй матрицы размера {columns}x{columns2}");
            Input(columns, columns2, out matrix2); //ввод 2 матрицы для умножения
            Console.WriteLine("Произведение матриц:");
            int sum;
            int[,] matrixRez = new int[lines, columns2];
            //создание матрицы произведения
            for (int i = 0; i < lines; i++)
            {
                for (int j = 0; j < columns2; j++)
                {
                    sum = 0;
                    for (int k = 0; k < columns; k++)
                    {
                        sum += matrix[i, k] * matrix2[k, j];
                        matrixRez[i, j] = sum;
                    }
                }
            }
            Output(lines, columns2, matrixRez); //вывод матрицы произведения
        }

        static void Power(int lines, int columns, int[,] matrix)
        {
            if (lines != columns)
            {
                Console.WriteLine("Возводить в степень можно только квадратную матрицу");
                Console.WriteLine($"Исходная матрица прямоугольная размера {lines}x{columns}");
            }
            else
            {
                Console.Write("Введите показатель степени (>0): ");
                int number;
                while (Int32.TryParse(Console.ReadLine(), out number) == false || number <= 0) //проверка ввода на число
                {
                    Console.Write("Неверный ввод. Попробуйте снова. Введите показатель степени: ");
                }
                //создание доп. матрицы (копия matrix)
                int[,] matrix2 = new int[lines, lines];
                CopyMatrix(lines, matrix, matrix2);
                int[,] matrixRez = new int[lines, lines];
                CopyMatrix(lines, matrix, matrixRez); //копирование исходной матрицы в результат на случай степени 1
                int x = 1; //вспомогательный счетчик для показателя степени
                while (x < number)
                {
                    int sum;
                    //создание матрицы произведения matrix и ее копии matrix2 (доп. матрица)
                    for (int i = 0; i < lines; i++)
                    {
                        for (int j = 0; j < lines; j++)
                        {
                            sum = 0;
                            for (int k = 0; k < lines; k++)
                            {
                                sum += matrix[i, k] * matrix2[k, j];
                                matrixRez[i, j] = sum;
                            }
                        }
                    }
                    x++;
                    CopyMatrix(lines, matrixRez, matrix2); //копирование результата в доп. матрицу
                }
                Output(lines, lines, matrixRez); //вывод матрицы-степени
            }
        }

        static void CopyMatrix(int lines, int[,] matrix, int[,] matrix2)
        {
            for (int i = 0; i < lines; i++)
            {
                for (int j = 0; j < lines; j++)
                {
                    matrix2[i, j] = matrix[i, j];
                }
            }
        }
    }
}
