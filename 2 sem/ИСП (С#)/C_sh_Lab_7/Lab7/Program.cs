using System;

namespace Lab7
{
    class Program
    {
        static void Main(string[] args)
        {
            long a = 12;
            long b = 20;
            long c = -7;
            long d = 15;
            RationalNumber r1 = new RationalNumber(a, b);
            RationalNumber r2 = new RationalNumber(c, d);

            //математические операции
            Console.WriteLine("ПЕРЕКРЫТИЕ МАТЕМАТИЧЕСКИХ ОПЕРАЦИЙ\n--------------------------------");
            Console.WriteLine($"Сумма дробей:\n{r1.ToString()} + ({r2.ToString()}) = " +
                $"{(r1 + r2).ToString()}");
            Console.WriteLine($"Сумма дроби и числа:\n{r1.ToString()} + 3 = {(r1 + 3).ToString()}");
            Console.WriteLine($"Сумма числа и дроби:\n2 + ({r2.ToString()}) = {(2 + r2).ToString()}");
            Console.WriteLine($"Разность дробей:\n{r1.ToString()} - ({r2.ToString()}) = " +
                $"{(r1 - r2).ToString()}");
            Console.WriteLine($"Разность дроби и числа:\n{r1.ToString()} - 3 = {(r1 - 3).ToString()}");
            Console.WriteLine($"Разность числа и дроби:\n2 - ({r2.ToString()}) = {(2 - r2).ToString()}");
            Console.WriteLine($"Произведение дробей:\n{r1.ToString()} * ({r2.ToString()}) =" +
                $" {(r1 * r2).ToString()}");
            Console.WriteLine($"Произведение дроби и числа:\n{r1.ToString()} * 3 = {(r1 * 3).ToString()}");
            Console.WriteLine($"Произведение числа и дроби:\n2 * {r2.ToString()} = {(2 * r2).ToString()}");
            try
            {
                Console.WriteLine($"Деление дробей:\n{r1.ToString()} / ({r2.ToString()}) =" +
                    $" {(r1 / r2).ToString()}");
                Console.WriteLine($"Деление дроби на число:\n{r1.ToString()} / 3 = {(r1 / 3).ToString()}");
                Console.WriteLine($"Деление числа на дробь:\n2 / {r2.ToString()} = {(2 / r2).ToString()}");
            }
            catch (DivideByZeroException)
            {
                Console.WriteLine("ОШИБКА! Деление на ноль");
            }
            Console.WriteLine($"Противоположная дробь:\n{r1.ToString()} -> {(-r1).ToString()}");
            Console.WriteLine($"Инкремент:\n++({r1.ToString()}) -> {(++r1).ToString()}");
            Console.WriteLine($"Декремент:\n--({r1.ToString()}) -> {(--r1).ToString()}");

            //операции сравнения
            Console.WriteLine("\nПЕРЕКРЫТИЕ ОПЕРАЦИЙ СРАВНЕНИЯ\n--------------------------------");
            Console.WriteLine($"Сравнение дробей(==,!=):\n{r1.ToString()} {EqualZn(r1, r1)} {r1.ToString()}");
            Console.WriteLine($"{r1.ToString()} {EqualZn(r1, r2)} {r2.ToString()}");
            Console.WriteLine($"Сравнение дробей(>,<,>=,<=):\n{r1.ToString()} {Znak(r1, r1)} {r1.ToString()}");
            Console.WriteLine($"{r2.ToString()} {Znak(r2, r1)} {r1.ToString()}");
            Console.WriteLine($"Сравнение дроби с числом(==,!=):\n{r1.ToString()} {EqualZn(r1, -3)} -3");
            Console.WriteLine($"Сравнение дроби с числом(>,<,>=,<=):\n{r1.ToString()} {Znak(r1, 5)} 5");

            // явные и неявные операторы преобразования
            RationalNumber r3 = new RationalNumber(-4, 3);
            Console.WriteLine("\nПРЕОБРАЗОВАНИЕ ТИПОВ\n--------------------------------");
            Console.WriteLine($"В int {r3.ToString()} -> {(int)r3}");
            Console.WriteLine($"В long {r3.ToString()} -> {(long)r3}");
            Console.WriteLine($"В double {r3.ToString()} -> {(double)r3}");
            Console.WriteLine($"В decimal {r3.ToString()} -> {(decimal)r3}");
            r3 = 25;
            Console.WriteLine($"Из int 25 -> {r3}");
            r3 = 154L;
            Console.WriteLine($"Из long 154 -> {r3}");
            r3 = 2.5;
            Console.WriteLine($"Из double 2.5 -> {r3}");
            r3 = 0.2225m;
            Console.WriteLine($"Из decimal 0.2225 -> {r3}");

            //представление в виде строки в различных форматах
            Console.WriteLine("\nПРЕДСТАВЛЕНИЕ ДРОБИ В ВИДЕ СТРОКИ\n-----------------------------------");
            Console.WriteLine("1 вариант: " + r1.DifferentStrings('.'));
            Console.WriteLine("2 вариант: " + r1.DifferentStrings(','));
            Console.WriteLine("3 вариант: " + r1.DifferentStrings('/'));

            // получение объекта класса по строковому представлению из разных форматов
            Console.WriteLine("\nПОЛУЧЕНИЕ ДРОБИ ПО СТРОКОВОМУ ПРЕДСТАВЛЕНИЮ" +
                "\n--------------------------------------------");
            do
            {
                r3 = RationalNumber.TakeFromStrings();
                r3.ReducedFraction();
                Console.WriteLine($"\nВаше число, преобразованное в дробь: {r3.ToString()}");
                Console.WriteLine("\nХотите повторить ввод?(нет - 0, да - любая клавиша)");
            } while (Console.ReadLine() != "0");
        }


        //функции для демонстрации сравнения
        static string EqualZn(RationalNumber a, RationalNumber b)
        {
            if (a == b)
            {
                return "==";
            }
            return "!=";
        }
        static string Znak(RationalNumber a, RationalNumber b)
        {
            if (a > b)
            {
                return ">";
            }
            if (a < b)
            {
                return "<";
            }
            return ">=";
        }
        static string EqualZn(RationalNumber a, long b)
        {
            if (a == b)
            {
                return "==";
            }
            return "!=";
        }
        static string Znak(RationalNumber a, long b)
        {
            if (a > b)
            {
                return ">";
            }
            if (b > a)
            {
                return "<";
            }
            return ">=";
        }
    }
}
