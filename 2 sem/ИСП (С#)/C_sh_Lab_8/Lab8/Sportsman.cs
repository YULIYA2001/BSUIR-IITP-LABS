using System;

namespace Lab8
{
    class Sportsman : Person, ISportsman
    {
        public enum Sports            // виды спорта
        {
            Basketball = 1,
            Football,
            Volleyball
        }
        private enum Health            // состояния здоровья
        {
            Healthy,
            Injured,
            Individual_Training
        }
        struct Team                         // свединия о команде спортсмена
        {
            public int awardsAmount;
            public string teamName;

            public Team(string teamName)
            {
                awardsAmount = 0;
                this.teamName = teamName;
            }
        }
        protected Sports sport;
        private Health healthStatus = Health.Healthy;
        private Team team;
        private int number;
        Sportsman[] sportsmen;          // для создания сразу массива людей    
        public delegate void ResultOf(string message);
        // событие на результат последней игры
        public event ResultOf LastGame;           
        // событие на смену состояния здоровья
        public event ResultOf HealthStatus;    
        
        public Sports Sport { get { return sport; } }
        protected int Number
        {
            get
            {
                return number;
            }
            set
            {
                if (value > 0)
                {
                    number = value;
                }
                else
                {
                    Console.WriteLine($"{value} - недопустимо. Введите число >0");
                    do
                    {
                        try
                        {
                            number = Convert.ToInt32(Console.ReadLine()); break;
                        }
                        catch (FormatException)
                        {
                            Console.Write("Введите правильный номер (число > 0): ");
                        }
                    } while (true);
                }
            }
        }

        // КОНСТРУКТОРЫ
        public Sportsman() { }
        // для создания массива людей
        public Sportsman(int count)
        {
            if (count > 0)
                sportsmen = new Sportsman[count];
        }

        // основа+рост+вес (без отчества)
        public Sportsman(string name, string surname, string gender, string country, int age,
            int height, double weight, string teamName, char sport)
            : base(name, surname, gender, country, age, height, weight)
        {
            if (sport == 'B')
            {
                this.sport = Sports.Basketball;
            }
            if (sport == 'F')
            {
                this.sport = Sports.Football;
            }
            if (sport == 'V')
            {
                this.sport = Sports.Volleyball;
            }
            team = new Team(teamName);
        }

        // основа+рост+вес (с отчеством)
        public Sportsman(string surname, string name, string patronymic, string gender, string country, int age,
            int height, double weight, string teamName, char sport)
            : base(surname, name, patronymic, gender, country, age, height, weight)
        {
            if (sport == 'B')
                this.sport = Sports.Basketball;
            if (sport == 'F')
                this.sport = Sports.Football;
            if (sport == 'V')
                this.sport = Sports.Volleyball;
            team = new Team(teamName);
        }

        // МЕТОДЫ
        // общее число спортсменов
        public new static void DisplayCount()
        {
            Console.WriteLine("Всего спортсменов: {0}\n", Count);
        }

        public override void Add()
        {
            // Console.WriteLine("Выберите вид спорта: ");
            // ChooseSport();
            base.Add();
            do
            {
                Console.WriteLine("Введите название команды: ");
                team.teamName = Console.ReadLine();
                if (team.teamName == "")
                {
                    Console.Write("Вы не ввели название. ");
                }
            } while (team.teamName == "");
        }

        // выбор вида спорта
        public void ChooseSport()
        {
            bool stop;  // для проверки неверного ввода
            do
            {
                stop = true;
                Console.WriteLine("Выберите спорт: 1 - Basketball, 2 - Football, 3 - Volleyball");
                switch (Console.ReadLine())
                {
                    case "1":
                        {
                            sport = Sports.Basketball;
                            break;
                        }
                    case "2":
                        {
                            sport = Sports.Football;
                            break;
                        }
                    case "3":
                        {
                            sport = Sports.Volleyball;
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
        }

        // смена состояния здоровья (событие HealthStatus)
        public void ChangeHealthStatus()
        {
            bool stop;
            //Console.WriteLine($"\nCurrent status of {Surname} is {healthStatus}");
            HealthStatus?.Invoke($"\nCurrent status of {Surname} is {healthStatus}");
            do
            {
                stop = true;
                Console.WriteLine("Choose: 1 - healthy, 2 - injured, 3 - individual recovery training");
                switch (Console.ReadLine())
                {
                    case "1":
                        {
                            healthStatus = Health.Healthy;
                            break;
                        }
                    case "2":
                        {
                            healthStatus = Health.Injured;
                            break;
                        }
                    case "3":
                        {
                            healthStatus = Health.Individual_Training;
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
            //Console.WriteLine("New status of {1} is {0}\n", healthStatus, Surname);
            HealthStatus?.Invoke($"New status of {Surname} is {healthStatus}\n");
        }

        // метод для вызова события LastGame
        public void ResultOfGame()
        {
            string result = new Random().Next(2) == 0 ? "ВЫИГРАЛ" : "ПРОИГРАЛ";
            LastGame?.Invoke($"Игрок {Surname} {result} последнюю игру.");
        }

        // смена команды (метод, принимающий делегат)
        public void NewTeam(ResultOf d)
        {
            string tName;
            do
            {
                Console.WriteLine("Введите название новой команды");
                tName = Console.ReadLine();
            } while (tName == "");
            team.teamName = tName;
            //Console.WriteLine($"\nИгрок {Surname} перешел в команду {team.teamName}\n");
            d?.Invoke($"\nИгрок {Surname} перешел в команду {team.teamName}\n");            
        }

        // получение награды
        public void GiveAward()
        {
            int amount = 0;
            Console.WriteLine("Сколько наград добавить?");
            bool stop;
            do
            {
                stop = true;
                try
                {
                    amount = Convert.ToInt32(Console.ReadLine());
                    if (amount < 0)
                    {
                        //генерация исключения
                        throw new FormatException();
                    }
                }
                catch (FormatException)
                {
                    Console.Write("Неверный ввод. Введите число(>0): ");
                    stop = false;
                }
            } while (!stop);
            team.awardsAmount += amount;
            Console.WriteLine($"У игрока {Surname} наград стало: {team.awardsAmount}.\n");
        }

        public override void DisplayPerson()
        {
            if (patronymic == null)
            {
                DisplayPerson1();
            }
            else
            {
                DisplayPerson2();
            }
            Console.WriteLine($"\nРост: {Height} см \nВес: {Weight} кг \nСостояние здоровья: {healthStatus} " +
                $"\nВид спорта: {sport} \nНазвание команды: {team.teamName} \nКоличество наград: " +
                $"{team.awardsAmount}");
        }

        protected virtual void ChoosePosition(int position) { }

        // ИНДЕКСАТОР
        public new Sportsman this[int x]
        {
            get
            {
                return sportsmen[x];
            }
            set
            {
                sportsmen[x] = value;
            }
        }

        //РЕАЛИЗАЦИЯ ИНТЕРФЕЙСА
        //IComparable
        public int CompareTo(Sportsman s)
        {
            return this.Surname.CompareTo(s.Surname);
        }

        //IComparer
        public int Compare(Sportsman s1, Sportsman s2)
        {
            if (s1.team.awardsAmount > s2.team.awardsAmount)
            {
                return -1;
            }
            else if (s1.team.awardsAmount < s2.team.awardsAmount)
            {
                return 1;
            }
            else return 0;
        }
        //ISportsman
        public void IsReadyToPlay()
        {
            if (healthStatus == Health.Healthy)
            {
                Console.WriteLine($"Игрок {Surname} готов к игре (здоров).");
            }
            else
            {
                Console.WriteLine($"Игрок {Surname} не может играть по состоянию здоровья ({healthStatus}).");
            }
        }
    }
}