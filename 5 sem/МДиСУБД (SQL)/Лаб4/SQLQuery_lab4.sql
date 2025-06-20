USE University_Lab3_MDiSUBD;
GO

-- 4. �������� ���������� ���� � ����
INSERT Faculty 
VALUES 
	(NEWID(), '����'),
	(NEWID(), '����')
GO


-- 5. �������� �������������� ��������� � ��������� �� ���������� ���� � ���� ��������������
INSERT INTO Prepods (ID, LAST_NAME, FIRST_NAME, FACULTY_ID) 
VALUES
	(NEWID(), '��������', '�������', (SELECT ID FROM Faculty WHERE NAME='����')),
	(NEWID(), '��������', '����', (SELECT ID FROM Faculty WHERE NAME='����'))
GO


-- ������� ��������� ������� � ������� (��� �.2)
INSERT  INTO Students (ID, LAST_NAME, FIRST_NAME, GROUP_ID) 
VALUES
	(NEWID(), '������', '����', NULL),
	(NEWID(), '������', '����', NULL)
GO


-- 1. �������� ����� ������ � ������� 123456 + 3. ��������� �������� ������� ��������� ������
INSERT GROUPS 
VALUES 
	((SELECT ID FROM Students WHERE LAST_NAME='������'),
	'123456',
	(SELECT ID FROM Students WHERE LAST_NAME='������'),
	(SELECT ID FROM Faculty WHERE NAME='����'))
GO


-- 2. ������ � ������ 123456 ��������� ������� � �������
UPDATE Students
SET GROUP_ID=(SELECT ID FROM GROUPS WHERE NAME='123456')
WHERE LAST_NAME='������'
UPDATE Students
SET GROUP_ID=(SELECT ID FROM GROUPS WHERE NAME='123456')
WHERE LAST_NAME='������'
GO


-- 6.	��������� ������������� ��������� ������� �������� ��������� � �������������� ��� ������ 123456.
-- �������
INSERT Subjects 
VALUES (NEWID(), '�������� � �������������', (SELECT FACULTY_ID FROM Prepods WHERE LAST_NAME='��������'))
GO

-- ���� ������� �������� 
INSERT TYPE_STUDY_LOAD 
VALUES
	(NEWID(), '�����������'),
	(NEWID(), '����������'),
	(NEWID(), '����������')
GO

-- ������� ��������
INSERT STUDY_LOAD 
VALUES 
	(60, 
	(SELECT ID FROM Subjects WHERE NAME='�������� � �������������'), 
	(SELECT ID FROM TYPE_STUDY_LOAD WHERE NAME='�����������'), 
	'���')
GO

-- �������
INSERT LESSONS VALUES 
	((SELECT ID FROM GROUPS WHERE NAME='123456'), 
	(SELECT ID FROM Prepods WHERE LAST_NAME='��������'), 
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='�������� � �������������')))
GO


-- 7. ��������� �������� ������� �� �������� ��������� � �������������� ������ 10,
-- �������� ���������� �������� ������� �� ������ �������
INSERT INTO RATING (ID, DATE, VAL, STUDENT_ID, STUDY_ID, PREPODS_ID, IS_ABSENT)
VALUES 
	(NEWID(), '2021-10-23',	10,
	(SELECT ID FROM Students WHERE LAST_NAME = N'������'),
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='�������� � �������������')),
	(SELECT ID FROM Prepods WHERE LAST_NAME = N'��������'),
	'N'),
	(NEWID(),'2021-10-23', NULL,
	(SELECT ID FROM Students WHERE LAST_NAME = N'������'),
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='�������� � �������������')),
	(SELECT ID FROM Prepods WHERE LAST_NAME = N'��������'),
	'Y')
GO

----------------------------------------------------------------------------------------------------------------
-- 8. ��������� ���� ����� �������, ����� � ���� ��������� ���������� �� ��������� ��������� (������� 4),
-- �� ������� �� ������� ������ �� �� ����� 3 ������� (������� 5 ���������). 
-- �� ��� ������� ���� �������� ������� ���������� ����������

