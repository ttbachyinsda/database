使用说明：

2.0.6新增功能：变长数据表，但是目前还没有变长类型，亟待加入。具体用法参考testflexible

如何创建数据表：

    string filename = "onetable.tb";
    Table* onetable = new FixedSizeTable();                            //此处创建了一个新的表
    onetable->setfilename(filename);					//设置文件名
    onetable->setname("testiterator");					//设置表名
    vector<string> clname;				
    vector<DataBaseType*> cltype;
    clname.push_back("userid");
    clname.push_back("password");
    clname.push_back("age");						//设置列的名称
    string t1="INTE"; string t2="CHAR"; string t3="INTE";
    string condition="FRTO00000000791160";
    char *testcondition = new char[condition.length()];
    memcpy(testcondition,condition.data(),condition.length());
    DataBaseType* type1=UIC::reconvert(t1.data(),6,true);		//设置列的类型
    int index=0;
    type1->readcondition(testcondition,index);				//为列添加条件语句
    delete[] testcondition;
    DataBaseType* type2=UIC::reconvert(t2.data(),20,true);
    DataBaseType* type3=UIC::reconvert(t3.data(),2,true);		//设置列的类型
    cltype.push_back(type1);
    cltype.push_back(type2);
    cltype.push_back(type3);
    onetable->createTable(clname, cltype);				//创建表，如果文件已存在会删除掉重建一个
    onetable->Initialize();						//初始化表，必须调用这个函数才能使用

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

    iterator = IteratorFactory::getiterator(onetable);	//新建一个iterator，指向表的第一个数据，如果没有第一个available为false
    record = RecordFactory::getrecord(onetable);	//新建一个record
    temp = new char[iterator->getcurrentsize()];
    if (iterator->available()) {			//这步是必须判断的
        int tempsize;
        iterator->getdata(temp, tempsize);		//获取char*格式的原数据
        record->Input(temp);				//解析数据
        for (int i = 0; i < 3; i++) {
            cout << "yes: " << i << ' ' << record->getAt(i) << endl;	//输出
        }
    }

如何插入数据：

    Record* t = RecordFactory::getrecord(onetable);
    for (int i = 0; i < 200000; i++) {
        aaa[0] = InttoString(i);
        aaa[1] = "12345678";
        aaa[2] = "58";
        bool can=t->set(aaa);						//set函数可以反解析数据，返回值说明是否合法
        if (can)							//这是合法的时候
            onetable->FastAllInsert(pagenum, pageposition, t);		//pagenum和pageposition返回的是插入的页号和在页内位置
        //if (i%1000==0) cout<<pagenum<<' '<<pageposition<<endl;
    }
    delete t;								//注意record对于同类型的数据是可以复用的
    delete[] aaa;

如何删除数据：

    iterator->access(300, 0);				//定位
    cout << "try to delete" << endl;
    iterator->deletedata();				//删除
    if (iterator->available()) {
        int tempsize;
        iterator->getdata(temp, tempsize);		//由于定长的表是与最后一个交换的，所以需要获取那个地方的数据
        record->Input(temp);
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

条件判断的类型有以下几种：

FRTO frTO FRto frto NTEQ CHOI

格式如下：

FRTO PARA1 PARA2 表示[PARA1,PARA2]

frTO PARA1 PARA2 表示(PARA1,PARA2]

FRto PARA1 PARA2 表示[PARA1,PARA2)

frto PARA1 PARA2 表示(PARA2,PARA2)

NTEQ PARA1 表示 ≠PARA1

CHOI PARANUM PARA1 PARA2 ... PARANUM 表示在这些中选择一个。

注意PARA的长度是实际长度+1，最后一位保存是不是NULL。

DataBaseType有两个函数readcondition可以读取条件信息。
