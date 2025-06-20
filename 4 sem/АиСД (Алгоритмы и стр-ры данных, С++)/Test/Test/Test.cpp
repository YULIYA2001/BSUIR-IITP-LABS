//// 1. Добавление
//// Дан неориентированный граф.Определить минимальное количество ребер, после добавления которых граф
//// станет связным.Вывести - 1 если ответа не существует.
//#include <vector>
//#include <iostream>
//#include <algorithm>
//
//using namespace std;
//
//void dfs(int v, vector<vector<int>>& g, vector<bool>& used);
//
//int main(int argc, char* argv[])
//{
//	int N, M, U, V, i;
//
//	cin >> N >> M;
//
//	vector<bool> used(N);
//	vector<vector<int>> sm_list(N);
//
//	for (i = 0; i < M; i++)
//	{
//		cin >> U >> V;
//		sm_list[--U].push_back(--V);
//		sm_list[V].push_back(U);
//	}
//
//	int count = 0;
//	for (i = 0; i < N; i++)
//	{
//		if (used[i] == true)
//			continue;
//		dfs(i, sm_list, used);
//		count++;
//	}
//
//	cout << count - 1;
//}
//
//void dfs(int v, vector<vector<int>>& g, vector<bool>& used)
//{
//	used[v] = true;
//	for (vector<int>::iterator i = g[v].begin(); i != g[v].end(); ++i)
//		if (!used[*i])
//			dfs(*i, g, used);
//}

//// 2. Простая задача
//// Дана последовательность целых чисел.Найти максимальное число, которое может быть получено путем
////перемножения двух любых чисел последовательности.
//#include <iostream>
//using namespace std;
//
//int main()
//{
//    int N;
//
//    cin >> N;
//
//    long long max = 0, MAX = 0, nmax = 0, nMAX = 0, temp;
//    if (N == 2)
//    {
//        cin >> MAX;
//        cin >> max;
//        cout << max * MAX;
//    }
//    else
//    {
//        for (int i = 0; i < N; i++)
//        {
//            cin >> temp;
//            if (temp >= 0)
//            {
//                if (temp >= MAX)
//                {
//                    max = MAX;
//                    MAX = temp;
//                }
//                else if (temp > max)
//                {
//                    max = temp;
//                }
//            }
//            else
//            {
//                if (temp <= nMAX)
//                {
//                    nmax = nMAX;
//                    nMAX = temp;
//                }
//                else if (temp < nmax)
//                {
//                    nmax = temp;
//                }
//            }
//        }
//        if (max * MAX > nmax * nMAX)
//            cout << max * MAX;
//        else
//            cout << nmax * nMAX;  
//    }
//}

//3. Максимальное k-произведение
//// Дана последовательность N целых чисел(1 ≤ N ≤ 105, | Ai | ≤ 2 ⋅ 109) и число K(1 ≤ K ≤ N).Найти 
////K чисел последовательности, произведение которых максимально.
//#include <vector>
//#include <iostream>
//#include <algorithm>
//
//using namespace std;
//
//int main(int argc, char* argv[])
//{
//    long long N, K, i, M = 1e9 + 7;
//    long long max = 1;
//    bool positive = false;
//
//    cin >> N >> K;
//
//    vector<long long> A(N);
//
//    for (i = 0; i < N; i++)
//    {
//        cin >> A[i];
//        if (A[i] >= 0)
//            positive = true;
//    }
//
//    sort(A.begin(), A.end());
//
//    if (positive == false)
//    {
//        if (K % 2 == 0)
//        {
//            for (i = 0; i < K; i++)
//            {
//                max *= A[i];
//                max %= M;
//            }
//        }
//        else
//        {
//            for (i = N - 1; i > N - 1 - K; i--)
//            {
//                max *= A[i];
//                max %= M;
//            }
//        }
//    }
//    else
//    {
//        if (K % 2 == 1)
//        {
//            max *= A[N - 1];
//            max %= M;
//            A.erase(A.begin() + N - 1);
//            N--;
//            K--;
//        }
//
//        vector<long long> newA(N / 2);
//        if (N % 2 == 0)
//        {
//            for (i = 0; i < N; i = i + 2)
//            {
//                newA[i / 2] = (A[i] * A[i + 1]);
//            }
//        }
//        else
//        {
//            i = 0;
//            while (i < N)
//            {
//                if (A[i++] < 0)
//                    continue;
//                else
//                    break;
//            }
//
//            if ((i - 1) % 2 == 0)
//            {
//                A.erase(A.begin() + i - 1);
//                N--;
//            }
//            else
//            {
//                A.erase(A.begin() + i - 2);
//                N--;
//            }
//
//            for (i = 0; i < N; i = i + 2)
//            {
//                newA[i / 2] = (A[i] * A[i + 1]);
//            }
//        }
//
//        sort(newA.begin(), newA.end());
//
//        for (i = N / 2 - 1; i >= N / 2 - K/2; i--)
//        {
//            max %= M;
//            newA[i] %= M;
//            max *= newA[i] % M;
//        }
//        max %= M;
//    }
//    if (max < 0)
//        max += M;
//    cout << max;
//}

