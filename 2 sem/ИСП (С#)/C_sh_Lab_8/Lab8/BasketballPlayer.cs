using System;

namespace Lab8
{
    class BasketballPlayer : Sportsman
    {
        private enum Positions
        {
            Centre,
            Power_Forward,
            Small_Forward,
            Shooting_Guard,
            Point_Guard
        }
        private Positions position;
        BasketballPlayer[] players;                 // для создания команды

        public static int CountB { get; private set; } = 0;

        // КОНСТРУКТОРЫ
        public BasketballPlayer() { }
        public BasketballPlayer(int count)
        {
            players = new BasketballPlayer[count];
        }

        // основа+рост+вес (без отчества)
        public BasketballPlayer(string name, string surname, string gender, string country, int age,
            int height, double weight, string teamName, char sport, int position, int number)
            : base(name, surname, gender, country, age, height, weight, teamName, sport)
        {
            ChoosePosition(position);
            Number = number;
            CountB++;
        }

        // основа+рост+вес (с отчеством)
        public BasketballPlayer(string surname, string name, string patronymic, string gender, string country, int age,
            int height, double weight, string teamName, char sport, int position, int number)
            : base(surname, name, patronymic, gender, country, age, height, weight, teamName, sport)
        {
            ChoosePosition(position);
            Number = number;
            CountB++;
        }

        // МЕТОДЫ
        public new static void DisplayCount()
        {
            Console.WriteLine("Баскетболистов: {0}", CountB);
        }

        // выбор позиции из перечисления
        protected override void ChoosePosition(int position)
        {
            if (position == 1)
            {
                this.position = Positions.Centre;
            }
            if (position == 2)
            {
                this.position = Positions.Power_Forward;
            }
            if (position == 3)
            {
                this.position = Positions.Small_Forward;
            }
            if (position == 4)
            {
                this.position = Positions.Shooting_Guard;
            }
            if (position == 5)
            {
                this.position = Positions.Point_Guard;
            }
        }

        // добавление данных при заполнении с клавиатуры
        public override void Add()
        {
            sport = Sports.Basketball;
            base.Add();
            Console.WriteLine("Выберите позицию: \n1 - Centre \n2 - Power_Forward \n3 - Small_Forward \n" +
                "4 - Shooting_Guard \n5 - Point_Guard");
            bool stop;  // для проверки неверного ввода
            do
            {
                stop = true;
                switch (Console.ReadLine())
                {
                    case "1":
                        {
                            position = Positions.Centre;
                            break;
                        }
                    case "2":
                        {
                            position = Positions.Power_Forward;
                            break;
                        }
                    case "3":
                        {
                            position = Positions.Small_Forward;
                            break;
                        }
                    case "4":
                        {
                            position = Positions.Shooting_Guard;
                            break;
                        }
                    case "5":
                        {
                            position = Positions.Point_Guard;
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
            // проверка ввода номера на число >0 
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
            CountB++;
        }

        // отображение
        public override void DisplayPerson()
        {
            base.DisplayPerson();
            Console.WriteLine($"Позиция: {position}\nИгровой номер: {Number}");
            Console.WriteLine("\n");
        }

        // ИНДЕКСАТОР
        public new BasketballPlayer this[int x]
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
