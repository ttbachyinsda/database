var depth = 0;

function addEle(list) {
    testModel.clear()
    for (var name = 0; name < list.length; name++) {
        testModel.append({"name":list[name]});
        console.log(list[name]);
    }
}
