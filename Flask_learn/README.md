# Flask 后端服务 - 使用说明

## �️ 数据库准备

### 1. 确保 MySQL 服务正在运行

### 2. 创建数据库（二选一）

**方法一：使用 SQL 文件**
```bash
# 在 MySQL 命令行或客户端中执行
mysql -u root -p < create_database.sql
```

**方法二：手动创建**
```sql
CREATE DATABASE vue_flask_demo CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
```

### 3. 数据库配置信息
- **主机**: localhost
- **端口**: 3306
- **用户**: root
- **密码**: jaten123
- **数据库名**: vue_flask_demo

## �📦 安装依赖

```bash
# 进入 Flask_learn 目录
cd Flask_learn

# 安装依赖包
pip install -r requirements.txt
```

## 🚀 启动后端服务

```bash
python backend_demo.py
```

**首次启动会自动：**
1. 创建数据表（users, messages）
2. 插入初始用户数据
3. 服务在 `http://localhost:5000` 启动

**如果遇到数据库连接错误：**
- 检查 MySQL 服务是否启动
- 确认数据库 `vue_flask_demo` 已创建
- 验证用户名密码是否正确

## 🔧 启动前端服务

在另一个终端：

```bash
# 进入 Vue 项目目录
cd Vue_learn/Vue_see/Vue_104

# 启动前端开发服务器
npm run dev
```

前端将在 `http://localhost:5173` 启动

## 📡 API 接口说明

### 1. GET /api/test
- **功能**: 测试基本 GET 请求
- **返回**: 服务器状态信息

### 2. POST /api/data
- **功能**: 测试 POST 请求
- **请求体**: 
  ```json
  {
    "name": "测试用户",
    "action": "test_post",
    "timestamp": "2026-01-04T10:00:00"
  }
  ```

### 3. GET /api/user?id=123&name=张三
- **功能**: 测试带查询参数的 GET 请求
- **参数**: id, name

### 4. POST /api/message
- **功能**: 发送消息
- **请求体**: 
  ```json
  {
    "message": "你好，这是一条测试消息"
  }
  ```

### 5. GET /api/messages
- **功能**: 获取所有消息列表

### 6. GET /api/users
- **功能**: 获取用户列表

### 7. POST /api/users
- **功能**: 创建新用户
- **请求体**:表结构

### users 表
| 字段 | 类型 | 说明 |
|------|------|------|
| id | INT | 主键，自增 |
| name | VARCHAR(50) | 用户名 |
| age | INT | 年龄 |
| created_at | DATETIME | 创建时间 |

### messages 表
| 字段 | 类型 | 说明 |
|------|------|------|
| id | INT | 主键，自增 |
| content | TEXT | 消息内容 |
| timestamp | DATETIME | 发送时间 |
```python
from flask_sqlalchemy import SQLAlchemy

app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql+pymysql://用户名:密码@localhost:3306/数据库名'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False

db = SQLAlchemy(app)
```

## 🐛 调试技巧

1. **查看控制台输出**: Flask 服务器会打印收到的请求信息
2. **Chrome DevTools**: 在浏览器中按 F12，查看 Network 标签
3. **使用 Postman**: 独立测试 API 接口

## ⚠️ 注意事项

- 确保前后端端口不冲突（前端 5173，后端 5000）
- CORS 已配置，允许跨域请求
- 当前使用内存存储数据，重启服务数据会丢失
- 生产环境需要配置真实数据库