-- ���������� ���������
INSERT  INTO Students (ID, LAST_NAME, FIRST_NAME, GROUP_ID) 
VALUES
	(NEWID(), 'Ҹ����', '�������', NULL),
	(NEWID(), '������������', '������', NULL),
	(NEWID(), '�������', '����', NULL),
	(NEWID(), '����������', '������', NULL),
	(NEWID(), '�������', '��������', NULL)
GO

-- ���������� ������
INSERT GROUPS 
VALUES 
	((SELECT ID FROM Students WHERE LAST_NAME='����������'),
	'654321',
	(SELECT ID FROM Students WHERE LAST_NAME='����������'),
	(SELECT ID FROM Faculty WHERE NAME='����'))
SELECT * FROM GROUPS
GO

-- ������������� ��������� �� �������
UPDATE Students
SET GROUP_ID=(SELECT ID FROM GROUPS WHERE NAME='654321')
WHERE LAST_NAME='����������'
UPDATE Students
SET GROUP_ID=(SELECT ID FROM GROUPS WHERE NAME='654321')
WHERE LAST_NAME='�������'
UPDATE Students
SET GROUP_ID=(SELECT ID FROM GROUPS WHERE NAME='654321')
WHERE LAST_NAME='�������'
UPDATE Students
SET GROUP_ID=(SELECT ID FROM GROUPS WHERE NAME='123456')
WHERE LAST_NAME='Ҹ����'
UPDATE Students
SET GROUP_ID=(SELECT ID FROM GROUPS WHERE NAME='123456')
WHERE LAST_NAME='������������'
SELECT * FROM Students
GO

-- ���������� ��������������
INSERT INTO Prepods (ID, LAST_NAME, FIRST_NAME, FACULTY_ID) 
VALUES
	(NEWID(), '��������', '��������', (SELECT ID FROM Faculty WHERE NAME='����')),
	(NEWID(), '�������', '�����', (SELECT ID FROM Faculty WHERE NAME='����'))
SELECT * FROM Prepods
GO

-- ���������� ���������
INSERT Subjects 
VALUES 
	(NEWID(), '������ � ����� ��������', (SELECT FACULTY_ID FROM Prepods WHERE LAST_NAME='�������')),
	(NEWID(), '����������. �������������� ������', (SELECT FACULTY_ID FROM Prepods WHERE LAST_NAME='��������')),
	(NEWID(), '���������', (SELECT FACULTY_ID FROM Prepods WHERE LAST_NAME='��������'))
SELECT * FROM Subjects
GO

-- ���������� ������� ��������
INSERT STUDY_LOAD 
VALUES 
	(200, 
	(SELECT ID FROM Subjects WHERE NAME='������ � ����� ��������'), 
	(SELECT ID FROM TYPE_STUDY_LOAD WHERE NAME='����������'), 
	'����'),
	(160, 
	(SELECT ID FROM Subjects WHERE NAME='����������. �������������� ������'), 
	(SELECT ID FROM TYPE_STUDY_LOAD WHERE NAME='�����������'), 
	'���'),
	(40, 
	(SELECT ID FROM Subjects WHERE NAME='���������'), 
	(SELECT ID FROM TYPE_STUDY_LOAD WHERE NAME='����������'), 
	'���')
SELECT * FROM STUDY_LOAD
GO

-- ���������� �������
INSERT LESSONS VALUES 
	((SELECT ID FROM GROUPS WHERE NAME='654321'), 
	(SELECT ID FROM Prepods WHERE LAST_NAME='��������'), 
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='���������'))),
	((SELECT ID FROM GROUPS WHERE NAME='123456'), 
	(SELECT ID FROM Prepods WHERE LAST_NAME='��������'), 
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='����������. �������������� ������'))),
	((SELECT ID FROM GROUPS WHERE NAME='123456'), 
	(SELECT ID FROM Prepods WHERE LAST_NAME='�������'), 
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='������ � ����� ��������')))
SELECT * FROM LESSONS
GO

