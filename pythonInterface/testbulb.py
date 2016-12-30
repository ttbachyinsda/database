#!/usr/bin/env python
# -*- coding=utf-8 -*-

import thjdb
import json


def parseSQLResult(res_str):
    res_json = json.loads(res_str)
    if not res_json:
        print "OK."
        return
    if 'result' in res_json:
        res_tbl = res_json['result']
        for line in json.loads(res_tbl):
            print "\t".join(line)


def executeSQL(sqlstr):
    print "Query:", sqlstr
    result = thjdb.execSQL(sqlstr)
    parseSQLResult(result)


def storeAvatar(uid, pic_name):
    print "Loading %s into database" % pic_name
    thjdb.storeBinaryFile("users", uid, pic_name)


def getAvatar(uid, output_name):
    print "Retrieving %s from database" % output_name
    thjdb.getBinaryFile("users", uid, output_name)

if __name__ == "__main__":
    thjdb.open()
    executeSQL("DROP DATABASE test;")
    executeSQL("CREATE DATABASE test;")
    executeSQL("USE test;")
    executeSQL("CREATE TABLE users (id int(5), avatar varbinary(), primary key (id));")
    executeSQL("SELECT * FROM users;")
    storeAvatar("10001", "pictures/1.jpg")
    storeAvatar("10002", "pictures/2.jpg")
    storeAvatar("10003", "pictures/3.jpg")
    storeAvatar("10004", "pictures/4.jpg")
    executeSQL("SELECT * FROM users;")
    getAvatar("10001", "output/1.jpg")
    getAvatar("10002", "output/2.jpg")
    getAvatar("10003", "output/3.jpg")
    getAvatar("10004", "output/4.jpg")
    thjdb.close()