//4. Путешествие с конём
//// Размеры прямоугольной размеченной квадратами доски n × m.В нижнем левом квадрате доски(1, 1) 
//// находится шахматный конь.Конь может ходить только согласно шахматным правилам – движение может быть
//// двумя квадратами горизонтально и затем одним вертикально, или двумя квадратами вертикально и одним
//// горизонтально.Например, если n = 4 и m = 3, и конь находится в квадрате(2, 1), то следующим может
//// быть ход(1, 3) или(3, 3) или(4, 2).Для заданных положительных целых значений n, m, i и j требуется
//// определить минимальное необходимое количество ходов коня для перемещения из начальной позиции(1, 1)
//// в квадрат(i, j).
//#include <iostream>
//#include <vector>
//#include <queue>
//#include <utility>
//
//using namespace std;
//
//int main(int argc, char* argv[])
//{
//    int n, m, i, j, find = 0;
//
//    cin >> n >> m >> i >> j;
//
//    if (i == 1 && j == 1)
//        cout << 0;
//    else
//    {
//        vector<int> X = { 1, 1, 2, 2, -1, -1, -2, -2 };
//        vector<int> Y = { 2, -2, 1, -1, 2, -2, 1, -1 };
//        vector<vector<int>> arr(n, vector<int>(m));
//
//        queue<pair<int, int>> q;
//        pair<int, int> prev(1, 1);
//        pair<int, int> point;
//
//        q.push(prev);
//
//        while (!q.empty())
//        {
//            prev = q.front();
//            for (int k = 0; k < X.size(); k++)
//            {
//                point = make_pair(prev.first + X[k], prev.second + Y[k]);
//                // в нужной ли точке
//                if (point.first == i && point.second == j)
//                {
//                    find = arr[prev.first - 1][prev.second - 1] + 1;
//                    cout << find;
//                    return 0;
//                }
//                // не вышли за пределы поля и еще не были в этой точке
//                if (point.first >= 1 && point.first <= n && point.second >= 1 && point.second <= m && arr[point.first - 1][point.second - 1] == 0)
//                {
//                    if (point.first == 1 && point.second == 1);
//                    else
//                    {
//                        arr[point.first - 1][point.second - 1] = arr[prev.first - 1][prev.second - 1] + 1;
//                        q.push(point);
//                    }
//                }
//            }
//            q.pop();
//        }
//        cout << "NEVAR";
//    }
//    return 0;
//}

