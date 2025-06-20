USE MDiSUBD_lab4
GO

--Создание Факультетов
INSERT INTO Faculty(ID, NAME)
VALUES (NEWID(), N'КСИС'),
	   (NEWID(), N'ФИТУ')
GO

--Создание Студентов
INSERT INTO Students(ID, LAST_NAME, FIRST_NAME, GROUP_ID)
VALUES (NEWID(), N'Петрова', N'Пётр', NULL),
	   (NEWID(), N'Иванова', N'Иван', NULL),
	   (NEWID(), N'Стасовский', N'Стасян', NULL),
	   (NEWID(), N'Ростущий', N'Ростислав', NULL),
	   (NEWID(), N'Веченный', N'Вячеслав', NULL),
	   (NEWID(), N'Свирюга', N'Зверюга', NULL)
GO

--Создание групп
INSERT INTO GROUPS(ID, NAME, HEAD_GROUP, FACULTY_ID) 
VALUES ((SELECT ID FROM Students WHERE LAST_NAME = N'Иванова'), 
		N'123456', 
		(SELECT ID FROM Students WHERE LAST_NAME = N'Иванова'), 
		(SELECT ID FROM Faculty WHERE NAME = N'КСИС'))
GO

--Назначение номера группы студентам
UPDATE Students
SET GROUP_ID=(SELECT ID FROM GROUPS WHERE NAME = N'123456')
GO

--Создание преподавателей
INSERT INTO Prepods(ID, LAST_NAME, FIRST_NAME, FACULTY_ID)
VALUES (NEWID(), N'Васечкин', N'Васян', (SELECT ID FROM Faculty WHERE NAME=N'КСИС')),
	   (NEWID(), N'Петечкина', N'Петучина', (SELECT ID FROM Faculty WHERE NAME=N'ФИТУ'))
GO

--Создание предметов
INSERT INTO Subjects(ID, NAME, FACULTY_ID)
VALUES  (NEWID(), N'Введение в специальность', (SELECT ID FROM Faculty WHERE NAME=N'КСИС')),
		(NEWID(), N'Увод из специальности', (SELECT ID FROM Faculty WHERE NAME=N'КСИС')),
		(NEWID(), N'Стасизм, основы и применение', (SELECT ID FROM Faculty WHERE NAME=N'КСИС')),
		(NEWID(), N'Ростиславоведение', (SELECT ID FROM Faculty WHERE NAME=N'КСИС'))		
GO

--Создание типов нагрузок
INSERT INTO TYPE_STUDY_LOAD(ID, NAME)
VALUES  (NEWID(), N'Душная'),
		(NEWID(), N'Вольготная')
GO

--Создание нагрузок
INSERT INTO STUDY_LOAD(ID, hours, SUBJECT_UD, Type_STUDY_ID)
VALUES (N'ВвВСп',
		42, 
		(SELECT ID FROM Subjects WHERE NAME=N'Введение в специальность'), 
		(SELECT ID FROM TYPE_STUDY_LOAD WHERE NAME=N'Душная')),
		(N'УвиСп',
		8, 
		(SELECT ID FROM Subjects WHERE NAME=N'Увод из специальности'), 
		(SELECT ID FROM TYPE_STUDY_LOAD WHERE NAME=N'Вольготная')),
		(N'СтОиП',
		28, 
		(SELECT ID FROM Subjects WHERE NAME=N'Стасизм, основы и применение'), 
		(SELECT ID FROM TYPE_STUDY_LOAD WHERE NAME=N'Вольготная')),
		(N'РвоВени',
		84, 
		(SELECT ID FROM Subjects WHERE NAME=N'Ростиславоведение'), 
		(SELECT ID FROM TYPE_STUDY_LOAD WHERE NAME=N'Душная'))
GO 

