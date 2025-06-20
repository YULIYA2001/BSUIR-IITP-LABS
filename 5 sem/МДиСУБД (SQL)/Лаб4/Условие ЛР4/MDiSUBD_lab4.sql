USE MDiSUBD_lab4
GO

--�������� �����������
INSERT INTO Faculty(ID, NAME)
VALUES (NEWID(), N'����'),
	   (NEWID(), N'����')
GO

--�������� ���������
INSERT INTO Students(ID, LAST_NAME, FIRST_NAME, GROUP_ID)
VALUES (NEWID(), N'�������', N'ϸ��', NULL),
	   (NEWID(), N'�������', N'����', NULL),
	   (NEWID(), N'����������', N'������', NULL),
	   (NEWID(), N'��������', N'���������', NULL),
	   (NEWID(), N'��������', N'��������', NULL),
	   (NEWID(), N'�������', N'�������', NULL)
GO

--�������� �����
INSERT INTO GROUPS(ID, NAME, HEAD_GROUP, FACULTY_ID) 
VALUES ((SELECT ID FROM Students WHERE LAST_NAME = N'�������'), 
		N'123456', 
		(SELECT ID FROM Students WHERE LAST_NAME = N'�������'), 
		(SELECT ID FROM Faculty WHERE NAME = N'����'))
GO

--���������� ������ ������ ���������
UPDATE Students
SET GROUP_ID=(SELECT ID FROM GROUPS WHERE NAME = N'123456')
GO

--�������� ��������������
INSERT INTO Prepods(ID, LAST_NAME, FIRST_NAME, FACULTY_ID)
VALUES (NEWID(), N'��������', N'�����', (SELECT ID FROM Faculty WHERE NAME=N'����')),
	   (NEWID(), N'���������', N'��������', (SELECT ID FROM Faculty WHERE NAME=N'����'))
GO

--�������� ���������
INSERT INTO Subjects(ID, NAME, FACULTY_ID)
VALUES  (NEWID(), N'�������� � �������������', (SELECT ID FROM Faculty WHERE NAME=N'����')),
		(NEWID(), N'���� �� �������������', (SELECT ID FROM Faculty WHERE NAME=N'����')),
		(NEWID(), N'�������, ������ � ����������', (SELECT ID FROM Faculty WHERE NAME=N'����')),
		(NEWID(), N'�����������������', (SELECT ID FROM Faculty WHERE NAME=N'����'))		
GO

--�������� ����� ��������
INSERT INTO TYPE_STUDY_LOAD(ID, NAME)
VALUES  (NEWID(), N'������'),
		(NEWID(), N'����������')
GO

--�������� ��������
INSERT INTO STUDY_LOAD(ID, hours, SUBJECT_UD, Type_STUDY_ID)
VALUES (N'�����',
		42, 
		(SELECT ID FROM Subjects WHERE NAME=N'�������� � �������������'), 
		(SELECT ID FROM TYPE_STUDY_LOAD WHERE NAME=N'������')),
		(N'�����',
		8, 
		(SELECT ID FROM Subjects WHERE NAME=N'���� �� �������������'), 
		(SELECT ID FROM TYPE_STUDY_LOAD WHERE NAME=N'����������')),
		(N'�����',
		28, 
		(SELECT ID FROM Subjects WHERE NAME=N'�������, ������ � ����������'), 
		(SELECT ID FROM TYPE_STUDY_LOAD WHERE NAME=N'����������')),
		(N'�������',
		84, 
		(SELECT ID FROM Subjects WHERE NAME=N'�����������������'), 
		(SELECT ID FROM TYPE_STUDY_LOAD WHERE NAME=N'������'))
GO 

--�������� ���������
INSERT INTO LESSONS(GROUP_ID, PREPOD_ID, STUDY_ID)
VALUES ((SELECT ID FROM GROUPS WHERE NAME = N'123456'),
		(SELECT ID FROM Prepods WHERE LAST_NAME = N'��������'),
		(SELECT STUDY_LOAD.ID FROM STUDY_LOAD JOIN Subjects ON Subjects.ID = SUBJECT_UD WHERE Subjects.NAME = N'�������� � �������������')),
	   ((SELECT ID FROM GROUPS WHERE NAME = N'123456'),
		(SELECT ID FROM Prepods WHERE LAST_NAME = N'��������'),
		(SELECT STUDY_LOAD.ID FROM STUDY_LOAD JOIN Subjects ON Subjects.ID = SUBJECT_UD WHERE Subjects.NAME = N'�������, ������ � ����������')),
	   ((SELECT ID FROM GROUPS WHERE NAME = N'123456'),
		(SELECT ID FROM Prepods WHERE LAST_NAME = N'���������'),
		(SELECT STUDY_LOAD.ID FROM STUDY_LOAD JOIN Subjects ON Subjects.ID = SUBJECT_UD WHERE Subjects.NAME = N'���� �� �������������')),
	   ((SELECT ID FROM GROUPS WHERE NAME = N'123456'),
		(SELECT ID FROM Prepods WHERE LAST_NAME = N'���������'),
		(SELECT STUDY_LOAD.ID FROM STUDY_LOAD JOIN Subjects ON Subjects.ID = SUBJECT_UD WHERE Subjects.NAME = N'�����������������'))
GO

