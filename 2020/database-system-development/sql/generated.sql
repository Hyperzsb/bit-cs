/*==============================================================*/
/* DBMS name:      Microsoft SQL Server 2012                    */
/* Created on:     2020/9/27 20:23:34                           */
/*==============================================================*/


if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('Course') and o.name = 'FK_COURSE_TEACHER_F_TEACHER')
alter table Course
   drop constraint FK_COURSE_TEACHER_F_TEACHER
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('CourseSelected') and o.name = 'FK_COURSESE_COURSE_SE_COURSE')
alter table CourseSelected
   drop constraint FK_COURSESE_COURSE_SE_COURSE
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('CourseSelected') and o.name = 'FK_COURSESE_STUDENT_S_STUDENT')
alter table CourseSelected
   drop constraint FK_COURSESE_STUDENT_S_STUDENT
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('TeachersForStudents') and o.name = 'FK_TEACHERS_STUDENT_W_STUDENT')
alter table TeachersForStudents
   drop constraint FK_TEACHERS_STUDENT_W_STUDENT
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('TeachersForStudents') and o.name = 'FK_TEACHERS_TEACHER_F_TEACHER')
alter table TeachersForStudents
   drop constraint FK_TEACHERS_TEACHER_F_TEACHER
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('Course')
            and   name  = 'teacher_for_course_FK'
            and   indid > 0
            and   indid < 255)
   drop index Course.teacher_for_course_FK
go

if exists (select 1
            from  sysobjects
           where  id = object_id('Course')
            and   type = 'U')
   drop table Course
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('CourseSelected')
            and   name  = 'student_select_course_FK'
            and   indid > 0
            and   indid < 255)
   drop index CourseSelected.student_select_course_FK
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('CourseSelected')
            and   name  = 'course_selected_FK'
            and   indid > 0
            and   indid < 255)
   drop index CourseSelected.course_selected_FK
go

if exists (select 1
            from  sysobjects
           where  id = object_id('CourseSelected')
            and   type = 'U')
   drop table CourseSelected
go

if exists (select 1
            from  sysobjects
           where  id = object_id('Student')
            and   type = 'U')
   drop table Student
go

if exists (select 1
            from  sysobjects
           where  id = object_id('Teacher')
            and   type = 'U')
   drop table Teacher
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('TeachersForStudents')
            and   name  = 'teacher_for_student_FK'
            and   indid > 0
            and   indid < 255)
   drop index TeachersForStudents.teacher_for_student_FK
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('TeachersForStudents')
            and   name  = 'student_with_teacher_FK'
            and   indid > 0
            and   indid < 255)
   drop index TeachersForStudents.student_with_teacher_FK
go

if exists (select 1
            from  sysobjects
           where  id = object_id('TeachersForStudents')
            and   type = 'U')
   drop table TeachersForStudents
go

/*==============================================================*/
/* Table: Course                                                */
/*==============================================================*/
create table Course (
   id                   char(5)              not null,
   name                 varchar(50)          not null,
   score                int                  not null,
   time                 varchar(30)          not null,
   teacher_id           char(10)             not null,
   constraint PK_COURSE primary key nonclustered (id)
)
go

/*==============================================================*/
/* Index: teacher_for_course_FK                                 */
/*==============================================================*/
create index teacher_for_course_FK on Course (
teacher_id ASC
)
go

/*==============================================================*/
/* Table: CourseSelected                                        */
/*==============================================================*/
create table CourseSelected (
   student_id           char(10)             not null,
   course_id            char(5)              not null
)
go

/*==============================================================*/
/* Index: course_selected_FK                                    */
/*==============================================================*/
create index course_selected_FK on CourseSelected (
course_id ASC
)
go

/*==============================================================*/
/* Index: student_select_course_FK                              */
/*==============================================================*/
create index student_select_course_FK on CourseSelected (
student_id ASC
)
go

/*==============================================================*/
/* Table: Student                                               */
/*==============================================================*/
create table Student (
   id                   char(10)             not null,
   name                 varchar(30)          not null,
   constraint PK_STUDENT primary key nonclustered (id)
)
go

/*==============================================================*/
/* Table: Teacher                                               */
/*==============================================================*/
create table Teacher (
   id                   char(10)             not null,
   name                 varchar(30)          not null,
   constraint PK_TEACHER primary key nonclustered (id)
)
go

/*==============================================================*/
/* Table: TeachersForStudents                                   */
/*==============================================================*/
create table TeachersForStudents (
   student_id           char(10)             not null,
   teacher_id           char(10)             not null
)
go

/*==============================================================*/
/* Index: student_with_teacher_FK                               */
/*==============================================================*/
create index student_with_teacher_FK on TeachersForStudents (
student_id ASC
)
go

/*==============================================================*/
/* Index: teacher_for_student_FK                                */
/*==============================================================*/
create index teacher_for_student_FK on TeachersForStudents (
teacher_id ASC
)
go

alter table Course
   add constraint FK_COURSE_TEACHER_F_TEACHER foreign key (teacher_id)
      references Teacher (id)
go

alter table CourseSelected
   add constraint FK_COURSESE_COURSE_SE_COURSE foreign key (course_id)
      references Course (id)
go

alter table CourseSelected
   add constraint FK_COURSESE_STUDENT_S_STUDENT foreign key (student_id)
      references Student (id)
go

alter table TeachersForStudents
   add constraint FK_TEACHERS_STUDENT_W_STUDENT foreign key (student_id)
      references Student (id)
go

alter table TeachersForStudents
   add constraint FK_TEACHERS_TEACHER_F_TEACHER foreign key (teacher_id)
      references Teacher (id)
go

