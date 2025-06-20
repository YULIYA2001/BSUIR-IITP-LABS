using System;
using System.Diagnostics.CodeAnalysis;
using System.Text.RegularExpressions;

namespace Lab7
{
    class RationalNumber : IEquatable<RationalNumber>, IComparable<RationalNumber>
    {
        private long n;
        private long m;

        //КОНСТРУКТОРЫ
        public RationalNumber(long n, long m)
        {
            this.n = n;
            this.m = (m > 0) ? m : 1;
            ReducedFraction();
        }

        public RationalNumber(long n) : this(n, 1){ }
       
        //МЕТОДЫ
        // НОД (Алгоритм Евклида)
        private static long GreatestCommonDivisor(long a, long b)
        {
            a = Math.Abs(a);
            while (b != 0)
            {
                long temp = b;
                b = a % b;
                a = temp;
            }
            return a;
        }

        // НОК
        private static long LeastCommonMultiple(long a, long b)
        {
            return a * b / GreatestCommonDivisor(a, b);
        }

        // Обратная дробь
        private RationalNumber Reverse()
        {
            if (n < 0)
            {
                return new RationalNumber(m * (-1), n * (-1));
            }
            return new RationalNumber(m, n);
        }

        // Противоположная дробь
        private RationalNumber ChangedSign()
        {
            return new RationalNumber((-1) * n, m);
        }

        // Сокращенная дробь
        public void ReducedFraction()
        {
            long GCD = GreatestCommonDivisor(n, m);
            n /= GCD;
            m /= GCD;
        }

        public int CompareTo(RationalNumber other)
        {
            if (n == other.n && m == other.m)
            {
                return 0;
            }
            if (n * other.m > other.n * m)
            {
                return 1;
            }
            return -1;
        }

        public bool Equals([AllowNull] RationalNumber other)
        {
            if (other == null)
            {
                return false;
            }
            return CompareTo(other) == 0;
        }

        public override bool Equals(object obj)
        {
            bool result = false;
            if (obj is RationalNumber)
            {
                result = this.Equals(obj as RationalNumber);
            }
            return result;
        }

        public override int GetHashCode()
        {
            return (int)(n * n + m * m);
        }

        public override string ToString()
        {
            if (this.n == 0)
            {
                return "0";
            }
            string result = "";
            if (n == m)
            {
                return result + "1";
            }
            if (m == 1)
            {
                return result + n;
            }
            return result + n + "/" + m;
        }

        // представление объекта класса в виде строки в различных форматах
        public string DifferentStrings(char ch)
        {
            if (ch == '.')
            {
                string str = ((double)this).ToString();
                str = str.Replace(",", ".");
                return str;
            }
            if (ch == ',')
            {
                return ((double)this).ToString();
            }
            return this.ToString();
        }

        // получение объекта класса по строковому представлению из разных форматов
        public static RationalNumber TakeFromStrings()
        {
            string pattern1 = @"^-?\d+\,\d+$";
            string pattern2 = @"^-?\d+\.\d+$";
            string pattern3 = @"^-?\d+\/\d+$";
            string pattern4 = @"^-?\d+$";
            Console.WriteLine("Введите число (вида: x/x  x.x  x,x  x)");
            bool stop;
            RationalNumber r = new RationalNumber(1);
            do
            {
                stop = true;
                string num = Console.ReadLine();
                if (Regex.IsMatch(num, pattern1))
                {
                    r = Convert.ToDouble(num);
                }
                else if (Regex.IsMatch(num, pattern2))
                {
                    num = num.Replace(".", ",");
                    r = Convert.ToDouble(num);
                }
                else if (Regex.IsMatch(num, pattern3))
                {
                    string[] subnum = num.Split(new char[] { '/' });
                    r.n = Convert.ToInt64(subnum[0]);
                    r.m = Convert.ToInt64(subnum[1]);
                }
                else if (Regex.IsMatch(num, pattern4))
                {
                    r = Convert.ToInt32(num);
                }
                else
                {
                    Console.Write("Неверный ввод. Попробуйте снова: ");
                    stop = false;
                }
            } while (!stop);
            return r;
        }

        // неявные операторы преобразования из целых и действительных чисел
        public static implicit operator RationalNumber(int a) => new RationalNumber(a);
        public static implicit operator RationalNumber(long a) => new RationalNumber(a);
        
        public static implicit operator RationalNumber(double a)
        {
            long num = ConvertFrom(a);
            return new RationalNumber((long)(a * num), num);
        }

        public static implicit operator RationalNumber(decimal a)
        {
            long num = ConvertFrom(a);
            return new RationalNumber((long)(a * num), num);
        }

        // функция для преобразования из double и decimal в RationalNumber
        private static long ConvertFrom<T>(T a)
        {
            string s = a.ToString();
            int len = s.Length;
            int i = 0;
            while (i++ < len)
            {
                if (s[i] != '.')
                {
                    break;
                }
            }
            long num = 1;
            if (i != 7)
            {
                for (int x = 0; x < len - i - 1; x++)
                {
                    num *= 10;
                }
            }
            return num;
        }

