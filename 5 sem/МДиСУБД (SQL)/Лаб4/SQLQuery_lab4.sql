USE University_Lab3_MDiSUBD;
GO

-- 4. Добавить факультеты КСИС и ФИТУ
INSERT Faculty 
VALUES 
	(NEWID(), 'КСИС'),
	(NEWID(), 'ФИТУ')
GO


-- 5. Добавить преподавателей Васечкина и Петечкина на факультеты КСИС и ФИТУ соответственно
INSERT INTO Prepods (ID, LAST_NAME, FIRST_NAME, FACULTY_ID) 
VALUES
	(NEWID(), 'Васечкин', 'Василий', (SELECT ID FROM Faculty WHERE NAME='КСИС')),
	(NEWID(), 'Петечкин', 'Петр', (SELECT ID FROM Faculty WHERE NAME='ФИТУ'))
GO


-- Создать студентов Иванова и Петрова (для п.2)
INSERT  INTO Students (ID, LAST_NAME, FIRST_NAME, GROUP_ID) 
VALUES
	(NEWID(), 'Иванов', 'Иван', NULL),
	(NEWID(), 'Петров', 'Петр', NULL)
GO


-- 1. Добавить новую группу с номером 123456 + 3. Назначить студента Иванова старостой группы
INSERT GROUPS 
VALUES 
	((SELECT ID FROM Students WHERE LAST_NAME='Иванов'),
	'123456',
	(SELECT ID FROM Students WHERE LAST_NAME='Иванов'),
	(SELECT ID FROM Faculty WHERE NAME='КСИС'))
GO


-- 2. Внести в группу 123456 студентов Иванова и Петрова
UPDATE Students
SET GROUP_ID=(SELECT ID FROM GROUPS WHERE NAME='123456')
WHERE LAST_NAME='Иванов'
UPDATE Students
SET GROUP_ID=(SELECT ID FROM GROUPS WHERE NAME='123456')
WHERE LAST_NAME='Петров'
GO


-- 6.	Назначить преподавателю Васечкину ведение предмета «Введение в специальность» для группы 123456.
-- предмет
INSERT Subjects 
VALUES (NEWID(), 'Введение в специальность', (SELECT FACULTY_ID FROM Prepods WHERE LAST_NAME='Васечкин'))
GO

-- типы учебных нагрузок 
INSERT TYPE_STUDY_LOAD 
VALUES
	(NEWID(), 'Стандартная'),
	(NEWID(), 'Повышенная'),
	(NEWID(), 'Пониженная')
GO

-- учебная нагрузка
INSERT STUDY_LOAD 
VALUES 
	(60, 
	(SELECT ID FROM Subjects WHERE NAME='Введение в специальность'), 
	(SELECT ID FROM TYPE_STUDY_LOAD WHERE NAME='Стандартная'), 
	'ВвС')
GO

-- занятие
INSERT LESSONS VALUES 
	((SELECT ID FROM GROUPS WHERE NAME='123456'), 
	(SELECT ID FROM Prepods WHERE LAST_NAME='Васечкин'), 
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='Введение в специальность')))
GO


-- 7. Поставить студенту Иванову по предмету «Введение в специальность» оценку 10,
-- отметить отсутствие студента Петрова на данном занятии
INSERT INTO RATING (ID, DATE, VAL, STUDENT_ID, STUDY_ID, PREPODS_ID, IS_ABSENT)
VALUES 
	(NEWID(), '2021-10-23',	10,
	(SELECT ID FROM Students WHERE LAST_NAME = N'Иванов'),
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='Введение в специальность')),
	(SELECT ID FROM Prepods WHERE LAST_NAME = N'Васечкин'),
	'N'),
	(NEWID(),'2021-10-23', NULL,
	(SELECT ID FROM Students WHERE LAST_NAME = N'Петров'),
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='Введение в специальность')),
	(SELECT ID FROM Prepods WHERE LAST_NAME = N'Васечкин'),
	'Y')
GO

----------------------------------------------------------------------------------------------------------------
-- 8. Наполнить базу таким образом, чтобы в базе появилась информация по различным предметам (минимум 4),
-- по каждому из которых стояло бы не менее 3 отметок (минимум 5 студентам). 
-- По как минимум двум запросам вывести статистику выполнения

