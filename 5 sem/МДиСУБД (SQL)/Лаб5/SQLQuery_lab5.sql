USE Northwind
GO

-- 1.1.	Построить запрос, формирующий вывод всех данных обо всех регионах (Region).
SELECT *
FROM Region
GO


-- 1.2. Построить запрос, формирующий вывод названия, адреса, города первых 5 поставщиков, 
-- отсортированные в алфавитном порядке по названию.
SELECT TOP 5 ContactName, Address, City
FROM Suppliers
ORDER BY ContactName
GO


-- 1.3. Вывести все данные о сотруднике Robert King
SELECT *
FROM Employees
WHERE FirstName = 'Robert' AND LastName = 'King'
GO


-- 1.4. Вывести цены всех товаров, продажа которых прекращена (discontinued).
SELECT UnitPrice
FROM Products
WHERE Discontinued = 1
GO


-- 1.5. Сформировать список (содержащий наименование, отпускную цену, остаток) товаров на складе,
-- остатки которых более 100 единиц.
SELECT ProductName, UnitPrice, UnitsInStock
FROM Products
WHERE UnitsInStock > 100
GO


-- 1.6. Вывести список всех сотрудников с днями рождения в октябре
SELECT *
FROM Employees
WHERE MONTH(BirthDate) = 10
GO


-- 1.7. Определить, кто из сотрудников имеет степень Ph.D. (образование указано в столбце Notes)
SELECT *
FROM Employees
WHERE CHARINDEX('Ph.D.', Notes) > 0
GO


-- 1.8. Построить запрос, формирующий табличный вывод: фамилию сотрудника и указание старше он/она
-- 60 лет или нет
SELECT LastName,
		IIF(DATEDIFF(YEAR, BirthDate, GETDATE()) > 60, 'Старше 60 лет', 'Младше 60 лет') as Age
FROM Employees
GO


-- 2.1. Сформировать список (содержащий наименование, цену, остаток) товаров категории Beverages на
-- складе, остатки которых более 100 единиц.
SELECT ProductName, UnitPrice, UnitsInStock
FROM Products
WHERE CategoryID = (
			SELECT CategoryID 
			FROM Categories 
			WHERE CategoryName='Beverages'
	  ) 
	  AND UnitsInStock > 100
GO


-- 2.2. Вывести общую стоимость всех заказов, которые оформил сотрудник фирмы “Steven Buchanan"  в июле
-- 1996 г., с указанием кода заказа, даты заказа и общей суммы.
WITH StevenBuchananJuly1996Orders AS		-- производная таблица
(
	SELECT O.OrderID, O.OrderDate, OS.Subtotal AS TotalSum
	FROM Orders AS O, [Order Subtotals] AS OS
	WHERE O.EmployeeID = (
			 SELECT EmployeeID 
			 FROM Employees 
			 WHERE FirstName = 'Steven' AND LastName = 'Buchanan'
		  )
		  AND MONTH(O.OrderDate) = 7
		  AND YEAR(O.OrderDate) = 1996
		  AND OS.OrderID = O.OrderID
)

-- запишется подытог NULL, NULL, SUM в таблицу StevenBuchananJuly1996Orders
SELECT *
FROM StevenBuchananJuly1996Orders
UNION ALL
	SELECT NULL, NULL, SUM(TotalSum)
	FROM StevenBuchananJuly1996Orders
GO


-- 2.3 Вывести номера и даты заказов с товарами категории “Seafood”.
SELECT O.OrderID, O.OrderDate
FROM Orders as O
JOIN [Order Details]AS OD ON OD.OrderID = O.OrderID
JOIN Products AS P ON P.ProductID = OD.ProductID
WHERE CategoryID = (
		SELECT CategoryID
		FROM Categories 
		WHERE CategoryName = 'Seafood'
		)
GROUP BY O.OrderID, O.OrderDate
GO


-- 2.4. Вывести все товары, отправленные в 1997 году в Канаду (неповторяющиеся значения).
SELECT DISTINCT P.*
FROM Products AS P
JOIN [Order Details] AS OD ON P.ProductID = OD.ProductID
JOIN Orders AS O ON O.OrderID = OD.OrderID
WHERE YEAR(O.ShippedDate) = 1997 AND O.ShipCountry = 'Canada'
GO

-- 2.5 Вывести все товары, отправленные в 1997 году в Канаду (неповторяющиеся значения)
-- посредством Speedy Express.
SELECT DISTINCT P.*
FROM Products AS P
JOIN [Order Details] AS OD ON P.ProductID = OD.ProductID
JOIN Orders AS O ON O.OrderID = OD.OrderID
WHERE YEAR(O.ShippedDate) = 1997
	AND O.ShipCountry = 'Canada' 
	AND O.ShipVia = (
			SELECT ShipperID
			FROM Shippers
			WHERE CompanyName = 'Speedy Express'
			)
