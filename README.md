# database
一个有情怀的数据库
Now it has one commands（底层）

这是一个qt工程。直接运行即可执行底层的几个test。

test1：测试类型是否正确

test2：测试数据表能否正确工作

test3：测试数据库能否正确工作

test4可以参考test3的测试方法测试数据库管理系统能否正确工作

test5：测试迭代器能否正确工作

目前可以插入删除数据库、数据表、记录，也可以修改记录的值。具体方法请见tester文件夹的测试代码和代码注释。

使用说明：
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

