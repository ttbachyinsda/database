import thjdb

SQLQUERY = '''
create database student;
use student;
create table book (id int(10), name char(20));
insert into book values (1, 'Good'), (2, 'Sth'), (3, 'Test');
create table orders (id int(10), goods char(30), buyer char(10));
insert into orders values (120, 'Soap','James'), (1, 'Laptop', 'John');
select book.name, orders.buyer from book,orders where book.id = orders.id;
insert into orders values (140, 'Coat', 'Alice');
'''

thjdb.open()
print thjdb.execSQL(SQLQUERY)
thjdb.close()

