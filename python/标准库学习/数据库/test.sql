-- Schema for test 

--Projects are hight-level activities made up of tasks
create table project(
    name  text primary key,
    description text,
    deadline date
);

-- Tasks are steps that can be taken to complete a project
create table task(
    id        integer primary key autoincrement not null,
    priority  integer default 1,
    details   text,
    status    text,
    deadline  date,
    completed_on date,
    project  text  no null references project(name)
);

