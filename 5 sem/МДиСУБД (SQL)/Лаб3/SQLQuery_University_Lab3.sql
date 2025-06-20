USE master;
GO

IF DB_ID (N'University_Lab3_MDiSUBD') IS NOT NULL
DROP DATABASE University_Lab3_MDiSUBD;
GO

CREATE DATABASE University_Lab3_MDiSUBD;
GO

USE University_Lab3_MDiSUBD;
GO

CREATE TABLE Faculty
(
    ID UNIQUEIDENTIFIER NOT NULL PRIMARY KEY,
	NAME VARCHAR(30) NOT NULL UNIQUE
);
GO

EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'��������� ����' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'Faculty', @level2type=N'COLUMN',@level2name=N'ID'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'�������� ����������' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'Faculty', @level2type=N'COLUMN',@level2name=N'NAME'
GO

CREATE TABLE GROUPS
(
    ID UNIQUEIDENTIFIER NOT NULL PRIMARY KEY,
	NAME VARCHAR(10) NOT NULL,
	HEAD_GROUP UNIQUEIDENTIFIER,
	FACULTY_ID UNIQUEIDENTIFIER NOT NULL FOREIGN KEY REFERENCES Faculty
);
GO

EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'��������� ����' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GROUPS', @level2type=N'COLUMN',@level2name=N'ID'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'����� ������' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GROUPS', @level2type=N'COLUMN',@level2name=N'NAME'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'�������� ������' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GROUPS', @level2type=N'COLUMN',@level2name=N'HEAD_GROUP'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'���������, � �������� ����������� ������' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'GROUPS', @level2type=N'COLUMN',@level2name=N'FACULTY_ID'
GO

CREATE TABLE LESSONS
(
    GROUP_ID UNIQUEIDENTIFIER NOT NULL FOREIGN KEY REFERENCES GROUPS,
	PREPOD_ID UNIQUEIDENTIFIER NOT NULL,
	STUDY_ID CHAR(20) NOT NULL	
);
GO

ALTER TABLE LESSONS
    ADD CONSTRAINT Key3 PRIMARY KEY (GROUP_ID,PREPOD_ID,STUDY_ID)
GO

EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'��������� ����' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'LESSONS', @level2type=N'COLUMN',@level2name=N'GROUP_ID'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'�������������' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'LESSONS', @level2type=N'COLUMN',@level2name=N'PREPOD_ID'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'������� ��������' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'LESSONS', @level2type=N'COLUMN',@level2name=N'STUDY_ID'
GO

CREATE TABLE Prepods
(
    ID UNIQUEIDENTIFIER NOT NULL PRIMARY KEY,
	LAST_NAME VARCHAR(120) NOT NULL,
	FIRST_NAME VARCHAR(120),
	FACULTY_ID UNIQUEIDENTIFIER NOT NULL FOREIGN KEY REFERENCES Faculty
);
GO

EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'��������� ����' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'Prepods', @level2type=N'COLUMN',@level2name=N'ID'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'������� �������������' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'Prepods', @level2type=N'COLUMN',@level2name=N'LAST_NAME'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'��� �������������' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'Prepods', @level2type=N'COLUMN',@level2name=N'FIRST_NAME'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'���������, �� ������� �������� �������������' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'Prepods', @level2type=N'COLUMN',@level2name=N'FACULTY_ID'
GO

CREATE TABLE RATING
(
    ID UNIQUEIDENTIFIER NOT NULL PRIMARY KEY,
	DATE DATE NOT NULL,
	VAL NUMERIC,
	STUDENT_ID UNIQUEIDENTIFIER NOT NULL,
	STUDY_ID CHAR(20) NOT NULL,
	PREPODS_ID UNIQUEIDENTIFIER NOT NULL FOREIGN KEY REFERENCES Prepods,
	IS_ABSENT CHAR(1) DEFAULT 'N',
	CONSTRAINT chkValue CHECK (VAL>3 AND VAL<=10)
);
GO

EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'��������� ����' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RATING', @level2type=N'COLUMN',@level2name=N'ID'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'���� ��������� �������' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RATING', @level2type=N'COLUMN',@level2name=N'DATE'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'���������� �������' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RATING', @level2type=N'COLUMN',@level2name=N'VAL'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'�������' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RATING', @level2type=N'COLUMN',@level2name=N'STUDENT_ID'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'������� �������' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RATING', @level2type=N'COLUMN',@level2name=N'STUDY_ID'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'�������������' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RATING', @level2type=N'COLUMN',@level2name=N'PREPODS_ID'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'����������� �� ������� �� �������' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'RATING', @level2type=N'COLUMN',@level2name=N'IS_ABSENT'
GO

CREATE TABLE Students
(
    ID UNIQUEIDENTIFIER NOT NULL PRIMARY KEY,
	LAST_NAME VARCHAR(60) NOT NULL,
	FIRST_NAME VARCHAR(30),
	GROUP_ID UNIQUEIDENTIFIER FOREIGN KEY REFERENCES GROUPS
);
GO


EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'��������� ����' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'Students', @level2type=N'COLUMN',@level2name=N'ID'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'������� ��������' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'Students', @level2type=N'COLUMN',@level2name=N'LAST_NAME'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'��� ��������' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'Students', @level2type=N'COLUMN',@level2name=N'FIRST_NAME'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'������, � ������� ��������� �������' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'Students', @level2type=N'COLUMN',@level2name=N'GROUP_ID'
GO

CREATE TABLE STUDY_LOAD
(
	hours NUMERIC,
	SUBJECT_ID UNIQUEIDENTIFIER NOT NULL,
	Type_STUDY_ID UNIQUEIDENTIFIER NOT NULL,
    ID CHAR(20) NOT NULL PRIMARY KEY
);
GO

EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'���������� ����������� ����� �� ����������' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'STUDY_LOAD', @level2type=N'COLUMN',@level2name=N'hours'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'�������' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'STUDY_LOAD', @level2type=N'COLUMN',@level2name=N'SUBJECT_ID'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'��� ��������' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'STUDY_LOAD', @level2type=N'COLUMN',@level2name=N'Type_STUDY_ID'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'��������� ����' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'STUDY_LOAD', @level2type=N'COLUMN',@level2name=N'ID'
GO

CREATE TABLE Subjects
(
    ID UNIQUEIDENTIFIER NOT NULL PRIMARY KEY,
	NAME VARCHAR(120) NOT NULL,
	FACULTY_ID UNIQUEIDENTIFIER FOREIGN KEY REFERENCES Faculty
);
GO

EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'��������� ����' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'Subjects', @level2type=N'COLUMN',@level2name=N'ID'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'�������� ����������' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'Subjects', @level2type=N'COLUMN',@level2name=N'NAME'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'��������� �� ������� ������������ ��������' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'Subjects', @level2type=N'COLUMN',@level2name=N'FACULTY_ID'
GO

CREATE TABLE TYPE_STUDY_LOAD
(
    ID UNIQUEIDENTIFIER NOT NULL PRIMARY KEY,
	NAME VARCHAR(120) NOT NULL UNIQUE
);
GO

EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'��������� ����' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TYPE_STUDY_LOAD', @level2type=N'COLUMN',@level2name=N'ID'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'��� ������� ��������' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TYPE_STUDY_LOAD', @level2type=N'COLUMN',@level2name=N'NAME'
GO

ALTER TABLE GROUPS
	ADD FOREIGN KEY (ID) REFERENCES Students;
ALTER TABLE GROUPS
	ADD FOREIGN KEY (HEAD_GROUP) REFERENCES Students;
GO

ALTER TABLE LESSONS
	ADD FOREIGN KEY (PREPOD_ID) REFERENCES Prepods;
ALTER TABLE LESSONS
	ADD FOREIGN KEY (STUDY_ID) REFERENCES STUDY_LOAD;
GO

ALTER TABLE RATING
	ADD FOREIGN KEY (STUDENT_ID) REFERENCES Students;
ALTER TABLE RATING
	ADD FOREIGN KEY (STUDY_ID) REFERENCES STUDY_LOAD;
GO

ALTER TABLE STUDY_LOAD
	ADD FOREIGN KEY (SUBJECT_ID) REFERENCES Subjects;
ALTER TABLE STUDY_LOAD
	ADD FOREIGN KEY (Type_STUDY_ID) REFERENCES TYPE_STUDY_LOAD;
GO