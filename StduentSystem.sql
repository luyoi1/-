
#数据库课设sql文件

CREATE DATABASE StudentSystem;

USE StudentSystem;


CREATE TABLE IF NOT EXISTS Student (
    ID INT NOT NULL PRIMARY KEY,
    Name VARCHAR(50) NOT NULL,
    ProFession VARCHAR(20) NOT NULL,
    Age SMALLINT NOT NULL,
    Email VARCHAR(30) NOT NULL,
    Grade_Point FLOAT(2,2) DEFAULT 0,
    StuPermissions SMALLINT NOT NULL DEFAULT 1,
    ClassID INT NOT NULL
);

CREATE TABLE IF NOT EXISTS Admin(
    ID INT NOT NULL PRIMARY KEY,
    Name VARCHAR(50) NOT NULL,
    Department VARCHAR(20) NOT NULL,
    Email VARCHAR(30) NOT NULL,
    Age SMALLINT NOT NULL,
    Permissions SMALLINT NOT NULL DEFAULT 3   
);

CREATE TABLE IF NOT EXISTS Course(
    ID INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    Name VARCHAR(20) NOT NULL,
    Score SMALLINT NOT NULL
);

CREATE TABLE IF NOT EXISTS Student_Course(
    ID INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    Student_ID INT NOT NULL,
    Course_ID INT NOT NULL,
    FOREIGN KEY (Student_ID) REFERENCES Student(ID),
    FOREIGN KEY (Course_ID) REFERENCES Course(ID)
);

CREATE TABLE IF NOT EXISTS Student_Grade(
    ID INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    Student_ID INT NOT NULL,
    Course_ID INT NOT NULL,
    Score INT,
    FOREIGN KEY(Student_ID) REFERENCES Student(ID),
    FOREIGN KEY(Course_ID) REFERENCES Course(ID)
);

CREATE TABLE IF NOT EXISTS Class(
    ID INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    Name VARCHAR(20) NOT NULL,
    StudentNum SMALLINT NOT NULL
);

CREATE TABLE IF NOT EXISTS Student_Class_Info(
    ID INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    Student_ID INT NOT NULL,
    Class_ID INT NOT NULL,
    FOREIGN KEY (Student_ID) REFERENCES Student(ID),
    FOREIGN KEY (Class_ID) REFERENCES Class(ID)
);

CREATE TABLE IF NOT EXISTS User_Info(
    ID INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    Student_ID INT NOT NULL UNIQUE,
    Password VARCHAR(50) NOT NULL,
    StuPermissions SMALLINT NOT NULL DEFAULT 1,
    FOREIGN KEY (Student_ID) REFERENCES Student(ID)
);


CREATE TABLE IF NOT EXISTS Key_Info(
    RegisterKey VARCHAR(20) NOT NULL PRIMARY KEY,
    IsUse BOOLEAN NOT NULL DEFAULT false
    
);

CREATE TABLE IF NOT EXISTS Admin_Info(
    ID INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    Admin_ID INT NOT NULL UNIQUE,
    Password VARCHAR(50) NOT NULL,
    Permissions SMALLINT NOT NULL DEFAULT 3,
    RegisterKey VARCHAR(20) NOT NULL UNIQUE,
    FOREIGN KEY (Admin_ID) REFERENCES Admin(ID),
    FOREIGN KEY (RegisterKey) REFERENCES Key_Info(RegisterKey)
);

#触发器语句
DELIMITER $$
CREATE TRIGGER Key_Trigger AFTER INSERT
ON Admin_Info FOR EACH ROW
begin
  update Key_Info
     set IsUse=true
   where new.RegisterKey = Key_Info.RegisterKey;
end;
$$

CREATE TRIGGER Class_Trigger AFTER INSERT
ON Student_Class_Info FOR EACH ROW
begin
  update class
     set StudentNum = StudentNum+1
   where new.Class_ID = class.ID;
end;
$$

CREATE TRIGGER Grade_Trigger AFTER INSERT
ON Student_Grade FOR EACH ROW
begin
    update Student
       set student.Grade_Point=(select AVG((new.Score-60)/10)
       from Student_Grade
        where student.ID = new.Student_ID)
     where ID = new.Student_ID;
end;
$$
DELIMITER ;

CREATE TRIGGER Student_Trigger AFTER insert
ON student FOR EACH ROW
insert into Student_Class_Info(Student_ID,Class_ID)
values(new.ID,new.ClassID);

DELIMITER $$
CREATE TRIGGER DeleteUser_Trigger AFTER delete
ON user_info FOR EACH ROW
begin
   delete from Student_Class_Info
   where old.student_ID=Student_Class_Info.Student_ID;
   delete from Student_Course
   where old.student_ID=Student_Course.Student_ID;
   delete from Student_Grade
   where old.student_ID=Student_Grade.Student_ID;
   update class
      set StudentNum=StudentNum-1
    where (select ClassID from 
    student where ID = old.student_id) =class.ID;
   delete from student
    where old.Student_ID=student.ID;
end;
$$
DELIMITER ;

DELIMITER $$
CREATE TRIGGER ClassUpdate_Trigger AFTER update
ON student FOR EACH ROW
begin
    if old.ClassID != new.ClassID THEN
        update class
           set StudentNum = StudentNum-1
         where class.ID = old.ClassID;
        update class
           set StudentNum = StudentNum+1
         where class.ID = new.ClassID;
    END if;
    if old.StuPermissions != new.StuPermissions THEN
        update user_info
            set user_info.StuPermissions = new.StuPermissions
        where Student_ID = new.ID;
    END if;
end;
$$
DELIMITER ;

CREATE TRIGGER KeyUpdate_Trigger AFTER delete
ON Admin_Info FOR EACH ROW
update Key_Info set IsUse = false
where Key_Info.RegisterKey = old.RegisterKey;