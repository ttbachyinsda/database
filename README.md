使用说明：

3.0.0.0正式发布：

一个学期的努力成果，数据库已经能够正常使用！

欢迎各位进行尝试！Linux x64 QT UI和Python接口编译通过

2.1.0.8改动：

将聚集函数处的mpq_class换成了mpreal库，使其能够正常的工作。小数位数的输出可以由define的那个MAX_DIGITS控制。

使用flask编写了一个数据库的server和client，具体请尝试用client.py连接到指定的ip地址。

2.1.0.7改动：

添加了一个加密模块，使用AES方式加密，具体请见testdatabase。

注意一旦encrypt，就处在未初始化状态，

有一个函数 isencrypt可以判断是不是在加密状态

其他改动：

removeTable 这个函数现在能正确删除其他文件了（.tableinfo .tb?）

修复了一个插入索引时的bug

为所有表添加了一个存储外链信息的linkedcolumn

修复了一个虚表Iterator的bug，该bug会使在表为空的时候访问出问题

添加了一个删除索引的模块

添加了一个build api的工具，使用qmake配合该工具即可进行编译

2.1.0.5改动：

添加了新的类型：Bulb和Text，具体示例请见testhashflexible。特点是在表中只占8个字节，用checkrightandchange输入实际内容，用output获得实际内容，用read和write只能获取链接（8个字节）。

添加了comparealgo（各种类型的比较算法），注意返回值请通过小于0，大于0或者等于0来判断，不要==-1这么写

添加了tablecondition，使用方法为：

    onetable->gettablecondition()->push_back(make_triple(2,3,"5"));
    onetable->gettablecondition()->push_back(make_triple(3,5,"7"));

    for (auto s = onetable->gettablecondition()->begin(); s != onetable->gettablecondition()->end();s++)
    {
        cout<<(*s).first<<' '<<(*s).second.first<<' '<<(*s).second.second<<endl;
    }

其中make_triple是一个宏。由于mingw的限制，暂不支持c++17的语法，所以只能这么做了/(ㄒoㄒ)/~~

修改flexibletable的数据页上限为5000

2.1.0.2改动：

添加了HashFlexibleTable，一种基于hash桶的表

注意：

HashFlexibleTable有一个FastFind函数可以调用，可以用hash的方法判断是否存在（注意即使非聚集索引存在时也会使用hash方法）

“高IO优化”算法之后会实现，暂时没有必要实现

2.1.0.0改动：

添加了两种group算法，

Group类直接通过访问表取得数据

RawGroup类需要自己输入数据

使用都很简便

注意：输出的为有理数，所以可能带分号

另外，需要确认自己的编译器支持gmp这个库，windows下请将bin下的gmpformingw32.rar中的文件复制到对应的qt mingw目录下即可，linux下应该可以直接装的吧。

另外修复了flexibletable下的一个严重bug，这个bug不能发现已经删除的记录

2.0.9.9改动：

添加了virtual table，一个只存在于内存的虚拟表。

特点是无法进行保存和从文件中的读取。

索引依然能够在virtual table 中使用。

2.0.9.8改动：

添加了对于日期date类型的支持，使用chrono和date库。但在使用前须注意：

c++支持到c++11

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
