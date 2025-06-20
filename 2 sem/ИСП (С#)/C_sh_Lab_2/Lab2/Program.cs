using System;

namespace Lab2
{
    class Program
    {
        static void Main(string[] args)
        {
            while (true)
            {
                Console.WriteLine("\nChoose task (0 to exit):");
                Console.WriteLine("1 - task 8");
                Console.WriteLine("2 - task 10");
                Console.WriteLine("3 - task 15");
                Console.WriteLine("0 - exit");
                int num;
                num = Convert.ToInt32(Console.ReadKey().KeyChar) - '0';
                Console.Write("\n\n");
                switch (num)
                {
                    case 0:
                        {
                            Console.WriteLine("Successfully exit");
                            return;
                        }
                    case 1:
                        {
                            new UsingDateTime();
                            break;
                        }
                    case 2:
                        {
                            new UsingStringAndMath();
                            break;
                        }
                    case 3:
                        {
                            new UsingStringBuilder();
                            break;
                        }
                    default:
                        {
                            Console.WriteLine("Wrong input. Try again");
                            break;
                        }
                }
            }
            //Console.ReadKey();    
        }
    }
}
