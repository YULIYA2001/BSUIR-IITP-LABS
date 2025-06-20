using System;
using System.Collections.Generic;

namespace Lab8
{
    interface ISportsman : IComparable<Sportsman>, IComparer<Sportsman>
    {
        void IsReadyToPlay();
    }

    interface IFootballPlayer
    {
        public void ChangeStatus(Display d);
    }

    interface IPerson
    {
        void DisplayPerson();
    }
}