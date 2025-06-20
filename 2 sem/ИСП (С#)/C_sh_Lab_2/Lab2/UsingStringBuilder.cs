using System;
using System.Collections.Generic;
using System.Text;

namespace Lab2
{
    class UsingStringBuilder
    {
        public UsingStringBuilder()
        {
            StringBuilder sb = new StringBuilder();
            string str;
            bool cursiveLetter;
            do
            {
                Console.WriteLine("Введите строку только строчных английских букв:");
                str = Console.ReadLine();
                cursiveLetter = false;
                for (int i = 0; i < str.Length; i++)
                {
                    if (str[i] < 'a' || str[i] > 'z')
                        cursiveLetter = true;
                }
                if (cursiveLetter)
                    Console.WriteLine("Неверный ввод.");
            } while (cursiveLetter == true);
            sb.Append(str);
            ChangeLetter(sb);
            Console.WriteLine("Буквы после гласных заменены на следующие по алфавиту:");
            Console.WriteLine(sb.ToString());
            Console.WriteLine("Алфавит: a-b-c-d-e-f-g-h-i-j-k-l-m-n-o-p-q-r-s-t-u-v-w-x-y-z(a)");
        }

        static void ChangeLetter(StringBuilder sb)
        {
            for (int i = sb.Length - 2; i >= 0; i--)
            {
                if (sb[i] == 'a' || sb[i] == 'e' || sb[i] == 'i' || sb[i] == 'o' || sb[i] == 'u' || sb[i] == 'y')
                {
                    if (sb[i + 1] == 'z')
                    {
                        sb.Insert(i + 1, 'a');
                    }
                    else
                        sb.Insert(i + 1, Convert.ToChar(Convert.ToInt32(sb[i + 1]) + 1));
                    sb.Remove(i + 2, 1);
                }
            }
        }
    }
}
