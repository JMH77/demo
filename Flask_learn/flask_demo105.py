from flask import Flask,request
app = Flask(__name__)

@app.route("/")
def index() :
    return  "Hello World"

@app.route("/hello",methods=['GET','POST'])
def hello() :
    return "This is /hello"

@app.route("/hi",methods=['POST'])
def hi() :
    return "This is hi" 

#如果前端请求带有参数
@app.route("/param",methods=['GET','POST'])
def print_param() :
    id = request.args.get('id')
    #要是有请求体，先转化为py字典
    json_data = request.get_json()
    name  = json_data.get('name')
    #查看一下get_data
    raw_data = request.get_data()
    print(raw_data)
    return f"ID : {id}  Name : {name}  Data : {raw_data}"

if __name__ == '__main__':
    app.run(debug=True)