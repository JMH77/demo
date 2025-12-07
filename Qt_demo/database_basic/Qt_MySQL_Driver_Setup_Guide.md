# Qt 5.15.2 MySQL 驱动配置完整攻略

## 问题描述

当在 Qt 5.15.2 + MinGW 的项目中使用 MySQL 数据库时，会遇到以下错误：

```
QSqlDatabase: QMYSQL driver not loaded
QSqlDatabase: available drivers: QSQLITE QODBC QODBC3 QPSQL QPSQL7
```

**原因**：Qt 安装时默认没有编译 MySQL 驱动插件（`qsqlmysql.dll`），需要手动构建。

---

## 完整解决方案

### 第一步：确保安装了 Qt 源码

1. 打开 **Qt Maintenance Tool**（通常在 `C:\Qt\MaintenanceTool.exe`）
2. 登录 Qt 账号
3. 选择"维护动作" → "添加(A)或移除组件"
4. 展开 `Qt 5.15.2` → 找到你使用的套件（如 `Desktop Qt 5.15.2 MinGW 81.0 64-bit`）
5. 展开后在底部勾选 **`Sources`**（约 1.2 GB）
6. 继续安装

**验证**：打开 PowerShell 执行
```powershell
Test-Path C:\Qt\5.15.2\Src\qtbase\src\plugins\sqldrivers\mysql
```
结果应为 `True`。

---

### 第二步：下载 MySQL Connector/C（重要！不是 C++）

**常见错误**：下载 `MySQL Connector/C++` 会包含错误的库文件。

**正确做法**：下载 `MySQL Connector/C` 或 `MySQL Server` 的 C API。

#### 方式一：命令行下载（推荐）

```powershell
Invoke-WebRequest -Uri "https://cdn.mysql.com/Downloads/Connector-C/mysql-connector-c-6.1.11-winx64.msi" `
                  -OutFile "D:\MySQL\mysql-connector-c-6.1.11-winx64.msi"
```

#### 方式二：手动下载

访问 [MySQL 官方下载页](https://dev.mysql.com/downloads/connector/c/)，选择：
- **Operating System**：Microsoft Windows
- **Packaging**：MSI Installer（或 ZIP Archive）
- **Architecture**：x86, 64-bit

下载后保存到 `D:\MySQL\`。

---

### 第三步：安装 MySQL Connector/C

```powershell
msiexec /i "D:\MySQL\mysql-connector-c-6.1.11-winx64.msi" INSTALLDIR="D:\MySQL\mysql-connector-c-6.1.11" /qn
```

**验证**：检查以下文件是否存在
```powershell
Test-Path D:\MySQL\lib\libmysql.lib
Test-Path D:\MySQL\lib\libmysql.dll
Test-Path D:\MySQL\include\mysql.h
```

---

### 第四步：准备 Qt 源码目录

进入 Qt 源码的驱动目录：

```powershell
cd C:\Qt\5.15.2\Src\qtbase\src\plugins\sqldrivers
```

创建文件 `qtsqldrivers-config.pri`（这个文件 Qt 5.15.2 没有自带）：

```powershell
@"
QT_CONFIG += sql-odbc sql-psql
contains(QT_CONFIG, sql-mysql): QT_CONFIG += sql-mysql
"@ | Set-Content -Path C:\Qt\5.15.2\Src\qtbase\src\plugins\sqldrivers\qtsqldrivers-config.pri
```

**验证**：
```powershell
Get-Content C:\Qt\5.15.2\Src\qtbase\src\plugins\sqldrivers\qtsqldrivers-config.pri
```

---

### 第五步：编译 MySQL 驱动

进入 MySQL 驱动源码目录：

```powershell
cd C:\Qt\5.15.2\Src\qtbase\src\plugins\sqldrivers\mysql
```

使用 **Qt MinGW 套件的 qmake**（而不是系统的 qmake）生成 Makefile：

```powershell
& "C:\Qt\5.15.2\mingw81_64\bin\qmake.exe" -spec win32-g++ `
  "QMAKE_INCDIR_MYSQL=D:/MySQL/include" `
  "QMAKE_LIBDIR_MYSQL=D:/MySQL/lib" `
  "QMAKE_LIBS_MYSQL=-LD:/MySQL/lib -llibmysql" `
  mysql.pro
