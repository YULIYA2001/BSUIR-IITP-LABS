-- ������ 1. ��������� � ��������� �������
CREATE TABLE ParentOf(parent TEXT, child TEXT);

INSERT INTO ParentOf VALUES ('Alice', 'Carol');
INSERT INTO ParentOf VALUES ('Bob', 'Carol');
INSERT INTO ParentOf VALUES ('Carol', 'Dave');
INSERT INTO ParentOf VALUES ('Carol', 'George');
INSERT INTO ParentOf VALUES ('Dave', 'Mary');
INSERT INTO ParentOf VALUES ('Eve', 'Mary');
INSERT INTO ParentOf VALUES ('Mary', 'Frank');

SELECT * FROM ParentOf
GO

-- ��������� ����������� ������� �����:
--1. ������� Mary

WITH Mary_CTE(parent, child)
AS 
(
	SELECT parent, child
	FROM ParentOf 
	WHERE CONVERT(VARCHAR, child) = 'Mary'
	UNION ALL
	SELECT P.parent, P.child
	FROM ParentOf AS P
	JOIN Mary_CTE AS CTE ON CONVERT(VARCHAR, CTE.parent) = CONVERT(VARCHAR, P.child)
)
SELECT parent AS '������ Mary', ' ' AS '      ', parent, child
FROM Mary_CTE
GO

--2. �������� Carol.
WITH Carol_CTE(parent, child)
AS 
(
	SELECT parent, child
	FROM ParentOf 
	WHERE CONVERT(VARCHAR, parent) = 'Carol'
	UNION ALL
	SELECT P.parent, P.child
	FROM ParentOf AS P
	JOIN Carol_CTE AS CTE ON CONVERT(VARCHAR, CTE.child) = CONVERT(VARCHAR, P.parent)
)
SELECT child AS '������� Carol', ' ' AS '      ', parent, child
FROM Carol_CTE
GO



--������ 2. ��������� � ��������� �������
CREATE TABLE Employee (ID INT, salary INT); --ID ���������� � �� ��������
CREATE TABLE Manager (mID INT, eID INT); -- ID ���������, ID ���������
CREATE TABLE Project (name TEXT, mgrID INT); -- �������� ������� � ID ������������

INSERT INTO Employee VALUES (123, 100);
INSERT INTO Employee VALUES (234, 90);
INSERT INTO Employee VALUES (345, 80);
INSERT INTO Employee VALUES (456, 70);
INSERT INTO Employee VALUES (567, 60);
INSERT INTO Manager VALUES (123, 234);
INSERT INTO Manager VALUES (234, 345);
INSERT INTO Manager VALUES (234, 456);
INSERT INTO Manager VALUES (345, 567);
INSERT INTO Project VALUES ('X', 123);

SELECT * FROM Employee
SELECT * FROM Manager
SELECT * FROM Project
GO

-- ��������� ����������� ������ ����� ���������� �������� �� �������.
WITH TotalSalary_CTE(mID, eID, salary)
AS 
(
	SELECT 0, mgrID, salary
	FROM Project
	JOIN Employee ON mgrID = ID
	WHERE CONVERT(VARCHAR, name) = 'X'
	UNION ALL
	SELECT M.mID, M.eID, E.salary
	FROM Manager AS M
	JOIN Employee AS E ON E.ID = M.eID
	JOIN TotalSalary_CTE AS CTE ON CTE.eID = M.mID
)
SELECT *
FROM TotalSalary_CTE
UNION ALL
	SELECT NULL, NULL, SUM(salary)
	FROM TotalSalary_CTE
GO

DROP TABLE  ParentOf, Project, Employee, Manager
GO



-- ������ 3. ��������� ����������� ������, ������� ������ 10 ����� ���������
WITH Fib_CTE(i, a, b, c) AS
(
	SELECT i = 1, a = 0, b = 1, c = 0+1
	UNION ALL
	SELECT i+1, a = b, b = c, c = b+c
	FROM Fib_CTE WHERE i < 10
)
SELECT *, '' AS ' ', a AS '�. ���������' 
FROM Fib_CTE
GO