-- добавление студентов
INSERT  INTO Students (ID, LAST_NAME, FIRST_NAME, GROUP_ID) 
VALUES
	(NEWID(), 'Тёркин', 'Василий', NULL),
	(NEWID(), 'Раскольников', 'Радион', NULL),
	(NEWID(), 'Безухов', 'Пьер', NULL),
	(NEWID(), 'Болконский', 'Андрей', NULL),
	(NEWID(), 'Курагин', 'Анатолий', NULL)
GO

-- добавление группы
INSERT GROUPS 
VALUES 
	((SELECT ID FROM Students WHERE LAST_NAME='Болконский'),
	'654321',
	(SELECT ID FROM Students WHERE LAST_NAME='Болконский'),
	(SELECT ID FROM Faculty WHERE NAME='ФИТУ'))
SELECT * FROM GROUPS
GO

-- распределение студентов по группам
UPDATE Students
SET GROUP_ID=(SELECT ID FROM GROUPS WHERE NAME='654321')
WHERE LAST_NAME='Болконский'
UPDATE Students
SET GROUP_ID=(SELECT ID FROM GROUPS WHERE NAME='654321')
WHERE LAST_NAME='Безухов'
UPDATE Students
SET GROUP_ID=(SELECT ID FROM GROUPS WHERE NAME='654321')
WHERE LAST_NAME='Курагин'
UPDATE Students
SET GROUP_ID=(SELECT ID FROM GROUPS WHERE NAME='123456')
WHERE LAST_NAME='Тёркин'
UPDATE Students
SET GROUP_ID=(SELECT ID FROM GROUPS WHERE NAME='123456')
WHERE LAST_NAME='Раскольников'
SELECT * FROM Students
GO

-- добавление преподавателей
INSERT INTO Prepods (ID, LAST_NAME, FIRST_NAME, FACULTY_ID) 
VALUES
	(NEWID(), 'Анисимов', 'Владимир', (SELECT ID FROM Faculty WHERE NAME='КСИС')),
	(NEWID(), 'Старуха', 'Алена', (SELECT ID FROM Faculty WHERE NAME='КСИС'))
SELECT * FROM Prepods
GO

-- добавление предметов
INSERT Subjects 
VALUES 
	(NEWID(), 'Законы и нормы общества', (SELECT FACULTY_ID FROM Prepods WHERE LAST_NAME='Старуха')),
	(NEWID(), 'Математика. Математический анализ', (SELECT FACULTY_ID FROM Prepods WHERE LAST_NAME='Анисимов')),
	(NEWID(), 'Философия', (SELECT FACULTY_ID FROM Prepods WHERE LAST_NAME='Петечкин'))
SELECT * FROM Subjects
GO

-- добавление учебной нагрузки
INSERT STUDY_LOAD 
VALUES 
	(200, 
	(SELECT ID FROM Subjects WHERE NAME='Законы и нормы общества'), 
	(SELECT ID FROM TYPE_STUDY_LOAD WHERE NAME='Повышенная'), 
	'ЗиНО'),
	(160, 
	(SELECT ID FROM Subjects WHERE NAME='Математика. Математический анализ'), 
	(SELECT ID FROM TYPE_STUDY_LOAD WHERE NAME='Стандартная'), 
	'ММА'),
	(40, 
	(SELECT ID FROM Subjects WHERE NAME='Философия'), 
	(SELECT ID FROM TYPE_STUDY_LOAD WHERE NAME='Пониженная'), 
	'Фил')
SELECT * FROM STUDY_LOAD
GO

-- добавление занятий
INSERT LESSONS VALUES 
	((SELECT ID FROM GROUPS WHERE NAME='654321'), 
	(SELECT ID FROM Prepods WHERE LAST_NAME='Петечкин'), 
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='Философия'))),
	((SELECT ID FROM GROUPS WHERE NAME='123456'), 
	(SELECT ID FROM Prepods WHERE LAST_NAME='Анисимов'), 
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='Математика. Математический анализ'))),
	((SELECT ID FROM GROUPS WHERE NAME='123456'), 
	(SELECT ID FROM Prepods WHERE LAST_NAME='Старуха'), 
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='Законы и нормы общества')))
SELECT * FROM LESSONS
GO

