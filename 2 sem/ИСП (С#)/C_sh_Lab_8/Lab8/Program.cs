using System;
using System.Collections.Generic;

namespace Lab8
{
    class Program
    {
        static void Main(string[] args)
        {
            List<Sportsman> sportsmen = new List<Sportsman>(10);
            List<FootballPlayer> football = new List<FootballPlayer>(5);
            // бесконечный цикл для работы в программе
            do
            {
                Console.WriteLine("1 - Добавить игрока\n2 - Просмотр всего списка\n3 - Проверить на" +
                    " гражданство беларуси\n4 - Число спортсменов в списке\n5 - Смена состояния здоровья" +
                    "\n6 - Смена команды\n7 - Добавление наград\n8 - Смена игрового статуса футболиста" +
                    "\n9 - Сортировка\n10 - Проверка готовности игрока\n11 - Результат последней игры" +
                    "\n12 - Время футболиста на поле\n00 - Автозаполнение\n0 - Выход");
                switch (Console.ReadLine())
                {
                    case "1":
                        {
                            Console.WriteLine();
                            Sportsman s = new Sportsman();
                            s.ChooseSport();
                            switch (Convert.ToString(s.Sport))
                            {
                                case "Football":
                                    {
                                        s = new FootballPlayer();
                                        s.Add();
                                        sportsmen.Add(s);
                                        football.Add((FootballPlayer)s);
                                        break;
                                    }
                                case "Basketball":
                                    {
                                        s = new BasketballPlayer();
                                        s.Add();
                                        sportsmen.Add(s);
                                        break;
                                    }
                                case "Volleyball":
                                    {
                                        s = new VolleyballPlayer();
                                        s.Add();
                                        sportsmen.Add(s);
                                        break;
                                    }
                            }
                            break;
                        }
                    case "2":
                        {
                            // проверка на наличие спортсменов в списке
                            Console.WriteLine();
                            if (sportsmen.Count == 0)
                            {
                                Console.WriteLine("Список пуст. Добавте спортсменов (нажмите 1 или 00)");
                            }
                            else
                            {
                                int i = 1;
                                foreach (Sportsman s in sportsmen)
                                {
                                    Console.WriteLine("Игрок {0} \n--------------------------", i++);
                                    s.DisplayPerson();
                                }
                            }
                            break;
                        }
                    case "3":
                        {
                            // проверка на наличие спортсменов в списке
                            Console.WriteLine();
                            if (sportsmen.Count == 0)
                            {
                                Console.WriteLine("Список пуст. Добавте спортсменов (нажмите 1 или 00)");
                            }
                            else
                            {
                                foreach (Sportsman s in sportsmen)
                                {
                                    s.IsBelarussian();
                                }
                            }
                            break;
                        }
                    case "4":
                        {
                            // проверка на наличие спортсменов в списке
                            Console.WriteLine();
                            if (sportsmen.Count == 0)
                            {
                                Console.WriteLine("Список пуст. Добавте спортсменов (нажмите 1 или 00)");
                            }
                            else
                            {
                                Sportsman.DisplayCount();
                                BasketballPlayer.DisplayCount();
                                VolleyballPlayer.DisplayCount();
                                FootballPlayer.DisplayCount();
                            }
                            break;
                        }
                    case "5":
                        {
                            // проверка на наличие спортсменов в списке
                            if (sportsmen.Count == 0)
                            {
                                Console.WriteLine("\nСписок пуст. Добавте спортсменов (нажмите 1 или 00)");
                            }
                            else
                            {
                                // обработчик события HealthStatus - делегат с анонимным методом
                                int i = ChooseFromList(sportsmen);
                                Sportsman.ResultOf r = delegate (string mes)
                                {
                                    Console.WriteLine(mes);
                                };
                                sportsmen[i].HealthStatus += r;
                                sportsmen[i].ChangeHealthStatus();
                                sportsmen[i].HealthStatus -= r;
                            }
                            break;
                        }
                    case "6":
                        {
                            // проверка на наличие спортсменов в списке
                            if (sportsmen.Count == 0)
                            {
                                Console.WriteLine("\nСписок пуст. Добавте спортсменов (нажмите 1 или 00)");
                            }
                            else
                            {
                                //метод, принимающий делегат
                                sportsmen[ChooseFromList(sportsmen)].NewTeam(new Sportsman.ResultOf(Display));
                            }
                            break;
                        }
                    case "7":
                        {
                            // проверка на наличие спортсменов в списке
                            if (sportsmen.Count == 0)
                            {
                                Console.WriteLine("\nСписок пуст. Добавте спортсменов (нажмите 1 или 00)");
                            }
                            else
                            {
                                sportsmen[ChooseFromList(sportsmen)].GiveAward();
                            }
                            break;
                        }
                    case "8":
                        {
                            // проверка на наличие спортсменов в списке
                            if (FootballPlayer.CountF == 0)
                            {
                                Console.WriteLine("\nВ списоке нет футболистов (нажмите 1 для добавления)");
                            }
                            else
                            {
                                //метод, принимающий делегат
                                football[ChooseFootballPlayer(football)].ChangeStatus(new Display(Display));
                            }
                            break;
                        }
                    case "9":
                        {
                            // проверка на наличие спортсменов в списке
                            Console.WriteLine();
                            if (sportsmen.Count == 0)
                            {
                                Console.WriteLine("Список пуст. Добавте спортсменов (нажмите 1 или 00)");
                            }
                            else
                            {
                                bool stop;
                                do
                                {
                                    stop = true;
                                    Console.WriteLine("Сортировка: 1 - по фамилии, 2 - количеству наград");
                                    switch (Console.ReadLine())
                                    {
                                        case "1":
                                            {
                                                Console.WriteLine("\nСортировка по фамилии:" +
                                                    "\n----------------------");
                                                sportsmen.Sort();
                                                int i = 1;
                                                foreach (Sportsman s in sportsmen)
                                                {
                                                    Console.WriteLine("Игрок {0} " +
                                                        "\n--------------------------", i++);
                                                    s.DisplayPerson();
                                                }
                                                break;
                                            }
                                        case "2":
                                            {
                                                Console.WriteLine("\nСортировка по количеству наград:" +
                                                    "\n-------------------------------");
                                                sportsmen.Sort(new Sportsman());
                                                int i = 1;
                                                foreach (Sportsman s in sportsmen)
                                                {
                                                    Console.WriteLine("Игрок {0} " +
                                                        "\n--------------------------", i++);
                                                    s.DisplayPerson();
                                                }
                                                break;
                                            }
                                        default:
                                            {
                                                Console.Write("Неверный ввод. Попробуйте снова: ");
                                                stop = false;
                                                break;
                                            }
                                    }
                                } while (!stop);
                            }
                            break;
                        }
                    case "10":
                        {
                            // проверка на наличие спортсменов в списке
                            Console.WriteLine();
                            if (sportsmen.Count == 0)
                            {
                                Console.WriteLine("Список пуст. Добавте спортсменов (нажмите 1 или 00)");
                            }
                            else
                            {
                                sportsmen[ChooseFromList(sportsmen)].IsReadyToPlay();
                            }
                            break;
                        }
                    case "11":
                        {
                            // проверка на наличие спортсменов в списке
                            Console.WriteLine();
                            if (sportsmen.Count == 0)
                            {
                                Console.WriteLine("Список пуст. Добавте спортсменов (нажмите 1 или 00)");
                            }
                            else
                            {
                                // обработчик события LastGame - делегат с лямбда-выражением
                                int i = ChooseFromList(sportsmen);
                                Sportsman.ResultOf r = mes => Console.WriteLine(mes);
                                sportsmen[i].LastGame += r;
                                sportsmen[i].ResultOfGame();
                                sportsmen[i].LastGame -= r;
                            }
                            break;
                        }
                    case "12":
                        {
                            // проверка на наличие спортсменов в списке
                            if (FootballPlayer.CountF == 0)
                            {
                                Console.WriteLine("\nВ списоке нет футболистов (нажмите 1 для добавления)");
                            }
                            else
                            {
                                // обработчик события Time - метод
                                int i = ChooseFootballPlayer(football);
                                football[i].TimeOfPlay += Display;
                                football[i].PlayTime();
                                football[i].TimeOfPlay -= Display;
                            }
                            break;
                        }
                    case "00":
                        {
                            //проверка и недопуск повторного автозаполнения
                            if (sportsmen.Count >= 5 && football.Count >= 3)
                            {
                                int counter = 0;
                                string[] arr = { "Стасевич", "Duarte", "Нехайчик", "Веремееенко", "Бирюкова" };
                                for (int i = 0; i < sportsmen.Count; i++)
                                {
                                    for (int j = 0; j < 5; j++)
                                    {
                                        if (sportsmen[i].Surname == arr[j])
                                        {
                                            counter++;
                                        }
                                    }
                                }
                                if (counter == 5)
                                {
                                    Console.WriteLine("\nПовторное автозаполнение недопустимо" +
                                        " (можно использовать 1 раз).");
                                }
                            }
                            else     // первичное автозаполнение
                            {
                                Sportsman s;
                                s = new FootballPlayer("Стасевич", "Игорь", "Николаевич", "муж.", "Беларусь",
                                    34, 178, 77, "\"БАТЭ\"(Беларусь)", 'F', 3, 22);
                                sportsmen.Add(s);
                                football.Add((FootballPlayer)s);
                                s = new FootballPlayer("Denish", "Duarte", "male", "Portugal", 26,
                                    190, 84, "\"Динамо-Брест\"(Беларусь)", 'F', 2, 3);
                                sportsmen.Add(s);
                                football.Add((FootballPlayer)s);
                                s = new FootballPlayer("Нехайчик", "Павел", "Александрович", "муж.", "Беларусь",
                                    31, 180, 70, "\"БАТЭ\"(Беларусь)", 'F', 3, 33);
                                sportsmen.Add(s);
                                football.Add((FootballPlayer)s);
                                s = new BasketballPlayer("Веремееенко", "Анастасия", "Владимировна",
                                    "жен.", "Эстония", 32, 193, 82, "\"Надежда\"(Россия)", 'B', 1, 11);
                                sportsmen.Add(s);
                                s = new VolleyballPlayer("Бирюкова", "Ольга", " Николаевна", "жен.", "Россия",
                                    25, 194, 74, "\"Динамо-Казань\"", 'V', 2, 10);
                                sportsmen.Add(s);
                                Console.WriteLine("\nВ список добавлены 3 футболиста, волейболистка, " +
                                    "баскетболистка");
                            }
                            break;
                        }
                    case "0":
                        {
                            Console.WriteLine();
                            Console.WriteLine("Вы вышли из программы");
                            return;
                        }
                    default:
                        {
                            Console.WriteLine();
                            Console.WriteLine("Неверный ввод. Попробуйте снова");
                            break;
                        }
                }
                Console.WriteLine();
            } while (true);
        }

        //выбор игрока из списка
        static int ChooseFromList(List<Sportsman> sportsmen)
        {
            //выбор игрока по положению в списке (с проверкой на ввод)
            Console.WriteLine("\nВыберите игрока:");
            int i = 1;
            foreach (Sportsman s in sportsmen)
            {
                Console.WriteLine($"{i++} - {s.Surname}({s.Sport})");
            }
            Console.WriteLine();
            bool stop;
            do
            {
                stop = true;
                try
                {
                    i = Convert.ToInt32(Console.ReadLine());
                    if (i < 1 || i > Sportsman.Count)
                    {
                        throw new FormatException();
                    }
                }
                catch (FormatException)
                {
                    Console.Write("Неверный ввод. Введите снова: ");
                    stop = false;
                }
            } while (!stop);
            return --i;
        }

        //выбор футболиста из списка футболистов
        static int ChooseFootballPlayer(List<FootballPlayer> football)
        {
            // (с проверкой номера на ввод)
            Console.WriteLine("\nВыберите игрока:");
            int i = 1;
            foreach (FootballPlayer f in football)
            {
                Console.WriteLine($"{i++} - {f.Surname}");
            }
            Console.WriteLine();
            bool stop;
            do
            {
                stop = true;
                try
                {
                    i = Convert.ToInt32(Console.ReadLine());
                    if (i < 1 || i > FootballPlayer.CountF)
                    {
                        throw new FormatException();
                    }
                }
                catch (FormatException)
                {
                    Console.Write("Неверный ввод. Введите снова: ");
                    stop = false;
                }
            } while (!stop);
            return --i;
        }

        // отображение(обработчик события в case 12 и метод для делегатов в case 6 и 8)
        static void Display(string mes)
        {
            Console.WriteLine(mes);
        }
    }
}