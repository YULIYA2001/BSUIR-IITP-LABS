using System;

namespace Lab5
{
    class Program
    {
        static void Main(string[] args)
        {
            //создание одного или массива игроков с помощью конструктора
            FootballPlayer football = new FootballPlayer(2);
            football[0] = new FootballPlayer("Стасевич", "Игорь", "Николаевич", "муж.", "Беларусь", 34,
                178, 77, "\"БАТЭ\"(Беларусь)", 'F', 3, 22);
            football[1] = new FootballPlayer("Denish", "Duarte", "male", "Portugal", 26,
                190, 84, "\"Динамо-Брест\"(Беларусь)", 'F', 2, 3);
            FootballPlayer football1 = new FootballPlayer("Нехайчик", "Павел", "Александрович", "муж.", "Беларусь",
                31, 180, 70, "\"БАТЭ\"(Беларусь)", 'F', 3, 33);

            BasketballPlayer basketball = new BasketballPlayer("Веремееенко", "Анастасия", "Владимировна",
                "жен.", "Эстония", 32, 193, 82, "\"Надежда\"(Россия)", 'B', 1, 11);

            VolleyballPlayer volleyball = new VolleyballPlayer(2);
            volleyball[0] = new VolleyballPlayer("Эрвин", "Нгапет", "муж.", "France", 29, 194, 93,
                "\"Зенит\"(Казань)", 'V', 2, 9);
            volleyball[1] = new VolleyballPlayer(" Бирюкова", "Ольга", " Николаевна", "жен.", "Россия", 25,
                194, 74, "\"Динамо-Казань\"", 'V', 2, 10);

            //вывод количества людей
            Sportsman.DisplayCount();
            FootballPlayer.DisplayCount();
            BasketballPlayer.DisplayCount();
            VolleyballPlayer.DisplayCount();
            Console.WriteLine("\n");

            //вывод полных сведений о игроках
            int x = 1;
            for (int i = 0; i < 2; i++)
            {
                Console.WriteLine("Игрок {0}:", x++);
                football[i].DisplayPerson();
            }
            Console.WriteLine("Игрок {0}:", x++);
            football1.DisplayPerson();

            Console.WriteLine("Игрок {0}:", x++);
            basketball.DisplayPerson();

            for (int i = 0; i < 2; i++)
            {
                Console.WriteLine("Игрок {0}:", x++);
                volleyball[i].DisplayPerson();
            }

            //возможность для всех спортсменов
            Console.WriteLine("...................Изменение статуса здоровья........................");
            football[0].ChangeHealthStatus();
            Console.WriteLine("......................Смена названия команды........................");
            volleyball[0].NewTeam();
            Console.WriteLine(".....................Получить награду (1 за раз).......................");
            basketball.GiveAward();
            basketball.GiveAward();

            //только для футболистов
            Console.WriteLine(".......................Изменение игрового статуса.......................");
            football1.ChangeStatus();

            //добавление игрока с клавиатуры (возможно для любого)
            Console.WriteLine("\n\n..Ввод информации о баскетболисте вручную (с проверкой на неверный ввод)..\n");
            BasketballPlayer basketball1 = new BasketballPlayer();
            basketball1.Add();
            basketball1.DisplayPerson();

        }
    }
}