GO


-- 3.1	Определить количество заказов в базе данных.
SELECT COUNT(*) AS OrdersCount
FROM Orders
GO


-- 3.2 Выполнить расчет позиций и общую стоимость товаров, входящих в заказы, отправленные 21
-- октября 1997 года.
WITH October21_1997Orders AS		-- производная таблица
(
	SELECT OD.OrderID, COUNT(P.ProductID) AS PositionCount, OS.Subtotal AS TotalSum
	FROM [Order Details] AS OD
		JOIN Products AS P ON OD.ProductID = P.ProductID
		JOIN [Order Subtotals] AS OS ON OS.OrderID = OD.OrderID 
		JOIN Orders AS O ON O.OrderID = OS.OrderID 
	WHERE CONVERT(VARCHAR, O.OrderDate, 103) = '21/10/1997'
	GROUP BY OD.OrderID, OS.Subtotal
	--ORDER BY OD.OrderID
)
-- запишется подытог NULL, SUM, SUM в роизводную таблицу October21_1997Orders
SELECT *
FROM October21_1997Orders
UNION ALL
	SELECT NULL, SUM(PositionCount), SUM(TotalSum)
	FROM October21_1997Orders
GO


-- 3.3 Выполнить расчет количества поставленного на склад товара с кодом 4 менеджером поставщика
-- с кодом 3.
SELECT COUNT(UnitsInStock) AS PrCount
FROM Products
WHERE ProductID = 4 AND SupplierID = 3
GO


-- 3.4. Выполнить расчет общей стоимости поставленной продукции в феврале 1998 года 
SELECT SUM(OS.Subtotal) AS TotalSum
FROM [Order Subtotals] AS OS
JOIN Orders AS O ON OS.OrderID = O.OrderID
WHERE MONTH(O.ShippedDate) = 2 AND YEAR(O.ShippedDate) = 1998
GO


-- 3.5. Получить количество типов товаров, продажи которых не прекращены
SELECT COUNT(DISTINCT CategoryID)
FROM Products 
WHERE Discontinued = 0
GO


-- 3.6. Выполнить расчет количества заказов, которые обслуживали сотрудники фирмы в 1997-1998 гг.
-- с указанием года, сотрудника и количества заказов
SELECT YEAR(OrderDate) AS Year, EmployeeID, COUNT(OrderID) AS OrdersCount
FROM Orders
WHERE YEAR(OrderDate) IN (1997, 1998)
GROUP BY YEAR(OrderDate), EmployeeID 
ORDER BY YEAR(OrderDate), EmployeeID 
GO


-- !НЕПОНЯТНОЕ УСЛОВИЕ 
-- 3.7. Вывести наименования категорий товаров на складе, остатки по которым [категориям] меньше 100, с указанием
-- категории и суммы остатка
WITH CategoriesStocks AS		-- производная таблица
(
	SELECT C.CategoryName, SUM(P.UnitsInStock) AS UnitsInStock
	FROM Products AS P, Categories AS C
	WHERE C.CategoryID = P.CategoryID
	GROUP BY C.CategoryName
)
SELECT *
FROM CategoriesStocks
WHERE UnitsInStock < 100

-- 3.7. Вывести наименования категорий, товаров на складе, остатки по которым [товарам] меньше 100, с указанием
-- категории и суммы остатка
SELECT C.CategoryName, P.ProductName, P.UnitsInStock
FROM Products AS P, Categories AS C
WHERE P.UnitsInStock < 100 AND C.CategoryID = P.CategoryID
GROUP BY C.CategoryName, P.ProductName, P.UnitsInStock
GO


-- 3.9. Вывести список сотрудников, общая сумма заказов которых составила в 1996 г. 5000 и более
-- денежных единиц
WITH EmplIDTotalSum AS		-- производная таблица
(
	SELECT SUM(OS.Subtotal) AS TotalSum, O.EmployeeID
	FROM [Order Subtotals] AS OS, Orders AS O
	WHERE OS.OrderID = O.OrderID AND YEAR(O.OrderDate) = 1996
	GROUP BY O.EmployeeID
)

SELECT ET.TotalSum, E.*
FROM Employees AS E
JOIN EmplIDTotalSum AS ET ON ET.EmployeeID = E.EmployeeID
WHERE TotalSum >= 5000
GO


-- 3.10. Вывести стоимость заказов, отправленных в 1997 году, в разрезе стран.
SELECT O.OrderID, O.ShipCountry, SUM(OS.Subtotal) AS TotalSum
FROM Orders AS O, [Order Subtotals] AS OS
WHERE OS.OrderID = O.OrderID AND YEAR(O.OrderDate) = 1997
GROUP BY O.OrderID, O.ShipCountry
ORDER BY O.ShipCountry
GO