//// 5. Кратчайший путь
//// Задан связный неориентированный взвешенный граф G.В графе возможно наличие нескольких ребер между
//// одной и той же парой вершин.Найдите вес кратчайшего пути между двумя заданными вершинами A и B.
//#include <iostream>
//#include <queue>
//#include <vector>
//
//using namespace std;
//
//const long long Inf = 9223372036854775807;
//
//int main()
//{
//    int N, M, A, B, C;
//
//    cin >> N;
//
//    vector<vector<pair<int, int>>> matrix(N);
//
//    cin >> M;
//
//    for (int i = 0; i < M; i++)
//    {
//        cin >> A >> B >> C;
//
//        matrix[--A].push_back(make_pair(--B, C));
//        matrix[B].push_back(make_pair(A, C));
//    }
//
//    cin >> A >> B;
//    A--;
//    B--;
//
//    vector <long long> dist(N, Inf);
//    dist[A] = 0;
//
//    priority_queue <pair <int, int >> q;
//    q.push(make_pair(0, A));
//
//    while (!q.empty())
//    {
//        int len = -q.top().first;
//        int v = q.top().second;
//        q.pop();
//        if (len > dist[v])
//            continue;
//        for (int i = 0; i < matrix[v].size(); ++i)
//        {
//            int to = matrix[v][i].first;
//            int len = matrix[v][i].second;
//            if (dist[to] > dist[v] + len)
//            {
//                dist[to] = dist[v] + len;
//                q.push(make_pair(-dist[to], to));
//            }
//        }
//    }
//    cout << dist[B];
//    return 0;
//}

//// 7. Шахматная игра
//// Дано поле N × M.На нем расположены две ладьи, координаты каждой(X1, Y1) и(X2, Y2) соответственно.
//// Ладья ходит по классическим правилам шахмат : за один ход может переместиться в любую клетку,
//// расположенную на одной вертикали либо горизонтали.Одна ладья может сбить другую, если та находится
//// с ней на одной горизонтали либо вертикали.Основное отличие от классических правил : ладья не может
//// переместиться в клетку, если во время передвижения к ней она станет на клетку, которая находится под
//// боем другой ладьи.У первого игрока в распоряжении первая ладья, а у второго —вторая.Игроки ходят по
//// очереди, ход пропускать нельзя.Первым ходит первый игрок.Проигрывает тот, кому некуда ходить(куда бы
//// ни пошел — собьют).Определите кто победит при оптимальной игре обоих.
//#include <iostream>
//#include <cmath>
//using namespace std;
//
//int main()
//{
//    int N, M, X1, Y1, X2, Y2;
//
//    cin >> N >> M >> X1 >> Y1 >> X2 >> Y2;
//    if (abs(X1 - X2) == abs(Y1 - Y2))
//        cout << "NO";
//    else
//        cout << "YES";
//}

////8. Максимальный неподпалиндром
////В заданной строке S найти максимальную по длине подстроку, которая не является палиндромом.
//#include <iostream>
//
//using namespace std;
//
//int main(int argc, char* argv[])
//{
//	string s;
//	cin >> s;
//
//	int len = s.size();
//	int res = 0, count = 1;
//	for (int i = 0; i < len - 1; i++)
//	{
//		if (s[i] == s[i + 1])
//			count++;
//		else
//			break;
//	}
//	if (count == len)
//	{
//		cout << -1;
//		return 0;
//	}
//
//	for (int i = 0; i < len / 2; i++)
//	{
//		if (s[i] != s[len - 1 - i])
//		{
//			res = len;
//			break;
//		}
//	}
//	if (res == 0)
//	{
//		res = len - 1;
//	}
//	cout << res;
//	return 0;
//}

//// 9. Инвертирование
//// Дана строка S и Q запросов.Запрос представляет собой пару чисел L и R — промежуток строки S, на
//// котором нужно инвертировать регистр символов.Требутеся найти строку S после выполнения всех запросов.
//#include <iostream>
//#include <vector>
//using namespace std;
//
//int main()
//{
//    string S;
//    int Q, L, R;
//
//    cin >> S;
//    cin >> Q;
//
//    vector<int> s(S.size() + 1);
//
//    for (int i = 0; i < Q; i++)
//    {
//        cin >> L >> R;
//        if (R < L)
//        {
//            swap(L, R);
//        }
//        s[L - 1] += 1;
//        s[R] += -1;
//    }
//    for (int i = 0; i < S.size(); i++)
//    {
//        if (s[i] % 2 == 1)
//            isupper(S[i]) ? S[i] = tolower(S[i]) : S[i] = toupper(S[i]);
//        s[i + 1] += s[i];
//    }
//    cout << S;
//}