--Создание предметов
INSERT INTO LESSONS(GROUP_ID, PREPOD_ID, STUDY_ID)
VALUES ((SELECT ID FROM GROUPS WHERE NAME = N'123456'),
		(SELECT ID FROM Prepods WHERE LAST_NAME = N'Васечкин'),
		(SELECT STUDY_LOAD.ID FROM STUDY_LOAD JOIN Subjects ON Subjects.ID = SUBJECT_UD WHERE Subjects.NAME = N'Введение в специальность')),
	   ((SELECT ID FROM GROUPS WHERE NAME = N'123456'),
		(SELECT ID FROM Prepods WHERE LAST_NAME = N'Васечкин'),
		(SELECT STUDY_LOAD.ID FROM STUDY_LOAD JOIN Subjects ON Subjects.ID = SUBJECT_UD WHERE Subjects.NAME = N'Стасизм, основы и применение')),
	   ((SELECT ID FROM GROUPS WHERE NAME = N'123456'),
		(SELECT ID FROM Prepods WHERE LAST_NAME = N'Петечкина'),
		(SELECT STUDY_LOAD.ID FROM STUDY_LOAD JOIN Subjects ON Subjects.ID = SUBJECT_UD WHERE Subjects.NAME = N'Увод из специальности')),
	   ((SELECT ID FROM GROUPS WHERE NAME = N'123456'),
		(SELECT ID FROM Prepods WHERE LAST_NAME = N'Петечкина'),
		(SELECT STUDY_LOAD.ID FROM STUDY_LOAD JOIN Subjects ON Subjects.ID = SUBJECT_UD WHERE Subjects.NAME = N'Ростиславоведение'))
GO

