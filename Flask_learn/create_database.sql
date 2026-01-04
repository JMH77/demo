-- 创建数据库
CREATE DATABASE IF NOT EXISTS vue_flask_demo 
CHARACTER SET utf8mb4 
COLLATE utf8mb4_unicode_ci;

-- 使用数据库
USE vue_flask_demo;

-- 用户表（Flask-SQLAlchemy 会自动创建，这里仅作参考）
-- CREATE TABLE IF NOT EXISTS users (
--     id INT AUTO_INCREMENT PRIMARY KEY,
--     name VARCHAR(50) NOT NULL,
--     age INT DEFAULT 0,
--     created_at DATETIME DEFAULT CURRENT_TIMESTAMP
-- );

-- 消息表（Flask-SQLAlchemy 会自动创建，这里仅作参考）
-- CREATE TABLE IF NOT EXISTS messages (
--     id INT AUTO_INCREMENT PRIMARY KEY,
--     content TEXT NOT NULL,
--     timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
-- );

-- 查看所有表
SHOW TABLES;