-- 3.11. Вывести стоимость заказов, отправленных в 1997 году, в разрезе стран, 
-- страны указаны в колонках итоговой таблицы.
SELECT O.ShipCountry, SUM(OS.Subtotal) AS TotalSum
FROM Orders AS O, [Order Subtotals] AS OS
WHERE OS.OrderID = O.OrderID AND YEAR(O.OrderDate) = 1997
GROUP BY O.ShipCountry
ORDER BY O.ShipCountry
GO


-- 3.12. Вывести стоимость сделанных заказов помесячно с подведением промежуточных ежегодных итогов
-- и общий итог.
WITH MonthYearSum AS		-- производная таблица
(
	SELECT MONTH(O.OrderDate) AS OrderMonth, YEAR(O.OrderDate) AS OrderYear, SUM(OS.Subtotal) AS TotalSum
	FROM Orders AS O, [Order Subtotals] AS OS
	WHERE OS.OrderID = O.OrderID
	GROUP BY O.OrderDate
)

SELECT OrderMonth, OrderYear, SUM(TotalSum) AS TotalOrderSumm
FROM MonthYearSum
GROUP BY ROLLUP(OrderYear, OrderMonth)
GO


-- 3.13. Вывести стоимость всех заказов заказчика HILARION-Abastos в 1997 году помесячно. 
WITH Temp AS (
	SELECT O.CustomerID, MONTH(O.OrderDate) AS OrderMonth, OS.Subtotal
	FROM Orders AS O
	JOIN [Order Subtotals] AS OS ON O.OrderID = OS.OrderID
	WHERE YEAR(O.OrderDate) = 1997
)

SELECT OrderMonth, SUM(Subtotal) AS TotalSum
FROM Temp
-- странное имя не работает
WHERE CustomerID = (SELECT CustomerID FROM Customers WHERE CustomerID = 'HILAA')--CompanyName = 'HILARIÓN-Abastos')
GROUP BY OrderMonth
GO


-- 4.1. Вывести наименование товаров, остатки на складе которых от 5 до 10 и от 25 и более
SELECT ProductName
FROM Products
WHERE (UnitsInStock BETWEEN 5 AND 10) OR (UnitsInStock >= 25)
GO


-- 4.2. Вывести заказы, в которые включены более 2-х товаров
WITH Temp AS
(
	SELECT OrderID, COUNT(ProductID) AS ProductsCount
	FROM [Order Details]
	GROUP BY OrderID
)

SELECT T.ProductsCount, O.*
FROM Temp AS T
JOIN Orders AS O ON T.OrderID = O.OrderID
WHERE ProductsCount > 2
GO


-- 4.3. Определить города, в которые направлены более 3 заказов	
SELECT ShipCity, COUNT(*) AS OrderCount
FROM Orders
GROUP BY ShipCity
HAVING COUNT(*) > 3
GO


-- 5.1. Построить запрос для определения изменения средней стоимости заказа в ноябре 1997 г
-- по сравнению с ноябрём 1996 г.
SELECT
	(
		SELECT AVG(OS.Subtotal) AS AvgPrice
		FROM Orders AS O
		JOIN [Order Subtotals] AS OS ON OS.OrderID = O.OrderID 
		WHERE MONTH(O.OrderDate) = 11 AND YEAR(O.OrderDate) = 1997
	) 
	-
	(
		SELECT AVG(OS.Subtotal) AS AvgPrice
		FROM Orders AS O
		JOIN [Order Subtotals] AS OS ON OS.OrderID = O.OrderID 
		WHERE MONTH(O.OrderDate) = 11 AND YEAR(O.OrderDate) = 1996
	 ) 
AS AvgChange
GO


-- 5.2. Построить запрос для определения среднего и медианного значений стоимости заказов в 1997 году
WITH Temp AS
(
	SELECT ROW_NUMBER() OVER(ORDER BY OS.Subtotal) AS Row, OS.Subtotal AS Subtotal
	FROM Orders AS O
	JOIN [Order Subtotals] AS OS ON OS.OrderID = O.OrderID 
	WHERE YEAR(O.OrderDate) = 1997
)

SELECT (
			SELECT AVG(OS.Subtotal)
			FROM Orders AS O
			JOIN [Order Subtotals] AS OS ON OS.OrderID = O.OrderID 
			WHERE YEAR(O.OrderDate) = 1997
	   ) AS AvgPrice,
	   (
			SELECT Subtotal 
			FROM Temp
			WHERE Row = (SELECT (COUNT(*) + 1) / 2 FROM Temp)
	   ) AS Median
GO