--Создание оценок
INSERT INTO RATING (ID, DATE, VAL, STUDENT_ID, STUDY_ID, PREPODS_ID, IS_ABSENT)
VALUES (NEWID(),
		'2021-10-22',
		10,
		(SELECT ID FROM Students WHERE LAST_NAME = N'Иванова'),
		(SELECT STUDY_LOAD.ID FROM STUDY_LOAD JOIN Subjects ON Subjects.ID = SUBJECT_UD WHERE Subjects.NAME = N'Введение в специальность'),
		(SELECT ID FROM Prepods WHERE LAST_NAME = N'Васечкин'),
		'N'),
		(NEWID(),
		'2021-10-22',
		NULL,
		(SELECT ID FROM Students WHERE LAST_NAME = N'Петрова'),
		(SELECT STUDY_LOAD.ID FROM STUDY_LOAD JOIN Subjects ON Subjects.ID = SUBJECT_UD WHERE Subjects.NAME = N'Введение в специальность'),
		(SELECT ID FROM Prepods WHERE LAST_NAME = N'Васечкин'),
		'Y'),
		(NEWID(),
		'2021-10-21',
		10,
		(SELECT ID FROM Students WHERE LAST_NAME = N'Стасовский'),
		(SELECT STUDY_LOAD.ID FROM STUDY_LOAD JOIN Subjects ON Subjects.ID = SUBJECT_UD WHERE Subjects.NAME = N'Стасизм, основы и применение'),
		(SELECT ID FROM Prepods WHERE LAST_NAME = N'Васечкин'),
		'N'),
		(NEWID(),
		'2021-10-21',
		4,
		(SELECT ID FROM Students WHERE LAST_NAME = N'Свирюга'),
		(SELECT STUDY_LOAD.ID FROM STUDY_LOAD JOIN Subjects ON Subjects.ID = SUBJECT_UD WHERE Subjects.NAME = N'Ростиславоведение'),
		(SELECT ID FROM Prepods WHERE LAST_NAME = N'Петечкина'),
		'N'),
		(NEWID(),
		'2021-10-21',
		4,
		(SELECT ID FROM Students WHERE LAST_NAME = N'Свирюга'),
		(SELECT STUDY_LOAD.ID FROM STUDY_LOAD JOIN Subjects ON Subjects.ID = SUBJECT_UD WHERE Subjects.NAME = N'Увод из специальности'),
		(SELECT ID FROM Prepods WHERE LAST_NAME = N'Петечкина'),
		'N'),
		(NEWID(),
		'2021-10-22',
		4,
		(SELECT ID FROM Students WHERE LAST_NAME = N'Ростущий'),
		(SELECT STUDY_LOAD.ID FROM STUDY_LOAD JOIN Subjects ON Subjects.ID = SUBJECT_UD WHERE Subjects.NAME = N'Стасизм, основы и применение'),
		(SELECT ID FROM Prepods WHERE LAST_NAME = N'Васечкин'),
		'N'),
		(NEWID(),
		'2021-10-23',
		NULL,
		(SELECT ID FROM Students WHERE LAST_NAME = N'Ростущий'),
		(SELECT STUDY_LOAD.ID FROM STUDY_LOAD JOIN Subjects ON Subjects.ID = SUBJECT_UD WHERE Subjects.NAME = N'Ростиславоведение'),
		(SELECT ID FROM Prepods WHERE LAST_NAME = N'Петечкина'),
		'Y'),
		(NEWID(),
		'2021-10-22',
		4,
		(SELECT ID FROM Students WHERE LAST_NAME = N'Ростущий'),
		(SELECT STUDY_LOAD.ID FROM STUDY_LOAD JOIN Subjects ON Subjects.ID = SUBJECT_UD WHERE Subjects.NAME = N'Стасизм, основы и применение'),
		(SELECT ID FROM Prepods WHERE LAST_NAME = N'Васечкин'),
		'N'),
		(NEWID(),
		'2021-10-23',
		8,
		(SELECT ID FROM Students WHERE LAST_NAME = N'Веченный'),
		(SELECT STUDY_LOAD.ID FROM STUDY_LOAD JOIN Subjects ON Subjects.ID = SUBJECT_UD WHERE Subjects.NAME = N'Ростиславоведение'),
		(SELECT ID FROM Prepods WHERE LAST_NAME = N'Петечкина'),
		'N'),

		(NEWID(),
		'2021-10-26',
		NULL,
		(SELECT ID FROM Students WHERE LAST_NAME = N'Веченный'),
		(SELECT STUDY_LOAD.ID FROM STUDY_LOAD JOIN Subjects ON Subjects.ID = SUBJECT_UD WHERE Subjects.NAME = N'Увод из специальности'),
		(SELECT ID FROM Prepods WHERE LAST_NAME = N'Петечкина'),
		'N'),
		(NEWID(),
		'2021-10-26',
		7,
		(SELECT ID FROM Students WHERE LAST_NAME = N'Иванова'),
		(SELECT STUDY_LOAD.ID FROM STUDY_LOAD JOIN Subjects ON Subjects.ID = SUBJECT_UD WHERE Subjects.NAME = N'Увод из специальности'),
		(SELECT ID FROM Prepods WHERE LAST_NAME = N'Петечкина'),
		'N'),
		(NEWID(),
		'2021-10-22',
		NULL,
		(SELECT ID FROM Students WHERE LAST_NAME = N'Ростущий'),
		(SELECT STUDY_LOAD.ID FROM STUDY_LOAD JOIN Subjects ON Subjects.ID = SUBJECT_UD WHERE Subjects.NAME = N'Введение в специальность'),
		(SELECT ID FROM Prepods WHERE LAST_NAME = N'Васечкин'),
		'N')
GO

--Добавление файловой группы
ALTER DATABASE MDiSUBD_lab4
ADD FILEGROUP Test1FG1;
GO

-- Добавление .ndf в файловую группу
ALTER DATABASE MDiSUBD_lab4
ADD FILE
(
    NAME = test1dat3,
    FILENAME = 'C:\Program Files\Microsoft SQL Server\MSSQL11.SQLEXPRESS\MSSQL\DATA\t1dat3.ndf',
    SIZE = 5MB,
    MAXSIZE = 100MB,
    FILEGROWTH = 5MB
)
TO FILEGROUP Test1FG1;
GO

--Очистка изменений
DELETE FROM RATING
DELETE FROM LESSONS
DELETE FROM Prepods  
DELETE FROM STUDY_LOAD
DELETE FROM Subjects
UPDATE Students SET GROUP_ID = NULL;
DELETE FROM GROUPS
DELETE FROM Students
DELETE FROM Faculty
DELETE FROM TYPE_STUDY_LOAD
GO