-- добавление отметок
INSERT INTO RATING (ID, DATE, VAL, STUDENT_ID, STUDY_ID, PREPODS_ID, IS_ABSENT)
VALUES 
	(NEWID(), '2021-10-24',	8,
	(SELECT ID FROM Students WHERE LAST_NAME = N'Раскольников'),
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='Введение в специальность')),
	(SELECT ID FROM Prepods WHERE LAST_NAME = N'Васечкин'),
	'N'),
	(NEWID(),'2021-10-24', 6,
	(SELECT ID FROM Students WHERE LAST_NAME = N'Тёркин'),
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='Введение в специальность')),
	(SELECT ID FROM Prepods WHERE LAST_NAME = N'Васечкин'),
	'N '),
	(NEWID(), '2021-10-25',	9,
	(SELECT ID FROM Students WHERE LAST_NAME = N'Болконский'),
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='Философия')),
	(SELECT ID FROM Prepods WHERE LAST_NAME = N'Петечкин'),
	'N'),
	(NEWID(),'2021-10-25', 5,
	(SELECT ID FROM Students WHERE LAST_NAME = N'Курагин'),
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='Философия')),
	(SELECT ID FROM Prepods WHERE LAST_NAME = N'Петечкин'),
	'N '),
	(NEWID(), '2021-10-25',	10,
	(SELECT ID FROM Students WHERE LAST_NAME = N'Безухов'),
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='Философия')),
	(SELECT ID FROM Prepods WHERE LAST_NAME = N'Петечкин'),
	'N'),
	(NEWID(), '2021-10-26',	4,
	(SELECT ID FROM Students WHERE LAST_NAME = N'Раскольников'),
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='Законы и нормы общества')),
	(SELECT ID FROM Prepods WHERE LAST_NAME = N'Старуха'),
	'N'),
	(NEWID(), '2021-10-26',	10,
	(SELECT ID FROM Students WHERE LAST_NAME = N'Тёркин'),
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='Законы и нормы общества')),
	(SELECT ID FROM Prepods WHERE LAST_NAME = N'Старуха'),
	'N'),
	(NEWID(), '2021-10-26',	7,
	(SELECT ID FROM Students WHERE LAST_NAME = N'Петров'),
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='Законы и нормы общества')),
	(SELECT ID FROM Prepods WHERE LAST_NAME = N'Старуха'),
	'N'),
	(NEWID(), '2021-10-26',	NULL,
	(SELECT ID FROM Students WHERE LAST_NAME = N'Иванов'),
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='Законы и нормы общества')),
	(SELECT ID FROM Prepods WHERE LAST_NAME = N'Старуха'),
	'Y'),
	(NEWID(), '2021-10-25',	10,
	(SELECT ID FROM Students WHERE LAST_NAME = N'Петров'),
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='Математика. Математический анализ')),
	(SELECT ID FROM Prepods WHERE LAST_NAME = N'Анисимов'),
	'N'),
	(NEWID(), '2021-10-25',	10,
	(SELECT ID FROM Students WHERE LAST_NAME = N'Иванов'),
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='Математика. Математический анализ')),
	(SELECT ID FROM Prepods WHERE LAST_NAME = N'Анисимов'),
	'N'),
	(NEWID(), '2021-10-25',	10,
	(SELECT ID FROM Students WHERE LAST_NAME = N'Тёркин'),
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='Математика. Математический анализ')),
	(SELECT ID FROM Prepods WHERE LAST_NAME = N'Анисимов'),
	'N'),
	(NEWID(), '2021-10-25',	10,
	(SELECT ID FROM Students WHERE LAST_NAME = N'Раскольников'),
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='Математика. Математический анализ')),
	(SELECT ID FROM Prepods WHERE LAST_NAME = N'Анисимов'),
	'N')
SELECT * FROM RATING
GO


--------------------------------------------------------------------------------------------------------------------------
-- 9. Добавить в БД произвольную файловую группу. Добавить .ndf файл
ALTER DATABASE University_Lab3_MDiSUBD
ADD FILEGROUP MyGroup;
GO
ALTER DATABASE University_Lab3_MDiSUBD 
ADD FILE 
(
    NAME = testfile,
	-- путь для сохранения файла
    FILENAME = 'C:\YCHEBA\5_term\tfile.ndf',
    SIZE = 5MB,
    MAXSIZE = 100MB,
    FILEGROWTH = 5MB
)
TO FILEGROUP MyGroup;
GO


-- 10. Очистить БД от внесенных данных.
DELETE RATING
DELETE LESSONS
DELETE Prepods  
DELETE STUDY_LOAD
DELETE Subjects
UPDATE Students SET GROUP_ID = NULL;
DELETE GROUPS
DELETE Students
DELETE Faculty
DELETE TYPE_STUDY_LOAD
GO

ALTER DATABASE University_Lab3_MDiSUBD
REMOVE FILE testfile
GO

ALTER DATABASE University_Lab3_MDiSUBD
REMOVE FILEGROUP MyGroup
GO