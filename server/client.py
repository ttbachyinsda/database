import requests
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
SQLQUERY2 = 'drop database student;'
print type(SQLQUERY)
onedata = {'name': 'ttbachyinsda', 'pass': '123456789', 'method': 'open'}
r = requests.post("http://128.199.74.228:5000/register", data=onedata)
print r.text
onedata = {'name': 'ttbachyinsda', 'pass': '123456789', 'method': 'execsql', 'sql': SQLQUERY}
r = requests.post("http://128.199.74.228:5000/register", data=onedata)
print r.text