//// 12. Большой куш
//// Известный фокусник Донни разбогател на очень простой игре.Он играл в нее на деньги с самыми богатыми
//// и знаменитыми личностями, но никто ни разу не смог его обхитрить.И тут очередь дошла до вас.Вы
//// белорусский бизнесмен и хотите удвоить свое состояние.Обыграйте Донни и сорвите куш!Так же вы можете
//// отказаться от игры, если, при виде начальной позиции, на вас нападет плохое предчувствие.Правила игры
//// следующие : Изначально дано число X.За один ход разрешается отнять от числа X любую цифру, кроме 0,
//// которая входит в число X.Проигрывает тот, кто не может ходить, то есть когда будет получено число 0.
//#include <iostream>
//using namespace std;
//
//int main()
//{
//    long long X;
//
//    cin >> X;
//    if (X % 10 == 0)
//        cout << "NO";
//    else
//        cout << X % 10;
//}

////13. Удаление
//// Дан неориентированный граф.Определить минимальное количество ребер, после удаления которых между
//// каждой парой вершин будет существовать только один маршрут(без повторений в нем ребер).Вывести - 1,
//// если ответа не существует.
//#include <vector>
//#include <iostream>
//
//using namespace std;
//
//void dfs(int v, vector<vector<int>>& g, vector<bool>& used);
//
//int main(int argc, char* argv[])
//{
//	int N, M, U, V, i, result;
//
//	cin >> N >> M;
//
//	vector<bool> used(N);
//	vector<vector<int>> sm_list(N);
//
//	for (i = 0; i < M; i++)
//	{
//		cin >> U >> V;
//		sm_list[--U].push_back(--V);
//		sm_list[V].push_back(U);
//	}
//
//	dfs(0, sm_list, used);
//	for (i = 0; i < N; i++)
//	{
//		if (used[i] != true)
//		{
//			cout << -1;
//			return 0;
//		}
//	}
//	cout << M - (N - 1);
//}
//
//void dfs(int v, vector<vector<int>>& g, vector<bool>& used)
//{
//	used[v] = true;
//	for (vector<int>::iterator i = g[v].begin(); i != g[v].end(); ++i)
//		if (!used[*i])
//			dfs(*i, g, used);
//}

//// 15. Выравнивание
//// Дана последовательность Ai, состоящая из N целых чисел.За одно действие можно зафиксировать
//// произвольный промежуток одинаковых элементов последовательности и увеличить все элементы этого
//// промежутка на 1. Необходимо за минимальное количество действий уравнять все элементы.
//#include <iostream>
//using namespace std;
//
//int main()
//{
//    long long int N, max, Ai, prevAi, steps = 0;
//
//    cin >> N >> prevAi;
//    max = prevAi;
//    for (int i = 1; i < N; i++)
//    {
//        cin >> Ai;
//        if (Ai > prevAi && Ai > max)
//        {
//            steps += Ai - max;
//            max = Ai;
//        }
//        else if (Ai < prevAi)
//            steps += prevAi - Ai;
//        prevAi = Ai;
//    }
//    cout << steps;
//}

////16. Следующее
//// Дано число X.Надо найти наименьшее число большее, чем X, которое может быть получено из X
//// перестановкой цифр.
//#include <iostream>
//#include <vector>
//#include <algorithm>
//#include <cstring>
//
//using namespace std;
//
//int main(int argc, char* argv[])
//{
//	string X;
//	cin >> X;
//
//	string x;
//	int n = stoi(X);
//	x = to_string(n);
//
//	vector<int> greater;
//
//	while (next_permutation(X.begin(), X.end()))
//	{
//		if (X > x)
//		{
//			greater.push_back(stoi(X));
//		}
//	}
//	if (greater.size() == 0)
//		cout << -1;
//	else
//	{
//		int min = greater[0];
//		for (int i = 1; i < greater.size(); i++)
//		{
//			if (greater[i] < min)
//				min = greater[i];
//		}
//		cout << min;
//	}
//}