-- ���������� �������
INSERT INTO RATING (ID, DATE, VAL, STUDENT_ID, STUDY_ID, PREPODS_ID, IS_ABSENT)
VALUES 
	(NEWID(), '2021-10-24',	8,
	(SELECT ID FROM Students WHERE LAST_NAME = N'������������'),
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='�������� � �������������')),
	(SELECT ID FROM Prepods WHERE LAST_NAME = N'��������'),
	'N'),
	(NEWID(),'2021-10-24', 6,
	(SELECT ID FROM Students WHERE LAST_NAME = N'Ҹ����'),
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='�������� � �������������')),
	(SELECT ID FROM Prepods WHERE LAST_NAME = N'��������'),
	'N '),
	(NEWID(), '2021-10-25',	9,
	(SELECT ID FROM Students WHERE LAST_NAME = N'����������'),
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='���������')),
	(SELECT ID FROM Prepods WHERE LAST_NAME = N'��������'),
	'N'),
	(NEWID(),'2021-10-25', 5,
	(SELECT ID FROM Students WHERE LAST_NAME = N'�������'),
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='���������')),
	(SELECT ID FROM Prepods WHERE LAST_NAME = N'��������'),
	'N '),
	(NEWID(), '2021-10-25',	10,
	(SELECT ID FROM Students WHERE LAST_NAME = N'�������'),
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='���������')),
	(SELECT ID FROM Prepods WHERE LAST_NAME = N'��������'),
	'N'),
	(NEWID(), '2021-10-26',	4,
	(SELECT ID FROM Students WHERE LAST_NAME = N'������������'),
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='������ � ����� ��������')),
	(SELECT ID FROM Prepods WHERE LAST_NAME = N'�������'),
	'N'),
	(NEWID(), '2021-10-26',	10,
	(SELECT ID FROM Students WHERE LAST_NAME = N'Ҹ����'),
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='������ � ����� ��������')),
	(SELECT ID FROM Prepods WHERE LAST_NAME = N'�������'),
	'N'),
	(NEWID(), '2021-10-26',	7,
	(SELECT ID FROM Students WHERE LAST_NAME = N'������'),
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='������ � ����� ��������')),
	(SELECT ID FROM Prepods WHERE LAST_NAME = N'�������'),
	'N'),
	(NEWID(), '2021-10-26',	NULL,
	(SELECT ID FROM Students WHERE LAST_NAME = N'������'),
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='������ � ����� ��������')),
	(SELECT ID FROM Prepods WHERE LAST_NAME = N'�������'),
	'Y'),
	(NEWID(), '2021-10-25',	10,
	(SELECT ID FROM Students WHERE LAST_NAME = N'������'),
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='����������. �������������� ������')),
	(SELECT ID FROM Prepods WHERE LAST_NAME = N'��������'),
	'N'),
	(NEWID(), '2021-10-25',	10,
	(SELECT ID FROM Students WHERE LAST_NAME = N'������'),
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='����������. �������������� ������')),
	(SELECT ID FROM Prepods WHERE LAST_NAME = N'��������'),
	'N'),
	(NEWID(), '2021-10-25',	10,
	(SELECT ID FROM Students WHERE LAST_NAME = N'Ҹ����'),
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='����������. �������������� ������')),
	(SELECT ID FROM Prepods WHERE LAST_NAME = N'��������'),
	'N'),
	(NEWID(), '2021-10-25',	10,
	(SELECT ID FROM Students WHERE LAST_NAME = N'������������'),
	(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM Subjects WHERE NAME='����������. �������������� ������')),
	(SELECT ID FROM Prepods WHERE LAST_NAME = N'��������'),
	'N')
SELECT * FROM RATING
GO


--------------------------------------------------------------------------------------------------------------------------
-- 9. �������� � �� ������������ �������� ������. �������� .ndf ����
ALTER DATABASE University_Lab3_MDiSUBD
ADD FILEGROUP MyGroup;
GO
ALTER DATABASE University_Lab3_MDiSUBD 
ADD FILE 
(
    NAME = testfile,
	-- ���� ��� ���������� �����
    FILENAME = 'C:\YCHEBA\5_term\tfile.ndf',
    SIZE = 5MB,
    MAXSIZE = 100MB,
    FILEGROWTH = 5MB
)
TO FILEGROUP MyGroup;
GO


-- 10. �������� �� �� ��������� ������.
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