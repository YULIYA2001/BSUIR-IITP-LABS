using System;
using System.Collections.Generic;
using System.Text;

namespace Lab6
{
    class Person : IPerson
    {
        private string name;
        protected string patronymic;
        private string gender;
        private int age;
        private int height;
        private double weight;
        Person[] people;          // для создания сразу массива людей 

        // КОНСТРУКТОРЫ
        protected Person() { }
        // для создания массива
        public Person(int count)
        {
            people = new Person[count];
        }
        // основное (без отчества)
        public Person(string name, string surname, string gender, string country, int age)
        {
            this.name = name;
            Surname = surname;
            this.gender = gender;
            Country = country;
            this.age = age;
            Count++;
        }
        // основное (с отчеством)
        public Person(string surname, string name, string patronymic, string gender, string country, int age)
        {
            this.name = name;
            Surname = surname;
            this.patronymic = patronymic;
            this.gender = gender;
            Country = country;
            this.age = age;
            Count++;
        }
        // основа+рост+вес (без отчества)
        public Person(string name, string surname, string gender, string country, int age,
            int height, double weight)
        {
            this.name = name;
            Surname = surname;
            this.gender = gender;
            Country = country;
            this.age = age;
            this.height = height;
            this.weight = weight;
            Count++;
        }
        // основа+рост+вес (с отчеством)
        public Person(string surname, string name, string patronymic, string gender, string country,
            int age, int height, double weight)
        {
            this.name = name;
            Surname = surname;
            this.patronymic = patronymic;
            this.gender = gender;
            Country = country;
            this.age = age;
            this.height = height;
            this.weight = weight;
            Count++;
        }

        // СВОЙСТВА
        public static int Count { get; private set; } = 0;         // СТАТИЧЕСКИЙ ЭЛЕМЕНТ
        public string Surname
        {
            get; set;
        }
        public string Country { get; set; } = "Беларусь";
        public virtual int Height
        {
            get
            {
                return height;
            }
            set
            {
                if (value > 40 && value < 300)
                {
                    height = value;
                }
                else
                {
                    Console.WriteLine($"\n{value} - неверный рост. Рост {name} {Surname} \"не установлен\"\n");
                    // будет приниматься как неустановленный и не будет виден при выводе
                    height = 0;   
                }
            }
        }
        public double Weight
        {
            get
            {
                return weight;
            }
            set
            {
                if (value > 0 && value < 800)
                {
                    weight = value;
                }
                else
                {
                    Console.WriteLine($"\n{value} - неверный вес. Вес {name} {Surname} \"не установлен\"\n");
                    // будет приниматься как неустановленный и не будет виден при выводе
                    weight = 0;  
                }
            }
        }
        public int Age
        {
            get
            {
                return age;
            }
            set
            {
                if (value > 0 && value < 200)
                {
                    age = value;
                }
                else
                {
                    Console.WriteLine($"{value} - неверный возраст. Введите число >0");
                    do
                    {
                        try
                        {
                            age = Convert.ToInt32(Console.ReadLine()); break;
                        }
                        catch (FormatException)
                        {
                            Console.Write("Введите правильный возраст (число > 0): ");
                        }
                    } while (true);
                }
            }
        }

        // МЕТОДЫ
        // вывод информации
        public static void DisplayCount()
        {
            Console.WriteLine("\nВсего людей: {0}\n", Count);
        }

        // проверка на гражданство Беларуси
        public void IsBelarussian()
        {
            if (Country == "Беларусь" || Country == "Belarus" || Country == "РБ")
            {
                Console.WriteLine($"{name} {Surname} белорус(ка).");
            }
            else
            {
                Console.WriteLine($"{name} {Surname} не белорус(ка).");
            }
        }

        // ПЕРЕГРУЗКА
        public void IsBelarussian(out bool check)
        {
            if (Country == "Беларусь" || Country == "Belarus" || Country == "РБ")
            {
                check = true;
            }
            else
            {
                check = false;
            }
        }

