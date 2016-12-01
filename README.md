使用说明：

2.0.9.8改动：

添加了对于日期date类型的支持，使用chrono和date库。但在使用前须注意：

1.确认-lcurl这个编译选项能够使用，即安装了curl库
2.c++支持到c++14

在testdate中有对应的测试程序，分成了两部分：

第一部分：如何获取时间并对时间进行一定的处理（beginpretest）

第二部分：对date类型进行操作（begintest）

有几个关键的部分：

1.如何输入年月日时分秒？
    time_point<system_clock,chrono::nanoseconds> temp1=static_cast<sys_days>(year_month_day{year{2013}/6/8})+make_time(hours{5},minutes{7},seconds{9},nanoseconds{22},0).to_duration();

看起来好长的样子……另外注意有日必须有月和年，有秒必须有分和时，依次类推。

2.大小是多少？

8个字节。

3.本地时间和系统时间存哪个？

输进来的时间。

然后如果以后需要区分的话可以参照beginpretest里面的内容。

4.UIC是不是应该有一些过程来支持一下？

是的，比如说time_point<system_clock,chrono::nanoseconds>转字符串，以后会加上的。


2.0.9变化：

使windows、linux和mac平台均可编译运行所有文件，且不会污染其他平台。注意sqlengine文件夹下的makefile.win是专为windows系统编译使用的，在windows系统下使用make -f makefile.wim 就可以生成windows的版本，在linux和mac系统下使用make 可以生成linux和mac的版本。

合并了底层、索引、语句处理三个模块

修复了一些bug

2.0.8进行了大量的改动，包括如下：

1.加入了varchar类型，可以存储变长字符串

2.修改了condition条件的读入方法和结构，现在结构如下：

FRTO LEN1 PARA1 LEN2 PARA2

NTEQ LEN1 PARA1

CHOI NUM LEN1 PARA1 LEN2 PARA2 ……

现在只能通过readcondition(string*)来读入条件

3.大幅加快了输入数据的速度

4.提供了一种新的方法来获取数据：

iterator->getdata(record)

这样就不用管理一个char*的内存了

5.改变了变长表部分过程的逻辑结构，使其能够正常工作

如何创建数据表：

    string filename = "oneflexibletable.tb";
    cout << "test iterator table begin..." << endl;
    Table* onetable = new FlexibleTable();  //这是一个变长表
    onetable->setfilename(filename);
    onetable->setname("testiterator");
    vector<string> clname;
    vector<DataBaseType*> cltype;
    clname.push_back("userid");
    clname.push_back("password");
    clname.push_back("age");
    string t1 = "INTE";
    string t2 = "VARC";                 //类型为VARCHAR，最大长度为20
    string t3 = "INTE";
    string *conditions = new string[3];
    conditions[0]="FRTO";
    conditions[1]="0";
    conditions[2]="500000";
    DataBaseType* type1 = UIC::reconvert(t1.data(), 6, true);
    type1->readcondition(conditions);   //新的条件输入方法
    DataBaseType* type2 = UIC::reconvert(t2.data(), 20, true);
    DataBaseType* type3 = UIC::reconvert(t3.data(), 2, true);
    cltype.push_back(type1);
    cltype.push_back(type2);
    cltype.push_back(type3);
    onetable->createTable(clname, cltype);
    onetable->Initialize();

如何打开数据表：

    onetable = new FixedSizeTable();
    onetable->setfilename(filename);
    onetable->Initialize();
    这样数据表可以从文件中自动读取信息

如何将数据表与数据库绑定：

    onedb.setfilename(filename);
    onedb.setname(dbname);
    onedb.Initialize();					//关闭数据库后remove文件名就可以删除数据库
    Table* t1 = new FixedSizeTable();
    t1->setfilename(table1);
    t1->setname(table1);
    Table* t2 = new FixedSizeTable();
    t2->setfilename(table2);
    t1->setname(table2);
    onedb.addTable(t1);
    onedb.addTable(t2);					//绑定表
    trytoInitializeTable(t1);
    trytoInitializeTable(t2);				//然后别忘了这俩表是要初始化的
    onedb.removeTable(0);				//删除一个表，这是由插入的序号决定的，此时会调用表的析构函数
    绑定之后，调用数据库的析构函数时会调用每一个表的析构函数，就不用自己去调用了。

如何查询指定位置的数据：

    Iterator* iterator = IteratorFactory::getiterator(onetable);
    Record* record = RecordFactory::getrecord(onetable);
    if (iterator->available()) {
        iterator->getdata(record);  //之前的过程也是可以使的，这样写更加简便
        for (int i = 0; i < 3; i++) {
            cout << "yes: " << i << ' ' << record->getAt(i) << endl;
        }
    }

如何插入数据：

    for (int i = 0; i < 200000; i++) {
        aaa[0] = InttoString(i);
        aaa[1] = "a"+InttoString(i);
        aaa[2] = "58";
        bool can = t->set(aaa);
        if (can && i%3)
        {
            can=t->setAt(1,"",true);
            t->update();
        }
        if (can)
            onetable->FastAllInsert(pagenum, pageposition, t);
        //if (i%1000==0) cout<<pagenum<<' '<<pageposition<<endl;
    }

如何删除数据：

    iterator->access(300, 0);
    cout << "try to delete" << endl;
    iterator->deletedata();
    if (iterator->available()) {
        iterator->getdata(record);
        for (int i = 0; i < 3; i++) {
            cout << "yes: " << i << ' ' << record->getAt(i) << endl;
        }
    }

另外

    ++(*iterator); 可以使迭代器+1，即访问下一个元素

注意：当使用
    record 某->getAt(i)时，如果那个数据是NULL，会返回一个NULL__DATA字符串。如果那个数据类型是int，高位会补0。注意这一点。
    如果担心出问题，也可以record 某->getcolumns() 和 record 某->getcolumncount()可以直接使用read、write（这两个函数不会判断，且输入的长度
需要为实际长度+1，最后一位存是不是null），checkRightAndChange()（这一系列函数都是安全的），然后使用record的update函数更新（别忘了）再插入。
同理，setAt函数也是需要执行完之后update的。
