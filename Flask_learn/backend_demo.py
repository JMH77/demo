"""
Flask 后端服务 - 前后端通信 Demo
演示如何接收和处理来自 Vue 前端的 HTTP 请求
连接 MySQL 数据库
"""

from flask import Flask, request, jsonify
from flask_cors import CORS
from flask_sqlalchemy import SQLAlchemy
from datetime import datetime
import pymysql

# 必须在使用 pymysql 之前安装
pymysql.install_as_MySQLdb()

app = Flask(__name__)

# ==================== 数据库配置 ====================
app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql+pymysql://root:jaten123@localhost:3306/vue_flask_demo'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
app.config['SQLALCHEMY_ECHO'] = True

# 初始化数据库
db = SQLAlchemy(app)

# 配置 CORS - 允许前端跨域访问
CORS(app, resources={
    r"/api/*": {
        "origins": ["http://localhost:5173", "http://127.0.0.1:5173"],
        "methods": ["GET", "POST", "PUT", "DELETE"],
        "allow_headers": ["Content-Type"]
    }
})


# ==================== 数据库模型定义 ====================

class User(db.Model):
    """用户表"""
    __tablename__ = 'users'
    
    id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    name = db.Column(db.String(50), nullable=False)
    age = db.Column(db.Integer, default=0)
    created_at = db.Column(db.DateTime, default=datetime.now)
    
    def to_dict(self):
        return {
            'id': self.id,
            'name': self.name,
            'age': self.age,
            'created_at': self.created_at.isoformat() if self.created_at else None
        }


class Message(db.Model):
    """消息表"""
    __tablename__ = 'messages'
    
    id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    content = db.Column(db.Text, nullable=False)
    timestamp = db.Column(db.DateTime, default=datetime.now)
    
    def to_dict(self):
        return {
            'id': self.id,
            'content': self.content,
            'timestamp': self.timestamp.isoformat() if self.timestamp else None
        }


# ==================== 路由定义 ====================

@app.route('/')
def home():
    """首页 - 服务状态检查"""
    return jsonify({
        "status": "running",
        "message": "Flask 后端服务正在运行",
        "timestamp": datetime.now().isoformat()
    })


@app.route('/api/test', methods=['GET'])
def test_get():
    """测试 GET 请求"""
    return jsonify({
        "success": True,
        "message": "GET 请求成功！",
        "data": {
            "server": "Flask",
            "timestamp": datetime.now().isoformat(),
            "method": "GET"
        }
    })


@app.route('/api/data', methods=['POST'])
def handle_post():
    """测试 POST 请求 - 接收 JSON 数据"""
    try:
        data = request.get_json()
        print(f"📥 收到 POST 数据: {data}")
        
        return jsonify({
            "success": True,
            "message": "POST 请求处理成功！",
            "received_data": data,
            "processed_at": datetime.now().isoformat()
        })
    
    except Exception as e:
        return jsonify({
            "success": False,
            "error": str(e)
        }), 400


@app.route('/api/user', methods=['GET'])
def get_user():
    """测试带查询参数的 GET 请求"""
    user_id = request.args.get('id')
    user_name = request.args.get('name')
    
    print(f"📥 收到查询参数: id={user_id}, name={user_name}")
    
    return jsonify({
        "success": True,
        "message": "带参数的 GET 请求成功！",
        "params": {
            "id": user_id,
            "name": user_name
        },
        "query_result": f"查询用户: {user_name} (ID: {user_id})"
    })


@app.route('/api/message', methods=['POST'])
def receive_message():
    """接收并保存用户消息"""
    try:
        data = request.get_json()
        message_content = data.get('message')
        
        if not message_content:
            return jsonify({
                "success": False,
                "error": "消息不能为空"
            }), 400
        
        new_message = Message(content=message_content)
        db.session.add(new_message)
        db.session.commit()
        
        print(f"💬 收到消息: {message_content}")
        print(f"📊 消息ID: {new_message.id}")
        
        return jsonify({
            "success": True,
            "message": "消息接收成功！",
            "saved_message": new_message.to_dict(),
            "total_messages": Message.query.count()
        })
    
    except Exception as e:
        db.session.rollback()
        print(f"❌ 错误: {str(e)}")
        return jsonify({
            "success": False,
            "error": str(e)
        }), 400


