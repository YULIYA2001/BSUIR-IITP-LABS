using System;
using System.Globalization;

namespace Lab2
{
    class UsingDateTime
    {
        public UsingDateTime()
        {
            string[] cultures = { "fr-FR", "en-US", "ru-RU", "es-ES", "de-DE", "it-IT" };
            string[] countries = { "Français", "English", "Русский", "Espanol", "Deutsch", "Italiano" };

            Console.WriteLine("0 - Exit");
            for (int i = 0; i < 6; i++)
            {
                Console.WriteLine($"{i + 1} - {countries[i]}");
            }
            int x;
            do
            {
                Console.WriteLine();
                Console.Write("Choose language: ");
                while (Int32.TryParse(Console.ReadLine(), out x) == false || x < 0 || x > 6) //проверка ввода на число
                {
                    Console.Write("Wrong input. Try again: ");
                }
                if (x == 0)
                {
                    break;
                }
                x--;
                Console.WriteLine("  " + countries[x] + ":");
                for (int i = 1; i <= 12; i++)
                {
                    DateTime month = new DateTime(2020, i, 1);     //инициализация нового экземпляра структуры
                    if (i < 10)
                    {
                        Console.Write(" ");
                    }
                    Console.Write(i + ".");
                    //преобразование значения объекта в строковое представление (указан формат и культура)
                    Console.WriteLine(month.ToString("MMMM", CultureInfo.CreateSpecificCulture(cultures[x])));
                }

            } while (true);
        }
    }
}
