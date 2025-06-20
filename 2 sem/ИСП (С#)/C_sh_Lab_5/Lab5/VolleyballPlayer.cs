using System;
using System.Collections.Generic;
using System.Text;

namespace Lab5
{
    class VolleyballPlayer : Sportsman
    {
        private enum Positions
        {
            Setter, 
            Outside_Hitter, 
            Middle_Hitter, 
            Opposite_Hitter, 
            Libero
        }        
        private Positions position;
        VolleyballPlayer[] players;                      //для создания команды

        public static int CountV { get; private set; } = 0;       

        //КОНСТРУКТОРЫ
        public VolleyballPlayer() { }
        public VolleyballPlayer(int count)
        {
            players = new VolleyballPlayer[count];
        }

        //основа+рост+вес (без отчества)
        public VolleyballPlayer(string name, string surname, string gender, string country, int age,
            int height, double weight, string teamName, char sport, int position, int number)
            : base(name, surname, gender, country, age, height, weight, teamName, sport)
        {
            ChoosePosition(position);
            Number = number;
            CountV++;
        }

        //основа+рост+вес (с отчеством)
        public VolleyballPlayer(string surname, string name, string patronymic, string gender, string country, int age,
            int height, double weight, string teamName, char sport, int position, int number)
            : base(surname, name, patronymic, gender, country, age, height, weight, teamName, sport)
        {
            ChoosePosition(position);
            Number = number;
            CountV++;
        }

        //МЕТОДЫ
        public new static void DisplayCount()
        {
            Console.WriteLine("Волейболистов: {0}", CountV);
        }
        //выбор позиции из перечисления
        protected override void ChoosePosition(int position)
        {
            if (position == 1)
            {
                this.position = Positions.Setter;
            }
            if (position == 2)
            {
                this.position = Positions.Outside_Hitter;
            }
            if (position == 3)
            {
                this.position = Positions.Middle_Hitter;
            }
            if (position == 4)
            {
                this.position = Positions.Opposite_Hitter;
            }
            if (position == 5)
            {
                this.position = Positions.Libero;
            }
        }

        //добавление данных при заполнении с клавиатуры
        public override void Add()
        {
            sport = Sports.Volleyball;
            base.Add();
            Console.WriteLine("Выберите позицию: \n1 - Setter \n2 - Outside_Hitter \n3 - Middle_Hitter \n" +
                "4 - Opposite_Hitter \n5 - Libero");
            bool stop;  //для проверки неверного ввода
            do
            {
                stop = true;
                switch (Console.ReadLine())
                {
                    case "1":
                        {
                            position = Positions.Setter;
                            break;
                        }
                    case "2":
                        {
                            position = Positions.Outside_Hitter;
                            break;
                        }
                    case "3":
                        {
                            position = Positions.Middle_Hitter;
                            break;
                        }
                    case "4":
                        {
                            position = Positions.Opposite_Hitter;
                            break;
                        }
                    case "5":
                        {
                            position = Positions.Libero;
                            break;
                        }
                    default:
                        {
                            Console.WriteLine("Неверный ввод. Попробуйте снова");
                            stop = false;
                            break;
                        }
                }
            } while (!stop);
            Console.WriteLine("Введите игровой номер:");
            //проверка ввода номера на число >0 
            do
            {
                try
                {
                    Number = Convert.ToInt32(Console.ReadLine()); break;
                }
                catch (FormatException)
                {
                    Console.Write("Неверный ввод. Введите правильный номер (число > 0): ");
                }
            } while (true);
            CountV++;
        }
        //отображение
        public override void DisplayPerson()
        {
            base.DisplayPerson();
            Console.WriteLine($"позиция: {position}\nигровой номер: {Number}");
            Console.WriteLine("\n");
        }

        //ИНДЕКСАТОР
        public new VolleyballPlayer this[int x]
        {
            get
            {
                return players[x];
            }
            set
            {
                players[x] = value;
            }
        }
    }
}
