from flask import Flask, request
import thjdb

isopen=0

app = Flask(__name__)

@app.route('/')
def hello_world():
    return 'hello world'

@app.route('/register', methods=['POST'])
def register():
    global isopen
    if (request.form.get('name') == 'ttbachyinsda' and request.form.get('pass') == '123456789'):
        s = request.form.get('method')
        if (s == 'open'):
            if (isopen == 0):
                thjdb.open()
                isopen = 1
            return "open successfully"
        else:
            if (s == 'execsql'):
                if (isopen == 1):
                    t = request.form.get('sql')
                    return thjdb.execSQL(t.encode("ascii"))
                else:
                    return "You have not logged in."
            else: 
                if (s == 'close'):
                    if (isopen == 1):
                        thjdb.close()
                        isopen = 0
                return "close successfully"

if __name__ == '__main__':
    app.run()