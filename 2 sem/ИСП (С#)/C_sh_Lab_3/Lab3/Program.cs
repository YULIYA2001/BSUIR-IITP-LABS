using System;

namespace Lab3
{
    class Program
    {
        static void Main(string[] args)
        {
            Person people = new Person(4);
            people[0] = new Person("Tom", "Smith", "male", "America", 30);                   //5 параметров
            people[1] = new Person("Кот", "Анна", "Андреевна", "жен.", "Беларусь", 20);      //6 параметров
            people[2] = new Person("Liza", "Jones", "female", "UK", 10, 125, 40.5);          //7 параметров
            people[3] = new Person("Петров", "Петр", "Иванович", "муж.", "РФ", 48, 180, 80); //8 параметров
            //вывод количества людей
            Person.DisplayCount();       
            for(int i = 0; i < Person.Count; i++)
            {
                people[i].DisplayPerson();
            }
            //добавление или изменение параметров
            people[0].Height = 175;
            people[1].Surname = "Петрова";
            people[2].Weight = -42;
            people[3].Age = 50;
            people[3].Country = "Беларусь";
            for (int i = 0; i < Person.Count; i++)
            {
                people[i].DisplayPerson();
            }
            //проверка на белоруса(ку)
            people[0].IsBelarussian();
            people[1].IsBelarussian(out bool check);
            Console.WriteLine("\n{0} белорус(ка)? {1}", people[1].Surname, check);
            
        }
    }
}