```

**注意**：用 `/` 而不是 `\` 作为路径分隔符。

编译 Release 版本：

```powershell
mingw32-make release
```

编译 Debug 版本（可选）：

```powershell
mingw32-make debug
```

**成功标志**：在以下目录看到 DLL 文件
```
C:\Qt\5.15.2\Src\qtbase\src\plugins\sqldrivers\plugins\sqldrivers\qsqlmysql.dll
C:\Qt\5.15.2\Src\qtbase\src\plugins\sqldrivers\plugins\sqldrivers\qsqlmysql.dll.debug
```

---

### 第六步：部署生成的驱动文件

#### 6.1 复制驱动插件到 Qt 插件目录

```powershell
Copy-Item "C:\Qt\5.15.2\Src\qtbase\src\plugins\sqldrivers\plugins\sqldrivers\qsqlmysql.dll" `
          "C:\Qt\5.15.2\mingw81_64\plugins\sqldrivers\" -Force

Copy-Item "C:\Qt\5.15.2\Src\qtbase\src\plugins\sqldrivers\plugins\sqldrivers\qsqlmysql.dll.debug" `
          "C:\Qt\5.15.2\mingw81_64\plugins\sqldrivers\" -Force
```

#### 6.2 复制 MySQL 客户端库到 Qt bin 目录

```powershell
Copy-Item "D:\MySQL\lib\libmysql.dll" `
          "C:\Qt\5.15.2\mingw81_64\bin\" -Force
```

---

### 第七步：验证驱动加载成功

在你的 Qt 程序中添加测试代码：

```cpp
#include <QSqlDatabase>
#include <QDebug>

int main() {
    QStringList drivers = QSqlDatabase::drivers();
    qDebug() << "Available drivers:" << drivers;
    
    if (drivers.contains("QMYSQL")) {
        qDebug() << "✓ MySQL driver loaded successfully!";
    } else {
        qDebug() << "✗ MySQL driver NOT found!";
    }
}
```

运行程序，输出应包含 `QMYSQL`。

---

## 常见问题排查

### 问题1：编译时报错 "Library 'mysql' is not defined"

**原因**：下载的是 `MySQL Connector/C++` 而不是 `Connector/C`。

**解决**：
- 卸载 C++ 版本
- 下载正确的 `mysql-connector-c-6.1.11-winx64.msi`
- 验证 `D:\MySQL\lib\libmysql.lib` 存在

### 问题2："QMYSQL driver not loaded"

**原因**：驱动 DLL 或 MySQL 客户端库缺失或路径错误。

**排查步骤**：
1. 确认 `C:\Qt\5.15.2\mingw81_64\plugins\sqldrivers\qsqlmysql.dll` 存在
2. 确认 `C:\Qt\5.15.2\mingw81_64\bin\libmysql.dll` 存在
3. 在 Qt Creator 中，确保项目使用的是 `Qt 5.15.2 MinGW 64-bit` 套件（与编译驱动的套件一致）

### 问题3："duplicate connection name 'qt_sql_default_connection'"

**原因**：多次调用 `QSqlDatabase::addDatabase("QMYSQL")`。

**解决**：确保只初始化一次数据库连接。例如：

```cpp
void databasemanager::initDatabase() {
    const QString connectionName = QStringLiteral("main_connection");
    
    // 检查连接是否已存在，存在则直接使用
    QSqlDatabase db = QSqlDatabase::contains(connectionName)
            ? QSqlDatabase::database(connectionName)
            : QSqlDatabase::addDatabase("QMYSQL", connectionName);
    
    db.setDatabaseName("your_database");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("password");
    db.setPort(3306);
    
    if (!db.isOpen() && !db.open()) {
        qDebug() << "Failed to connect to database";
    }
}
```

或者在 `MainWindow` 中只调用一次初始化，不要既在构造函数中调用，又在外部调用。

---

## 部署到其他机器

如果要在另一台没有 Qt 开发环境的机器上运行程序，需要复制这两个文件到应用程序输出目录或 PATH：

1. `qsqlmysql.dll`（放在 `plugins/sqldrivers/` 子目录）
2. `libmysql.dll`（放在应用程序目录或 system32）

---

## 总结

| 步骤 | 关键操作 | 验证方法 |
|------|---------|---------|
| 1 | 安装 Qt 源码 | `Test-Path C:\Qt\5.15.2\Src\qtbase\src\plugins\sqldrivers\mysql` |
| 2 | 下载 Connector/C | `Test-Path D:\MySQL\lib\libmysql.lib` |
| 3 | 创建 `qtsqldrivers-config.pri` | 文件存在且内容正确 |
| 4 | qmake 生成 Makefile | Makefile 文件出现 |
| 5 | mingw32-make 编译 | `qsqlmysql.dll` 生成 |
| 6 | 复制 DLL 文件 | 驱动和库文件在正确位置 |
| 7 | 验证加载 | 程序输出包含 `QMYSQL` |

---

祝你成功配置 Qt MySQL 驱动！
