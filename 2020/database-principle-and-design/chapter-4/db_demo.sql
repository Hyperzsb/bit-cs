# Create db_demo database
create database if not exists db_demo;
use db_demo;
# Create student, course and student_course tables
drop table if exists student;
create table if not exists student
(
    id              int         not null auto_increment,
    student_id      char(10)    not null unique,
    student_name    varchar(20) not null,
    student_age     int,
    student_gender  varchar(10) not null,
    student_college varchar(20) not null,
    primary key (id, student_id)
) character set UTF8MB4;
drop table if exists course;
create table if not exists course
(
    id            int         not null auto_increment,
    course_id     char(10)    not null unique,
    course_name   varchar(50) not null unique,
    course_credit int         not null default 100,
    primary key (id, course_id)
) character set UTF8MB4;
drop table if exists student_course;
create table if not exists student_course
(
    id         int      not null auto_increment,
    student_id char(10) not null,
    course_id  char(10) not null,
    grade      int default null,
    primary key (id)
) character set UTF8MB4;
# Insert data into student table
insert into student (student_id, student_name, student_age, student_gender, student_college)
    value ('1120180000', '张三', 20, 'Male', '计算机系');
insert into student (student_id, student_name, student_age, student_gender, student_college)
    value ('1120180001', '李四', 25, 'Male', '计算机系');
insert into student (student_id, student_name, student_age, student_gender, student_college)
    value ('1120180002', '王五', 19, 'Female', '信息系');
insert into student (student_id, student_name, student_age, student_gender, student_college)
    value ('1120180003', '赵六', 21, 'Male', '计算机系');
insert into student (student_id, student_name, student_age, student_gender, student_college)
    value ('1120180004', '邓七', 22, 'Male', '信息系');
insert into student (student_id, student_name, student_age, student_gender, student_college)
    value ('1120180005', '马莉', 20, 'Female', '电子系');
insert into student (student_id, student_name, student_age, student_gender, student_college)
    value ('1120180006', '董南', 18, 'Female', '计算机系');
insert into student (student_id, student_name, student_age, student_gender, student_college)
    value ('1120180007', '王一平', 19, 'Male', '电子系');
insert into student (student_id, student_name, student_age, student_gender, student_college)
    value ('1120180008', '张帆', 19, 'Male', '计算机系');
insert into student (student_id, student_name, student_age, student_gender, student_college)
    value ('1120180009', '欧阳一', 25, 'Female', '计算机系');
insert into student (student_id, student_name, student_age, student_gender, student_college)
    value ('1120180010', '欧阳二', 18, 'Male', '信息系');
insert into student (student_id, student_name, student_age, student_gender, student_college)
    value ('1120180011', '欧阳三', 21, 'Male', '电子系');
# select *
# from student;
# Insert data into course table
insert into course (course_id, course_name, course_credit)
    value ('7020180000', 'C++程序设计', 100);
insert into course (course_id, course_name, course_credit)
    value ('7020180001', '数据结构', 100);
insert into course (course_id, course_name, course_credit)
    value ('7020180002', '信息系统', 100);
insert into course (course_id, course_name, course_credit)
    value ('7020180003', '数字电路', 100);
insert into course (course_id, course_name, course_credit)
    value ('7020180004', '模拟电路', 100);
insert into course (course_id, course_name, course_credit)
    value ('7020180005', '马克思原理概论', 100);
# select *
# from course;
# Insert data into student_course table
# student_college = '计算机系'
insert into student_course (student_id, course_id, grade)
    value ('1120180000', '7020180000', 90);
insert into student_course (student_id, course_id, grade)
    value ('1120180001', '7020180000', 91);
insert into student_course (student_id, course_id, grade)
    value ('1120180003', '7020180000', 82);
insert into student_course (student_id, course_id, grade)
    value ('1120180006', '7020180000', 93);
insert into student_course (student_id, course_id, grade)
    value ('1120180008', '7020180000', 79);
insert into student_course (student_id, course_id, grade)
    value ('1120180009', '7020180000', 99);
insert into student_course (student_id, course_id, grade)
    value ('1120180000', '7020180001', 100);
insert into student_course (student_id, course_id, grade)
    value ('1120180001', '7020180001', 97);
insert into student_course (student_id, course_id, grade)
    value ('1120180003', '7020180001', 89);
insert into student_course (student_id, course_id, grade)
    value ('1120180006', '7020180001', 88);
insert into student_course (student_id, course_id, grade)
    value ('1120180008', '7020180001', 95);
insert into student_course (student_id, course_id, grade)
    value ('1120180009', '7020180001', 90);
insert into student_course (student_id, course_id, grade)
    value ('1120180000', '7020180005', 95);
insert into student_course (student_id, course_id, grade)
    value ('1120180001', '7020180005', 87);
insert into student_course (student_id, course_id, grade)
    value ('1120180003', '7020180005', 88);
