CREATE DATABASE TEST;

-- ANCESTORS

USE TEST;

create table ParentOf(parent text, child text);
insert into ParentOf values ('Alice', 'Carol');
insert into ParentOf values ('Bob', 'Carol');
insert into ParentOf values ('Carol', 'Dave');
insert into ParentOf values ('Carol', 'George');
insert into ParentOf values ('Dave', 'Mary');
insert into ParentOf values ('Eve', 'Mary');
insert into ParentOf values ('Mary', 'Frank');
insert into ParentOf values ('Bob', 'Ellie');
-----------------------------------------------

with Ancestor(a,d) as (select parent as a, child as d from ParentOf
                    union all
                    select Ancestor.a, ParentOf.child as d
                    from Ancestor, ParentOf
                    where Ancestor.d LIKE ParentOf.parent)
select a from Ancestor where d LIKE 'Mary';

-- SALARY ON THE PROJECT

USE TEST;
create table Employee(ID int, salary int);
create table Manager(mID int, eID int);
create table Project(name text, mgrID int);

insert into Employee values (123, 100);
insert into Employee values (890, 110);
insert into Employee values (234, 90);
insert into Employee values (345, 80);
insert into Employee values (456, 70);
insert into Employee values (567, 60);
insert into Employee values (111, 200);
insert into Employee values (222, 150);
insert into Employee values (333, 120);
insert into Employee values (098, 15);
insert into Manager values (123, 234);
insert into Manager values (111, 222);
insert into Manager values (222, 333);
insert into Manager values (234, 345);
insert into Manager values (234, 456);
insert into Manager values (345, 567);
insert into Manager values (123, 890);
insert into Manager values (890, 098);
insert into Project values ('X', 123);
insert into Project values ('Y', 234);
insert into Project values ('Z', 456);

SELECT * FROM Manager

----- JOINS SOLUTION ---------

DECLARE @Proj varchar;
SET @Proj = 'X';

SELECT @Proj AS 'PROJECT', SUM (salary) as 'SALARY'

FROM (

SELECT DISTINCT (m.mID) as 'ID', salary as 'SALARY'
FROM Manager m INNER JOIN Employee e ON e.ID=m.mID
WHERE m.mID in (SELECT Project.mgrID FROM Project WHERE Project.name LIKE @Proj)
UNION
SELECT m.eID, salary
FROM Manager m INNER JOIN Employee e ON e.ID=m.eID
WHERE m.mID in (SELECT Project.mgrID FROM Project WHERE Project.name LIKE @Proj)
UNION
SELECT m1.eID, salary
FROM Manager m INNER JOIN Manager m1 ON m.eID=m1.mID
			   INNER JOIN Employee e ON e.ID=m1.eID
WHERE m1.mID in (SELECT m.eID
FROM Manager m 
WHERE m.mID in (SELECT Project.mgrID FROM Project WHERE Project.name LIKE @Proj)
				)
UNION
SELECT m2.eID, salary
FROM Manager m2 INNER JOIN Manager m1 ON m1.eID=m2.mID
				INNER JOIN Employee e ON e.ID=m2.eID
WHERE m2.mID in (SELECT m1.eID
FROM Manager m INNER JOIN Manager m1 ON m.eID=m1.mID
			   
WHERE m1.mID in (SELECT m.eID
FROM Manager m 
WHERE m.mID in (SELECT Project.mgrID FROM Project WHERE Project.name LIKE @Proj)
				))) AS T;
				GO;

--- RECURSIVE SOLUTION ----


DECLARE @Proj varchar;
SET @Proj = 'X';
with Superior as (select * from Manager
               union all
               select S.mID, M.eID
               from Superior S, Manager M
               where S.eID = M.mID )
select sum(salary)
from Employee
where ID in
  (select mgrID from Project where name LIKE  @Proj
   union
   select eID from Project, Superior
   where Project.name LIKE  @Proj AND Project.mgrID = Superior.mID );

   GO;

/** ALTERNATIVE SOLUTION TIED TO PROJECT **/

DECLARE @Proj varchar;
SET @Proj = 'X';

WITH PRemps(ID) AS (SELECT mgrID AS ID FROM Project WHERE name LIKE @Proj
                UNION ALL
                SELECT eID AS ID
                FROM Manager M, PRemps X
                WHERE M.mID = X.ID)
SELECT SUM (salary)
FROM Employee
WHERE ID IN (SELECT ID FROM PRemps);

-- FIBONACCI 
WITH FibonacciNumbers (RecursionLevel, FibonacciNumber, NextNumber) 
AS (
   -- Anchor member definition
   SELECT  0  AS RecursionLevel,
           0  AS FibonacciNumber,
           1  AS NextNumber
   UNION ALL
   -- Recursive member definition
   SELECT  a.RecursionLevel + 1 AS RecursionLevel,
           a.NextNumber AS FibonacciNumber,
           a.FibonacciNumber + a.NextNumber AS NextNumber
   FROM FibonacciNumbers a
   WHERE a.RecursionLevel < 10
)
-- Statement that executes the CTE
SELECT  'F' + CAST( fn.RecursionLevel AS VARCHAR) AS FibonacciOrdinal, 
        fn.FibonacciNumber,
        fn.NextNumber
FROM FibonacciNumbers fn
WHERE FibonacciNumber > 0
GO