        // выбор пола
        private void ChooseGender()
        {
            Console.WriteLine("1 - муж., 2 - жен.");
            bool stop;
            do
            {
                stop = true;
                switch (Console.ReadLine())
                {
                    case "1":
                        {
                            gender = "муж.";
                            break;
                        }
                    case "2":
                        {
                            gender = "жен.";
                            break;
                        }
                    default:
                        {
                            Console.WriteLine("Неверный ввод. Введите снова");
                            stop = false;
                            break;
                        }
                }
            } while (!stop);
        }

        // добавление 
        public virtual void Add()
        {
            do
            {
                Console.WriteLine("Введите фамилию: ");
                Surname = Console.ReadLine();
            } while (Surname == "");
            do
            {
                Console.WriteLine("Введите имя: ");
                name = Console.ReadLine();
            } while (name == "");
            string ch;
            bool stop;
            // проверка наличия отчества
            do
            {
                stop = true;
                Console.WriteLine("Есть отчество? 1 - да, 2 - нет");
                if ((ch = Console.ReadLine()) == "1")
                {
                    do
                    { 
                        Console.WriteLine("Введите отчество: ");
                        patronymic = Console.ReadLine();
                    } while (patronymic == "");
                }
                else if (ch != "2")
                {
                    Console.WriteLine("Неверный ввод");
                    stop = false;
                }
            } while (!stop);
            Console.WriteLine("Выберите пол: ");
            ChooseGender();
            do
            {
                Console.WriteLine("Введите страну: ");
                Country = Console.ReadLine();
            } while (Country == "");
            Console.WriteLine("Введите возраст: ");
            // проверка ввода возраста на число в нужном диапазоне 
            do
            {
                try
                {
                    Age = Convert.ToInt32(Console.ReadLine());
                    if (Age < 15 || Age > 45)
                    {
                        throw new FormatException();
                    }
                    break;
                }
                catch (FormatException)
                {
                    Console.Write("Неверный ввод. Введите допустимый возраст (15 < число < 45): ");
                }
            } while (true);
            Console.WriteLine("Введите рост (в см): ");
            // проверка ввода роста на число в нужном диапазоне                 
            do
            {
                stop = true;
                try
                {
                    height = Convert.ToInt32(Console.ReadLine());
                    if (height < 140 || height > 300)
                    {
                        Console.Write("Неверный ввод. Введите допустимый рост (140 < число < 300): ");
                        stop = false;
                    }
                    else
                    {
                        break;
                    }
                }
                catch (FormatException)
                {
                    Console.Write("Неверный ввод. Введите допустимый рост (140 < число < 300): ");
                    stop = false;
                }
            } while (!stop);
            Console.WriteLine("Введите вес (в кг): ");
            // проверка ввода веса на число в нужном диапазоне 
            do
            {
                stop = true;
                try
                {
                    weight = Convert.ToDouble(Console.ReadLine());
                    if (weight < 50 || weight > 100)
                    {
                        Console.Write("Неверный ввод. Введите допустимый вес (50 < число < 100): ");
                        stop = false;
                    }
                    else
                    {
                        break;
                    }
                }
                catch (FormatException)
                {
                    Console.Write("Неверный ввод. Введите допустимый вес (50 < число < 100): ");
                    stop = false;
                }
            } while (!stop);
            Count++;
        }

        // имя фамилия страна пол возраст
        protected void DisplayPerson1()
        {
            Console.Write($"{name} {Surname} \nСтрана: {Country} \nПол: {gender} \nВозраст: {age} ");
        }

        // фамилия имя отчество страна пол возраст
        protected void DisplayPerson2()
        {
            Console.Write($"{Surname} {name} {patronymic}\nСтрана: {Country}\nПол: {gender}\nВозраст: {age}");
        }

        // ИНДЕКСАТОР
        public Person this[int x]
        {
            get
            {
                return people[x];
            }
            set
            {
                people[x] = value;
            }
        }

        //РЕАЛИЗАЦИЯ ИНТЕРФЕЙСА
        public virtual void DisplayPerson()
        {
            if (patronymic == null)
            {
                DisplayPerson1();
            }
            else
            {
                DisplayPerson2();
            }
            if (height != 0)
            {
                Console.Write($"\nРост: {height} см");
            }
            if (weight != 0)
            {
                Console.Write($"\nВес: {weight} кг");
            }
            Console.WriteLine("\n");
        }
    }
}