--�������� ������
INSERT INTO RATING (ID, DATE, VAL, STUDENT_ID, STUDY_ID, PREPODS_ID, IS_ABSENT)
VALUES (NEWID(),
		'2021-10-22',
		10,
		(SELECT ID FROM Students WHERE LAST_NAME = N'�������'),
		(SELECT STUDY_LOAD.ID FROM STUDY_LOAD JOIN Subjects ON Subjects.ID = SUBJECT_UD WHERE Subjects.NAME = N'�������� � �������������'),
		(SELECT ID FROM Prepods WHERE LAST_NAME = N'��������'),
		'N'),
		(NEWID(),
		'2021-10-22',
		NULL,
		(SELECT ID FROM Students WHERE LAST_NAME = N'�������'),
		(SELECT STUDY_LOAD.ID FROM STUDY_LOAD JOIN Subjects ON Subjects.ID = SUBJECT_UD WHERE Subjects.NAME = N'�������� � �������������'),
		(SELECT ID FROM Prepods WHERE LAST_NAME = N'��������'),
		'Y'),
		(NEWID(),
		'2021-10-21',
		10,
		(SELECT ID FROM Students WHERE LAST_NAME = N'����������'),
		(SELECT STUDY_LOAD.ID FROM STUDY_LOAD JOIN Subjects ON Subjects.ID = SUBJECT_UD WHERE Subjects.NAME = N'�������, ������ � ����������'),
		(SELECT ID FROM Prepods WHERE LAST_NAME = N'��������'),
		'N'),
		(NEWID(),
		'2021-10-21',
		4,
		(SELECT ID FROM Students WHERE LAST_NAME = N'�������'),
		(SELECT STUDY_LOAD.ID FROM STUDY_LOAD JOIN Subjects ON Subjects.ID = SUBJECT_UD WHERE Subjects.NAME = N'�����������������'),
		(SELECT ID FROM Prepods WHERE LAST_NAME = N'���������'),
		'N'),
		(NEWID(),
		'2021-10-21',
		4,
		(SELECT ID FROM Students WHERE LAST_NAME = N'�������'),
		(SELECT STUDY_LOAD.ID FROM STUDY_LOAD JOIN Subjects ON Subjects.ID = SUBJECT_UD WHERE Subjects.NAME = N'���� �� �������������'),
		(SELECT ID FROM Prepods WHERE LAST_NAME = N'���������'),
		'N'),
		(NEWID(),
		'2021-10-22',
		4,
		(SELECT ID FROM Students WHERE LAST_NAME = N'��������'),
		(SELECT STUDY_LOAD.ID FROM STUDY_LOAD JOIN Subjects ON Subjects.ID = SUBJECT_UD WHERE Subjects.NAME = N'�������, ������ � ����������'),
		(SELECT ID FROM Prepods WHERE LAST_NAME = N'��������'),
		'N'),
		(NEWID(),
		'2021-10-23',
		NULL,
		(SELECT ID FROM Students WHERE LAST_NAME = N'��������'),
		(SELECT STUDY_LOAD.ID FROM STUDY_LOAD JOIN Subjects ON Subjects.ID = SUBJECT_UD WHERE Subjects.NAME = N'�����������������'),
		(SELECT ID FROM Prepods WHERE LAST_NAME = N'���������'),
		'Y'),
		(NEWID(),
		'2021-10-22',
		4,
		(SELECT ID FROM Students WHERE LAST_NAME = N'��������'),
		(SELECT STUDY_LOAD.ID FROM STUDY_LOAD JOIN Subjects ON Subjects.ID = SUBJECT_UD WHERE Subjects.NAME = N'�������, ������ � ����������'),
		(SELECT ID FROM Prepods WHERE LAST_NAME = N'��������'),
		'N'),
		(NEWID(),
		'2021-10-23',
		8,
		(SELECT ID FROM Students WHERE LAST_NAME = N'��������'),
		(SELECT STUDY_LOAD.ID FROM STUDY_LOAD JOIN Subjects ON Subjects.ID = SUBJECT_UD WHERE Subjects.NAME = N'�����������������'),
		(SELECT ID FROM Prepods WHERE LAST_NAME = N'���������'),
		'N'),

		(NEWID(),
		'2021-10-26',
		NULL,
		(SELECT ID FROM Students WHERE LAST_NAME = N'��������'),
		(SELECT STUDY_LOAD.ID FROM STUDY_LOAD JOIN Subjects ON Subjects.ID = SUBJECT_UD WHERE Subjects.NAME = N'���� �� �������������'),
		(SELECT ID FROM Prepods WHERE LAST_NAME = N'���������'),
		'N'),
		(NEWID(),
		'2021-10-26',
		7,
		(SELECT ID FROM Students WHERE LAST_NAME = N'�������'),
		(SELECT STUDY_LOAD.ID FROM STUDY_LOAD JOIN Subjects ON Subjects.ID = SUBJECT_UD WHERE Subjects.NAME = N'���� �� �������������'),
		(SELECT ID FROM Prepods WHERE LAST_NAME = N'���������'),
		'N'),
		(NEWID(),
		'2021-10-22',
		NULL,
		(SELECT ID FROM Students WHERE LAST_NAME = N'��������'),
		(SELECT STUDY_LOAD.ID FROM STUDY_LOAD JOIN Subjects ON Subjects.ID = SUBJECT_UD WHERE Subjects.NAME = N'�������� � �������������'),
		(SELECT ID FROM Prepods WHERE LAST_NAME = N'��������'),
		'N')
GO

--���������� �������� ������
ALTER DATABASE MDiSUBD_lab4
ADD FILEGROUP Test1FG1;
GO

-- ���������� .ndf � �������� ������
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

--������� ���������
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