@app.route('/api/messages', methods=['GET'])
def get_all_messages():
    """获取所有消息列表"""
    try:
        messages = Message.query.order_by(Message.timestamp.desc()).all()
        return jsonify({
            "success": True,
            "data": [msg.to_dict() for msg in messages],
            "count": len(messages)
        })
    except Exception as e:
        return jsonify({
            "success": False,
            "error": str(e)
        }), 400


@app.route('/api/users', methods=['GET'])
def get_users():
    """获取用户列表"""
    try:
        users = User.query.all()
        return jsonify({
            "success": True,
            "data": [user.to_dict() for user in users],
            "count": len(users)
        })
    except Exception as e:
        return jsonify({
            "success": False,
            "error": str(e)
        }), 400


@app.route('/api/users', methods=['POST'])
def create_user():
    """创建新用户"""
    try:
        data = request.get_json()
        
        if not data.get('name'):
            return jsonify({
                "success": False,
                "error": "用户名不能为空"
            }), 400
        
        new_user = User(
            name=data.get('name'),
            age=data.get('age', 0)
        )
        db.session.add(new_user)
        db.session.commit()
        
        print(f"👤 创建新用户: {new_user.to_dict()}")
        
        return jsonify({
            "success": True,
            "message": "用户创建成功！",
            "data": new_user.to_dict()
        }), 201
    
    except Exception as e:
        db.session.rollback()
        print(f"❌ 错误: {str(e)}")
        return jsonify({
            "success": False,
            "error": str(e)
        }), 400


# ==================== 错误处理 ====================

@app.errorhandler(404)
def not_found(error):
    """404 错误处理"""
    return jsonify({
        "success": False,
        "error": "接口不存在",
        "path": request.path
    }), 404


@app.errorhandler(500)
def internal_error(error):
    """500 错误处理"""
    return jsonify({
        "success": False,
        "error": "服务器内部错误"
    }), 500


# ==================== 数据库初始化 ====================

def init_database():
    """初始化数据库"""
    try:
        with app.app_context():
            db.create_all()
            
            if User.query.count() == 0:
                print("📊 添加初始用户数据...")
                initial_users = [
                    User(name="张三", age=25),
                    User(name="李四", age=30),
                    User(name="王五", age=28)
                ]
                db.session.add_all(initial_users)
                db.session.commit()
                print(f"✅ 已添加 {len(initial_users)} 个初始用户")
            
            print("✅ 数据库初始化成功！")
            
    except Exception as e:
        print(f"❌ 数据库初始化失败: {str(e)}")
        print("⚠️  请确保 MySQL 服务正在运行")
        print("⚠️  请手动创建数据库: CREATE DATABASE vue_flask_demo CHARACTER SET utf8mb4;")
        raise


# ==================== 启动服务 ====================

if __name__ == '__main__':
    print("=" * 60)
    print("🚀 Flask 后端服务启动中...")
    print("=" * 60)
    print("📡 服务地址: http://localhost:5000")
    print("🗄️  数据库配置:")
    print("   - 主机: localhost:3306")
    print("   - 数据库: vue_flask_demo")
    print("   - 用户: root")
    print("")
    print("📝 API 文档:")
    print("   GET  /api/test       - 测试 GET 请求")
    print("   POST /api/data       - 测试 POST 请求")
    print("   GET  /api/user       - 带参数的 GET 请求")
    print("   POST /api/message    - 发送消息")
    print("   GET  /api/messages   - 获取所有消息")
    print("   GET  /api/users      - 获取用户列表")
    print("   POST /api/users      - 创建新用户")
    print("=" * 60)
    
    init_database()
    
    app.run(
        host='0.0.0.0',
        port=5000,
        debug=True
    )
