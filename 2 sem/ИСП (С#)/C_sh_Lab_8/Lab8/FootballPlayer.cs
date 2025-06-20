using System;

namespace Lab8
{
    public delegate void Display(string mesage);
    class FootballPlayer : Sportsman, IFootballPlayer
    {
        private enum Positions
        {
            Goalkeeper,
            Defender,
            Midfielder,
            Forward
        }
        private string status = "Игрок основново состава";
        private Positions position;
        FootballPlayer[] players;                // для создания команды
        
        //событие на количество минут проведенных на поле 
        public event Display TimeOfPlay;

        //метод для вызова события Time
        public void PlayTime()
        {
            int time = new Random().Next(1, 97);
            TimeOfPlay?.Invoke($"Игрок {Surname} в последнем матче провел на поле {time} минут");
        }

        public static int CountF { get; private set; } = 0;

        // КОНСТРУКТОРЫ
        public FootballPlayer() { }
        public FootballPlayer(int count)
        {
            players = new FootballPlayer[count];
        }
        // основа+рост+вес (без отчества)
        public FootballPlayer(string name, string surname, string gender, string country, int age,
            int height, double weight, string teamName, char sport, int position, int number)
            : base(name, surname, gender, country, age, height, weight, teamName, sport)
        {
            ChoosePosition(position);
            Number = number;
            CountF++;
        }

        // основа+рост+вес (с отчеством)
        public FootballPlayer(string surname, string name, string patronymic, string gender, string country, int age,
            int height, double weight, string teamName, char sport, int position, int number)
            : base(surname, name, patronymic, gender, country, age, height, weight, teamName, sport)
        {
            ChoosePosition(position);
            Number = number;
            CountF++;
        }

        // МЕТОДЫ
        public new static void DisplayCount()
        {
            Console.WriteLine("Футболистов: {0}", CountF);
        }

        // выбор позиции из перечисления
        protected override void ChoosePosition(int position)
        {
            if (position == 1)
            {
                this.position = Positions.Goalkeeper;
            }
            if (position == 2)
            {
                this.position = Positions.Defender;
            }
            if (position == 3)
            {
                this.position = Positions.Midfielder;
            }
            if (position == 4)
            {
                this.position = Positions.Forward;
            }
        }

        // добавление данных при заполнении с клавиатуры
        public override void Add()
        {
            sport = Sports.Football;
            base.Add();
            Console.WriteLine("Выберите позицию: \n1 - Goalkeeper \n2 - Defender \n3 - Midfielder \n4 - Forward");
            bool stop;  // для проверки неверного ввода
            do
            {
                stop = true;
                switch (Console.ReadLine())
                {
                    case "1":
                        {
                            position = Positions.Goalkeeper;
                            break;
                        }
                    case "2":
                        {
                            position = Positions.Defender;
                            break;
                        }
                    case "3":
                        {
                            position = Positions.Midfielder;
                            break;
                        }
                    case "4":
                        {
                            position = Positions.Forward;
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
            CountF++;
        }

        // отображение
        public override void DisplayPerson()
        {
            base.DisplayPerson();
            Console.WriteLine($"Позиция: {position}\nИгровой номер: {Number}\nИгровой статус: {status}");
            Console.WriteLine("\n");
        }

        // ИНДЕКСАТОР
        public new FootballPlayer this[int x]
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

        //РЕАЛИЗАЦИЯ ИНТЕРФЕЙСА
        // выбор статуса игрока
        public void ChangeStatus(Display d)
        {
            bool stop;
            Console.WriteLine($"\nТекуший статус игрока {Surname}: {status}");
            do
            {
                stop = true;
                Console.WriteLine("Выберите статус игрока: \n1 - основа\n2 - запасной");
                switch (Console.ReadLine())
                {
                    case "1":
                        {
                            status = "Игрок основново состава";
                            break;
                        }
                    case "2":
                        {
                            status = "В запасном составе";
                            break;
                        }
                    default:
                        {
                            Console.WriteLine("Неверный ввод. ");
                            stop = false;
                            break;
                        }
                }
            } while (!stop);
            //Console.WriteLine($"Новый статус игрока {Surname}: {status}");
            d?.Invoke($"Новый статус игрока {Surname}: {status}");
        }
    }
}