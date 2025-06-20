using System;
using System.Collections.Generic;
using System.Text;

namespace Lab6
{
    interface ISportsman : IComparable<Sportsman>, IComparer<Sportsman>
    {
        void IsReadyToPlay();
    }

    interface IFootballPlayer
    {
        public void ChangeStatus();
    }
    interface IPerson
    {
        void DisplayPerson();
    }
}