        // явные операторы преобразования к целым и действительным числам
        public static explicit operator int(RationalNumber r) => (int)(r.n / r.m);
        public static explicit operator long(RationalNumber r) => r.n / r.m;
        public static explicit operator double(RationalNumber r) => (r.n / (double)r.m);
        public static explicit operator decimal(RationalNumber r) => (r.n / (decimal)r.m);

        // "+" (для двух дробей, для дроби и числа, для числа и дроби)
        public static RationalNumber operator +(RationalNumber a, RationalNumber b)
        {
            long LCM = LeastCommonMultiple(a.m, b.m);            
            return new RationalNumber(( LCM / a.m * a.n + LCM / b.m * b.n ), LCM);
        }
        public static RationalNumber operator +(RationalNumber a, long b) => a + new RationalNumber(b);
        public static RationalNumber operator +(long a, RationalNumber b) => b + a;

        // "-" (для двух дробей, для дроби и числа, для числа и дроби) 
        public static RationalNumber operator -(RationalNumber a, RationalNumber b)
        {
            long LCM = LeastCommonMultiple(a.m, b.m);
            return new RationalNumber(((LCM / a.m * a.n) - (LCM / b.m * b.n)), LCM);
        }
        public static RationalNumber operator -(RationalNumber a, long b) => a - new RationalNumber(b);
        public static RationalNumber operator -(long a, RationalNumber b) => -(b - a);

        // "*" (для двух дробей, для дроби и числа, для числа и дроби)
        public static RationalNumber operator *(RationalNumber a, RationalNumber b)
        {
            return new RationalNumber(a.n * b.n, a.m * b.m);
        }
        public static RationalNumber operator *(RationalNumber a, long b) => a * new RationalNumber(b);
        public static RationalNumber operator *(long a, RationalNumber b) => b * a;

        //  "/" (для двух дробей, для дроби и числа, для числа и дроби)
        public static RationalNumber operator /(RationalNumber a, RationalNumber b)
        {
            if (b.n == 0)
            {
                throw new DivideByZeroException();
            }
            return a * b.Reverse();
        }
        public static RationalNumber operator /(RationalNumber a, long b) => a / new RationalNumber(b);
        public static RationalNumber operator /(long a, RationalNumber b) => new RationalNumber(a) / b;
        
        // "-" для противоположной дроби
        public static RationalNumber operator -(RationalNumber a) => a.ChangedSign();
        public static RationalNumber operator ++(RationalNumber a) => a + 1;
        public static RationalNumber operator --(RationalNumber a) => a - 1;

        //"==" (для двух дробей, для дроби и числа, для числа и дроби)
        public static bool operator ==(RationalNumber a, RationalNumber b)
        {
            if ((object)a == null)
            {
                if ((object)b == null)
                {
                    return true;
                }
                return false;
            }
            return a.Equals(b);
        }
        public static bool operator ==(RationalNumber a, long b) => a == new RationalNumber(b);
        public static bool operator ==(long a, RationalNumber b) => new RationalNumber(a) == b;

        // "!=" (для двух дробей, для дроби и числа, для числа и дроби)
        public static bool operator !=(RationalNumber a, RationalNumber b) => !(a == b);
        public static bool operator !=(RationalNumber a, long b) => a != new RationalNumber(b);
        public static bool operator !=(long a, RationalNumber b) => new RationalNumber(a) != b;

        // ">" (для двух дробей, для дроби и числа, для числа и дроби)
        public static bool operator >(RationalNumber a, RationalNumber b) => a.CompareTo(b) > 0;
        public static bool operator >(RationalNumber a, long b) => a > new RationalNumber(b);
        public static bool operator >(long a, RationalNumber b) => new RationalNumber(a) > b;

        // "<" (для двух дробей, для дроби и числа, для числа и дроби)
        public static bool operator <(RationalNumber a, RationalNumber b) => a.CompareTo(b) < 0;
        public static bool operator <(RationalNumber a, long b) => a < new RationalNumber(b);
        public static bool operator <(long a, RationalNumber b) => new RationalNumber(a) < b;

        // ">=" (для двух дробей, для дроби и числа, для числа и дроби)
        public static bool operator >=(RationalNumber a, RationalNumber b) => a.CompareTo(b) >= 0;
        public static bool operator >=(RationalNumber a, long b) => a >= new RationalNumber(b);
        public static bool operator >=(long a, RationalNumber b) => new RationalNumber(a) >= b;

        // "<=" (для двух дробей, для дроби и числа, для числа и дроби)
        public static bool operator <=(RationalNumber a, RationalNumber b) => a.CompareTo(b) <= 0;
        public static bool operator <=(RationalNumber a, long b) => a <= new RationalNumber(b);
        public static bool operator <=(long a, RationalNumber b) => new RationalNumber(a) <= b;
    }
}
