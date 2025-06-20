using System;
using System.Collections.Generic;
using System.Text;

namespace Lab5
{
    class Sportsman : Person
    {
        protected enum Sports            //виды спорта
        {
            Basketball = 1,
            Football,
            Volleyball
        }
        private enum Health            //состояния здоровья
        {
            Healthy,
            Injured, 
            Individual_Training
        }
        struct Team                         //свединия о команде спортсмена
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
        Sportsman[] sportsmen;          //для создания сразу массива людей 

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

        //КОНСТРУКТОРЫ
        public Sportsman() { }
        //для создания массива людей
        public Sportsman(int count)
        {
            if (count > 0)
                sportsmen = new Sportsman[count];
        }

        //основа+рост+вес (без отчества)
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

        //основа+рост+вес (с отчеством)
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

        //МЕТОДЫ
        //общее число спортсменов
        public new static void DisplayCount()
        {
            Console.WriteLine("Всего спортсменов: {0}\n", Count);
        }

        public override void Add()
        {
            //Console.WriteLine("Выберите вид спорта: ");
            //ChooseSport();
            base.Add();
            Console.WriteLine("Введите название команды: ");
            team.teamName = Console.ReadLine();                        
        }
                //выбор вида спорта
        private void ChooseSport()
        {
            bool stop;  //для проверки неверного ввода
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

        // смена состояния здоровья
        public void ChangeHealthStatus()
        {
            bool stop;
            Console.WriteLine($"Current status of {Surname} is {healthStatus}");
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
            Console.WriteLine("\nNew status is {0}\n", healthStatus);
        }

        //смена команды
        public void NewTeam()
        {
            Console.WriteLine("Введите название новой команды");
            string tName = Console.ReadLine();
            team.teamName = tName;
            Console.WriteLine($"\nИгрок {Surname} перешел в команду {team.teamName}\n");
        }

        //получение награды
        public void GiveAward()
        {
            team.awardsAmount++;
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
            Console.WriteLine($"\nрост: {Height} см \nвес: {Weight} кг \nсостояние здоровья: {healthStatus} " +
                $"\nвид спорта: {sport} \nназвание команды: {team.teamName} \nколичество наград: " +
                $"{team.awardsAmount}");
        }

        protected virtual void ChoosePosition(int position) { }

        //ИНДЕКСАТОР
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
    }
}

