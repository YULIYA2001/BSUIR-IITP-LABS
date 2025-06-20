using System;
//using System.Collections.Generic;
//using System.Text;

namespace Lab3
{
    class Person
    {
        private string name;
        private string patronymic;
        private string gender;
        private int age;
        private int height;
        private double weight;
        Person[] people;          //для создания сразу массива людей 

        //КОНСТРУКТОРЫ
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
            get; set; }
        public string Country { get; set; } = "Беларусь";
        public int Height
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
                if (value > 0)
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
            Console.WriteLine("Всего людей: {0}\n", Count);
        }
        public void DisplayPerson()
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
                Console.Write($"\nрост: {height} ");
            }
            if (weight != 0)
            {
                Console.Write($"\nвес: {weight} ");
            }
            Console.WriteLine("\n");
        }
        // имя фамилия страна пол возраст
        private void DisplayPerson1()
        {
            Console.Write($"{name} {Surname} \nстрана: {Country} \nпол: {gender} \nвозраст: {age} ");
        }
        //фамилия имя отчество страна пол возраст
        private void DisplayPerson2()
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