insert into student_course (student_id, course_id, grade)
    value ('1120180006', '7020180005', 98);
insert into student_course (student_id, course_id, grade)
    value ('1120180008', '7020180005', 75);
insert into student_course (student_id, course_id, grade)
    value ('1120180009', '7020180005', 97);
# student_college = '信息系'
insert into student_course (student_id, course_id, grade)
    value ('1120180002', '7020180002', 100);
insert into student_course (student_id, course_id, grade)
    value ('1120180004', '7020180002', 91);
insert into student_course (student_id, course_id, grade)
    value ('1120180010', '7020180002', 93);
insert into student_course (student_id, course_id, grade)
    value ('1120180002', '7020180005', 95);
insert into student_course (student_id, course_id, grade)
    value ('1120180004', '7020180005', 97);
insert into student_course (student_id, course_id, grade)
    value ('1120180010', '7020180005', 80);
# student_college = '电子系'
insert into student_course (student_id, course_id, grade)
    value ('1120180005', '7020180003', 87);
insert into student_course (student_id, course_id, grade)
    value ('1120180007', '7020180003', 89);
insert into student_course (student_id, course_id, grade)
    value ('1120180011', '7020180003', 100);
insert into student_course (student_id, course_id, grade)
    value ('1120180005', '7020180004', 93);
insert into student_course (student_id, course_id, grade)
    value ('1120180007', '7020180004', 90);
insert into student_course (student_id, course_id, grade)
    value ('1120180011', '7020180004', 95);
insert into student_course (student_id, course_id, grade)
    value ('1120180005', '7020180005', 78);
insert into student_course (student_id, course_id, grade)
    value ('1120180007', '7020180005', 91);
insert into student_course (student_id, course_id, grade)
    value ('1120180011', '7020180005', 100);
# select *
# from student_course;
# Query test
# 查询年龄小于20岁的所有计算机系的学生
select *
from student
where student_college = '计算机系'
  and student_age < 20;
# 查询学生“马莉”选修的所有课的课程号和成绩
select course.course_id, course.course_credit
from student,
     course,
     student_course
where student.student_id = student_course.student_id
  and student_course.course_id = course.course_id
  and student.student_name = '马莉';
# 查询同时选修了7020180005和7020180000号课程的所有学生姓名和所在系
select student.student_name, student.student_college
from student,
     student_course
where student.student_id = student_course.student_id
  and student_course.course_id = '7020180005'
  and student.student_id in
      (select stu.student_id
       from student as stu,
            student_course as sc
       where stu.student_id = sc.student_id
         and sc.course_id = '7020180000');
# 查询选修了“C++程序设计”课的学生的学号、姓名及成绩
select student.student_id, student.student_name, student_course.grade
from student,
     course,
     student_course
where student.student_id = student_course.student_id
  and course.course_id = student_course.course_id
  and course.course_name = 'C++程序设计';
# 查询学生“王一平”选修课的总学分
select SUM(student_course.grade)
from student,
     student_course
where student.student_id = student_course.student_id
  and student.student_name = '王一平';
# 查询没有选修'7020180000'也没有选修'7020180002'号课的所有学生姓名和所在系
select student.student_name, student.student_college
from student
where student.student_id not in
      (select sc1.student_id
       from student_course as sc1
       where sc1.course_id = '7020180000'
       union
       select sc2.student_id
       from student_course as sc2
       where sc2.course_id = '7020180002');
# 查询所有姓“欧阳”的学生姓名和所在系
select student_name, student_college
from student
where student_name like '欧阳%';
# 查询与“张帆”所选课程都相同的学生姓名
select student.student_name
from student
where not exists
    (select *
     from student_course as sc1
     where student.student_id = sc1.student_id
       and not exists
         (select *
          from student as stu1,
               student_course as sc2
          where stu1.student_id = sc2.student_id
            and stu1.student_name = '张帆'
            and sc2.course_id = sc1.course_id));
# 把信息系的学生“董南”选修的'7020180000'号课加入选课表中
insert into student_course (student_id, course_id)
select student.student_id, '7020180000'
from student
where student.student_name = '董南'
  and student.student_college = '信息系';
# 修改“数据结构”课的学分为3.5
update course
set course_credit=3.5
where course_name = '数据结构';
# 删除所有“电子系”的学生所选修的'7020180004'号课
delete
from student_course
where course_id = '7020180004'
  and student_id in
      (select student.student_id
       from student
       where student.student_college = '电子系');
# Create view student_course_details
create view student_course_details (student_id, student_name, course_name, grade)
as
select student.student_id, student.student_name, course.course_name, student_course.grade
from student,
     course,
     student_course
where student.student_id = student_course.student_id
  and course.course_id = student_course.course_id;
select student_name, course_name
from student_course_details
where grade < 85
  and grade > 70;
