using System;
using System.Collections.Generic;
using System.Text;

namespace Lab5
{
    class Person
    {
        private string name;
        protected string patronymic;
        private string gender;
        private int age;
        private int height;
        private double weight;
        Person[] people;          //для создания сразу массива людей 

        //КОНСТРУКТОРЫ
        protected Person() { }
            //для создания массива
            public Person(int count)
        {
            people = new Person[count];
        }
        //основное (без отчества)
        public Person(string name, string surname, string gender, string country, int age)
        {
            this.name = name;
            Surname = surname;
            this.gender = gender;
            Country = country;
            this.age = age;
            Count++;
        }
        //основное (с отчеством)
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
        //основа+рост+вес (без отчества)
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
        //основа+рост+вес (с отчеством)
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

        //СВОЙСТВА
        public static int Count { get; private set; } = 0;         //СТАТИЧЕСКИЙ ЭЛЕМЕНТ
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
                    height = 0;   //будет приниматься как неустановленный и не будет виден при выводе
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
                    weight = 0;   //будет приниматься как неустановленный и не будет виден при выводе
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

        //МЕТОДЫ
        //вывод информации
        public static void DisplayCount()
        {
            Console.WriteLine("\nВсего людей: {0}\n", Count);
        }
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
                Console.Write($"\nрост: {height} см");
            }
            if (weight != 0)
            {
                Console.Write($"\nвес: {weight} кг");
            }
            Console.WriteLine("\n");
        }
        // имя фамилия страна пол возраст
        protected void DisplayPerson1()
        {
            Console.Write($"{name} {Surname} \nстрана: {Country} \nпол: {gender} \nвозраст: {age} ");
        }
        //фамилия имя отчество страна пол возраст
        protected void DisplayPerson2()
        {
            Console.Write($"{Surname} {name} {patronymic} \nстрана: {Country} \nпол: {gender} \nвозраст: {age} ");
        }
        //проверка на гражданство Беларуси
        public void IsBelarussian()
        {
            if (Country == "Беларусь" || Country == "Belarus" || Country == "РБ")
            {
                Console.WriteLine($"\n{name} {Surname} белорус(ка).");
            }
            else
            {
                Console.WriteLine($"\n{name} {Surname} не белорус(ка).");
            }
        }
        //ПЕРЕГРУЗКА
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

        private void ChooseGender()
        {
            Console.WriteLine("1 - муж., 2 - жен.");
            bool stop;
            do
            {
                stop = true;
                switch(Console.ReadLine())
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

        public virtual void Add()
        {
            Console.WriteLine("Введите фамилию: ");
            Surname = Console.ReadLine();
            Console.WriteLine("Введите имя: ");
            name = Console.ReadLine();
            string ch;
            bool stop;
            //проверка наличия отчества
            do
            {
                stop = true;
                Console.WriteLine("Есть отчество? 1 - да, 2 - нет");
                if ((ch = Console.ReadLine()) == "1")
                {
                    Console.WriteLine("Введите отчество: ");
                    patronymic = Console.ReadLine();
                }
                else if (ch != "2")
                {
                    Console.WriteLine("Неверный ввод");
                    stop = false;
                }
            } while (!stop);
            Console.WriteLine("Выберите пол: ");
            ChooseGender();
            Console.WriteLine("Введите страну: ");
            Country = Console.ReadLine();
            Console.WriteLine("Введите возраст: ");
            //проверка ввода возраста на число в нужном диапазоне 
            do
            {
                try
                {
                    Age = Convert.ToInt32(Console.ReadLine()); break;
                }
                catch (FormatException)
                {
                    Console.Write("Неверный ввод. Введите правильный возраст (число > 0): ");
                }
            } while (true);
            Console.WriteLine("Введите рост: ");
            //проверка ввода роста на число в нужном диапазоне                 
            do
            {
                stop = true;
                try
                {
                    height = Convert.ToInt32(Console.ReadLine());
                    if (height <= 0 || height > 300)
                    {
                        Console.Write("Неверный ввод. Введите правильный рост: ");
                        stop = false;
                    }
                    else
                    {
                        break;
                    }
                }
                catch (FormatException)
                {
                    Console.Write("Неверный ввод. Введите правильный рост: ");
                    stop = false;
                }
            } while (!stop);
            Console.WriteLine("Введите вес: ");
            //проверка ввода веса на число в нужном диапазоне 
            do
            {
                stop = true;
                try
                {
                    weight = Convert.ToDouble(Console.ReadLine());
                    if (weight <= 0 || weight > 900)
                    {
                        Console.Write("Неверный ввод. Введите правильный вес: ");
                        stop = false;
                    }
                    else
                    {
                        break;
                    }
                }
                catch (FormatException)
                {
                    Console.Write("Неверный ввод. Введите правильный вес: ");
                    stop = false;
                }
            } while (!stop);
            Count++;
        }

        //ИНДЕКСАТОР
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
    }
}