//// 17. 1087388483
//// Дана последовательность из N целых положительных чисел.Требуется определить можно ли путем
//// перемножения некоторых чисел последовательности получить число 1087388483.
//#include <iostream>
//using namespace std;
//
//int main()
//{
//    int N, a = 0, b = 0, c = 0;
//    int good[3] = {1021, 1031, 1033};
//    long long num;
//
//    cin >> N;
//
//    for (int i = 0; i < N; i++)
//    {
//        cin >> num;
//        if (num == good[0])
//            a = 1;
//        else if (num == good[1])
//            b = 1;
//        else if (num == good[2])
//            c = 1;
//        else if (num == good[0] * good[1])
//            a = b = 1;
//        else if (num == good[0] * good[2])
//            a = c = 1;
//        else if (num == good[1] * good[2])
//            b = c = 1;
//        else if (num == good[0] * good[1] * good[2])
//            a = b = c = 1;
//    }
//
//    if(a == 1 && b == 1 && c == 1)
//        cout << "YES";
//    else
//        cout << "NO";   
//}


//// 18. Високосный
//// Високосный год — год в юлианском и григорианском календарях, продолжительность которого равна 366
//// дням — на одни сутки больше продолжительности обычного, невисокосного года.В юлианском календаре
//// високосным годом является каждый четвёртый год, в григорианском календаре из этого правила есть
//// исключения.Год в григорианском календаре является високосным, если он кратен 4 и при этом не кратен
//// 100, либо кратен 400. Определите, является ли заданный год високосным в григорианском календаре.
//#include <iostream>
//
//int main()
//{
//    int Y;
//    std::cin >> Y;
//    if (Y >= 2000 && Y <= 9999)
//    {
//        if (Y % 400 == 0 || (Y % 100 != 0 && Y % 4 == 0))
//            std::cout << "YES";
//        else
//            std::cout << "NO";
//    }
//}

//// 19. Инверсии
//// Перестановкой чисел назовем такую последовательность А длины N, что 1 ≤ Ai ≤ N, и все числа
//// последовательности различны.Инверсией в пeрестановке A размера N называется всякая пара индексов(i, j)
//// такая, что i < j и Ai > Aj.В данной задаче необходимо найти число инверсий в заданной перестановке.
//#include <iostream>
//#include <vector>
//
//using namespace std;
//
//long long merge(vector<int>& A, int left, int medium, int right)
//{
//    long long invCount = 0;
//    vector<int> res(right - left + 1);
//    int i1 = left, i2 = medium + 1, iR = 0;
//
//    while (i1 <= medium && i2 <= right)
//    {
//        if (A[i1] < A[i2])
//            res[iR++] = A[i1++];
//        else
//        {
//            res[iR++] = A[i2++];
//            invCount += medium - i1 + 1;
//        }
//    }
//
//    while (i1 <= medium)
//        res[iR++] = A[i1++];
//
//    while (i2 <= right)
//        res[iR++] = A[i2++];
//
//    copy(res.begin(), res.end(), A.begin() + left);
//
//    return invCount;
//}
//
//long long mergeSort(vector<int> &A, int left, int right)
//{
//    long long invCount = 0;
//    
//    if (left == right)
//        return invCount;
//
//    int medium = (left + right) / 2;
//
//    invCount += mergeSort(A, left, medium);
//    invCount += mergeSort(A, medium + 1, right);
//
//    invCount += merge(A, left, medium, right);
//    
//    return invCount;
//}
//
//int main()
//{
//    int N;
//
//    cin >> N;
//
//    vector<int> A(N);
//
//    for (int i = 0; i < N; i++)
//    {
//        cin >> A[i];
//    }
//
//    cout << mergeSort(A, 0, N-1);
//    return 0;
//}
