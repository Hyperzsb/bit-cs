/* 创建数据库及数据表 */
create database CourseManagement
go
use CourseManagement
go
create table Student
(
	id char(10) not null,
	name varchar(30) not null,
	primary key (id)
)
go
create table Teacher
(
	id char(10) not null,
	name varchar(30) not null,
	primary key (id)
)
go
create table TeachersForStudents
(
	student_id char(10) not null,
	teacher_id char(10) not null,
	foreign key (student_id) references Student(id) on delete cascade on update cascade,
	foreign key (teacher_id) references Teacher(id) on delete cascade on update cascade
)
go
create table Course
(
	id char(5) not null,
	name varchar(50) not null,
	score int not null,
	time varchar(30) not null,
	teacher_id char(10) not null,
	primary key (id),
	foreign key (teacher_id) references Teacher(id) on delete cascade on update cascade
)
go
create table CourseSelected
(
	student_id char(10) not null,
	course_id char(5) not null,
	foreign key (student_id) references Student(id) on delete cascade on update cascade,
	foreign key (course_id) references Course(id) on delete cascade on update cascade
)
go
/* 插入测试数据 */
insert into Student (id, name) values
('1120180000', 'ZhangSanyi'),
('1120180001', 'ZhangSaner'),
('1120180002', 'ZhangSansan'),
('1120180003', 'LiSiyi'),
('1120180004', 'LiSier'),
('1120180005', 'LiSisan'),
('1120180006', 'WangWuyi'),
('1120180007', 'WangWuer'),
('1120180008', 'WangWusan'),
('1120180009', 'ZhaoLiuyi'),
('1120180010', 'ZhaoLiuer'),
('1120180011', 'ZhaoLiusan'),
('1120180012', 'ZhengQiyi'),
('1120180013', 'ZhengQier'),
('1120180014', 'ZhengQisan')
go
insert into Teacher (id, name) values
('0020120000','ZhaoLaoshi'),
('0020120001', 'QianLaoshi'),
('0020120002', 'SunLaoshi'),
('0020120003', 'LiLaoshi'),
('0020120004', 'ZhouLaoshi'),
('0020120005', 'WuLaoshi'),
('0020120006', 'ZhengLaoshi'),
('0020120007', 'WangLaoshi')
go
insert into TeachersForStudents (student_id, teacher_id) values
('1120180000', '0020120000'),
('1120180000', '0020120001'),
('1120180000', '0020120002'),
('1120180000', '0020120003'),
('1120180001', '0020120001'),
('1120180001', '0020120002'),
('1120180001', '0020120003'),
('1120180001', '0020120004'),
('1120180002', '0020120002'),
('1120180002', '0020120003'),
('1120180002', '0020120004'),
('1120180002', '0020120005'),
('1120180003', '0020120003'),
('1120180003', '0020120004'),
('1120180003', '0020120005'),
('1120180003', '0020120006'),
('1120180004', '0020120004'),
('1120180004', '0020120005'),
('1120180004', '0020120006'),
('1120180004', '0020120007'),
('1120180005', '0020120005'),
('1120180005', '0020120006'),
('1120180005', '0020120007'),
('1120180005', '0020120000'),
('1120180006', '0020120006'),
('1120180006', '0020120007'),
('1120180006', '0020120000'),
('1120180006', '0020120001'),
('1120180007', '0020120007'),
('1120180007', '0020120000'),
('1120180007', '0020120001'),
('1120180007', '0020120002'),
('1120180008', '0020120000'),
('1120180008', '0020120001'),
('1120180008', '0020120002'),
('1120180008', '0020120003'),
('1120180009', '0020120001'),
('1120180009', '0020120002'),
('1120180009', '0020120003'),
('1120180009', '0020120004'),
('1120180010', '0020120002'),
('1120180010', '0020120003'),
('1120180010', '0020120004'),
('1120180010', '0020120005'),
('1120180011', '0020120003'),
('1120180011', '0020120004'),
('1120180011', '0020120005'),
('1120180011', '0020120006'),
('1120180012', '0020120004'),
('1120180012', '0020120005'),
('1120180012', '0020120006'),
('1120180012', '0020120007'),
('1120180013', '0020120005'),
('1120180013', '0020120006'),
('1120180013', '0020120007'),
('1120180013', '0020120000'),
('1120180014', '0020120006'),
('1120180014', '0020120007'),
('1120180014', '0020120000'),
('1120180014', '0020120001')
go
insert into Course (id, name ,score, time, teacher_id) values
('00001', 'Fundamentals of Programming', 4, '4-9:50~11:25', '0020120000'),
('00002', 'Data Structure', 6, '1-13:20~14:55', '0020120001'),
('00003', 'Discrete Mathematics', 4, '3-8:00~9:35', '0020120002'),
('00004', 'Fundamentals of Web Development', 2, '2-9:50~11:25', '0020120003'),
('00005', 'Java Programming', 2, '5-13:20~14:55', '0020120004'),
('00006', 'Programming Method and Practice', 4, '1-15:15~17:30', '0020120005'),
('00007', 'Basic Practice of Computer Science', 4, '3-9:50~11:25', '0020120006'),
('00008', 'Combinatorial Mathematics', 6, '5-8:00~9:35', '0020120007'),
('00009', 'Computation Theory and Algorithm Analysis', 6, '1-9:50~11:25', '0020120000'),
('00010', 'Database Principle and Design', 4, '2-9:50~11:25', '0020120001'),
('00011', 'Digital Logic', 4, '3-9:50~11:25', '0020120002'),
('00012', 'Object Oriented Technology and Methods', 2, '4-9:50~11:25', '0020120003'),
('00013', 'Fundamentals of Programming', 4, '5-9:50~11:25', '0020120004'),
('00014', 'Data Structure', 6, '3-15:15~17:30', '0020120005'),
('00015', 'Discrete Mathematics', 4, '3-15:15~17:30', '0020120006'),
('00016', 'Fundamentals of Web Development', 2, '3-15:15~17:30', '0020120007')
go
/* 测试语句，同时也为 ADO.NET 中使用的查询语句 */
select Course.id as 'ID', Course.name as 'Course name' , Course.score as 'Score', Teacher.name as 'Teacher name', Course.time as 'Course time'
from Course, Teacher
where Course.teacher_id = Teacher.id
and Course.id not in(
	select cs.course_id
	from CourseSelected as cs
	where cs.student_id = '1120180000'
)
and Teacher.id in (
	select t.id 
	from Teacher as t, TeachersForStudents as tfs
	where t.id = tfs.teacher_id
	and tfs.student_id = '1120180000'
)
go
select Course.id as 'ID', Course.name as 'Course name' , Course.score as 'Score', Teacher.name as 'Teacher name', Course.time as 'Course time'
from Course, Teacher, CourseSelected
where Course.teacher_id = Teacher.id 
and Course.id = CourseSelected.course_id
and CourseSelected.student_id = '1120180000'
and Teacher.id in (
	select t.id 
	from Teacher as t, TeachersForStudents as tfs
	where t.id = tfs.teacher_id
)
go