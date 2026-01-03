/* ==========================================================
   第一部分：变量声明 (const vs let)
   Vue 场景：定义组件的数据 (data / ref)
   ========================================================== */

// 1. const (常量)：用来定义“引用”不改动的东西。
// 类比：给箱子贴个死标签，箱子本身不能换，但箱子里的东西可以换。
const appName = "Vue 学习系统"; 
// appName = "React"; // ❌ 报错：常量不能重新赋值

// 重点：对象和数组建议永远用 const
const user = {
    id: 1,
    name: "张三",
    role: "admin"
};
user.name = "李四"; // ✅ 没问题！箱子没换，换的是里面的衣服。

// 2. let (变量)：用来定义随后会变化的值。
// 类比：计数器、开关、循环变量。
let score = 0;
score = 10; // ✅ 可以修改
let isLoading = false; // Vue 中常见的加载状态

/* ==========================================================
   第二部分：箭头函数与模板字符串
   Vue 场景：Methods 方法、计算属性、插值表达式
   ========================================================== */

// 1. 模板字符串 (Template Literals) —— 反引号 ``
// Vue 模板中 :class 或 {{ }} 最喜欢用这个
const welcomeMsg = `欢迎, ${user.name}! 当前应用是: ${appName}`;
console.log("模板字符串演示:", welcomeMsg);

// 2. 箭头函数 (Arrow Function)
// 传统写法：function add(a, b) { return a + b; }
// 现代写法：更短，且不绑定 this (这个特性对 React 很关键，Vue3 组合式 API 也常用)
const addScore = (current, point) => current + point;

// 简写技巧：如果只要返回一个对象，加个括号 ()
// Vue 场景：Vuex/Pinia 中返回 state 时常用
const createUser = (name) => ({ name: name, active: true });

/* ==========================================================
   第三部分：解构赋值 (Destructuring) —— 必考！
   Vue 场景：获取 props，使用 Composition API (const { ref } = Vue)
   ========================================================== */

const course = {
    title: "前端全栈",
    price: 998,
    teacher: {
        name: "王老师",
        age: 35
    }
};

// 1. 对象解构：直接把属性“拆”出来变成变量
// 以前要写：const title = course.title;
const { title, price } = course; 
console.log("解构演示:", title, price); // 输出：前端全栈 998

// 2. 多重解构 + 重命名 (高级技巧)
// 把 teacher.name 拆出来，并且改名叫 teacherName
const { teacher: { name: teacherName } } = course;
console.log("重命名解构:", teacherName); // 输出：王老师

/* ==========================================================
   第四部分：展开运算符 (Spread Operator) ... —— 必考！
   Vue 场景：修改对象状态(React核心)、合并表单数据
   ========================================================== */

const baseInfo = { name: "小明", age: 18 };
const extraInfo = { hobby: "Coding", city: "Beijing" };

// 1. 对象合并
// 想象把两个背包里的东西倒在桌子上，合到一个新背包里
// 如果有重复属性，后面的会覆盖前面的
const fullProfile = { ...baseInfo, ...extraInfo, role: "student" };
console.log("对象合并:", fullProfile);

// 2. 数组复制与合并
const oldTags = ["html", "css"];
const newTags = [...oldTags, "javascript", "vue"]; 
// console.log(newTags) -> ["html", "css", "javascript", "vue"]

/* ==========================================================
   第五部分：数组的高阶方法 (Array Methods) —— 这里的每一行都是 Vue 的 v-for
   Vue 场景：v-for 列表渲染、computed 计算属性
   ========================================================== */

const cart = [
    { id: 1, name: "JS书", price: 100, checked: true },
    { id: 2, name: "Vue书", price: 200, checked: true },
    { id: 3, name: "React书", price: 300, checked: false }, // 未选中
];

// 1. .map() —— “加工厂”
// 作用：把数组里的每一项拿出来，处理一下，变成一个**等长的新数组**。
// Vue 场景：渲染列表 data.map(item => <li key={item.id}>{item.name}</li>)
const itemNames = cart.map(item => item.name);
console.log("Map结果:", itemNames); // ["JS书", "Vue书", "React书"]

// 2. .filter() —— “过滤器”
// 作用：把符合条件的留下来，不符合的扔掉。
// Vue 场景：筛选已完成的订单、搜索功能。
const checkedItems = cart.filter(item => item.checked);
console.log("Filter结果:", checkedItems); // 只剩下 id 1 和 2

// 3. .reduce() —— “累加器” (进阶，但计算总价必用)
// 作用：把一堆东西归纳成一个值。
// Vue 场景：计算购物车总金额 (computed)。
// (total 是累加值，item 是当前项，0 是初始值)
const totalPrice = checkedItems.reduce((total, item) => total + item.price, 0);
console.log("总价:", totalPrice); // 300

// 4. .find() —— “寻人启事”
// 作用：找到**第一个**符合条件的项就停止。
// Vue 场景：根据路由 id 找到对应的商品详情。
const targetBook = cart.find(item => item.id === 2);

/* ==========================================================
   第六部分：异步处理 (Promise & Async/Await) —— 接口请求必备
   Vue 场景：onMounted 生命周期里请求后端数据
   ========================================================== */

// 模拟一个假接口请求
const fetchUserData = () => {
    return new Promise((resolve, reject) => {
        console.log("⏳ 正在请求服务器...");
        setTimeout(() => {
            // 2秒后成功返回数据
            resolve({ status: 200, data: "后端返回的用户列表" });
            // 或者 reject("网络错误")
        }, 2000);
    });
};

// ❌ 以前的写法 (回调地狱/链式调用)
// fetchUserData().then(res => console.log(res));

// ✅ 现在的写法 (Async/Await) —— 把异步代码写得像同步一样
// Vue 场景：setup() 或 created() 中
const initPage = async () => {
    try {
        // await: "停在这里！等 fetchUserData 有结果了再往下走！"
        const response = await fetchUserData(); 
        console.log("✅ 请求成功:", response.data);
        
        // 拿到数据后，这里通常会做: this.list = response.data
    } catch (error) {
        console.log("❌ 请求失败:", error);
    }
};

// 执行异步函数
initPage();

/* ==========================================================
   第七部分：三元运算符与短路逻辑
   Vue 场景：v-if / v-show 的 js 替代版，动态 class
   ========================================================== */

const isActive = true;

// 1. 三元运算符 (Condition ? True : False)
// Vue 模板中：:class="{ active: isActive }" 本质就是这个
const statusClass = isActive ? "class-active" : "class-inactive";

// 2. 短路逻辑 (&& ||)
// React/Vue 中常见的条件渲染
const userLoggedIn = true;
// 如果 userLoggedIn 为真，就显示后面的名字；否则什么都不显示
const showName = userLoggedIn && "欢迎回来，用户！"; 

// 默认值处理 (|| 或 ??)
// 如果 inputVal 为空/null，就用 "默认值"
const inputVal = null;
const finalVal = inputVal || "默认值";

/* ==========================================================
   第八部分：事件处理 (Event Handling) —— Vue @click 的底层
   Vue 场景：methods 中定义的所有函数，本质就是事件回调
   ========================================================== */

// 模拟一个按钮点击事件
const handleLogin = (event) => {
    // event 是浏览器自动传进来的事件对象
    console.log("按钮被点击了！", event.type); // 输出: click
    
    // 常见事件属性
    console.log("点击位置:", event.clientX, event.clientY);
    
    // 阻止默认行为（比如表单提交刷新页面）
    event.preventDefault();
};

// 模拟调用（真实场景是绑定到 DOM）
console.log("【模拟】登录按钮被点击");
handleLogin({ type: 'click', clientX: 150, clientY: 300, preventDefault: () => {} });

// 带参数的事件函数（Vue 中 @click="addToCart(item.id)"）
const addToCart = (productId, quantity = 1) => {
    console.log(`添加商品 ${productId} 到购物车，数量: ${quantity}`);
};
addToCart(101, 3); // 添加商品 101 到购物车，数量: 3

/* ==========================================================
   第九部分：表单事件与双向绑定模拟
   Vue 场景：v-model 的底层原理（input 事件 + value 更新）
   ========================================================== */

let formData = {
    username: '',
    password: '',
    remember: false
};

// 模拟输入框变化
const handleInputChange = (event) => {
    const { name, value, type, checked } = event.target;
    
    // 根据输入类型更新对应字段
    if (type === 'checkbox') {
        formData[name] = checked;
    } else {
        formData[name] = value;
    }
    
    console.log("当前表单数据:", formData);
};

// 模拟用户输入
handleInputChange({ target: { name: 'username', value: 'zhangshan' } });
handleInputChange({ target: { name: 'password', value: '123456' } });
handleInputChange({ target: { name: 'remember', type: 'checkbox', checked: true } });

/* ==========================================================
   第十部分：条件与循环（JS 原生写法）—— 对应 Vue 的 v-if / v-for
   ========================================================== */

const courses = [
    { id: 1, name: "Vue3 入门", price: 0, isFree: true },
    { id: 2, name: "React 进阶", price: 999, isFree: false },
    { id: 3, name: "TypeScript", price: 0, isFree: true }
];

// 1. 条件判断 (if / 三元)
courses.forEach(course => {
    const displayPrice = course.isFree 
        ? "免费" 
        : `￥${course.price}`;
    
    console.log(`${course.name} - 价格: ${displayPrice}`);
});

// 2. 循环遍历 (forEach / for...of)
// Vue 的 v-for 本质上就是这些
console.log("=== 课程列表 ===");
for (const course of courses) {
    if (course.isFree) {
        console.log(`🎁 免费课程: ${course.name}`);
    }
}

/* ==========================================================
   第十一部分：DOM 操作基础（理解 Vue 为什么能替代它）
   虽然 Vue 不推荐直接操作 DOM，但理解它能让你知道 Vue 有多香
   ========================================================== */

// 假设页面上有这个元素（真实项目中你不会这么写，但要知道原理）
const mockElement = {
    textContent: '',
    classList: {
        add: (cls) => console.log(`添加类: ${cls}`),
        remove: (cls) => console.log(`移除类: ${cls}`),
        toggle: (cls) => console.log(`切换类: ${cls}`)
    },
    style: {}
};

// 修改文本
mockElement.textContent = "登录成功！";
console.log("DOM文本更新:", mockElement.textContent);

// 操作类名（Vue 中用 :class 替代）
mockElement.classList.add("success");
mockElement.classList.toggle("active");

// 修改样式（Vue 中用 :style 替代）
mockElement.style.color = "green";
mockElement.style.display = "block";

/* ==========================================================
   第十二部分：模块化（import / export）—— Vue 单文件组件的核心
   Vue 项目里到处都是 import
   ========================================================== */

// 假设这是 utils.js 文件的内容
// export const formatPrice = (price) => price === 0 ? '免费' : `￥${price}`;
// export const API_BASE = 'https://api.example.com';

// 假设这是当前文件（main.js）
const formatPrice = (price) => price === 0 ? '免费' : `￥${price}`;
const API_BASE = 'https://api.example.com';

// 使用
courses.forEach(course => {
    console.log(`课程: ${course.name}, 价格: ${formatPrice(course.price)}`);
});

// 默认导出和导入（Vue 组件常用）
const MyComponent = {
    data() { return { msg: 'Hello Vue' }; },
    methods: { sayHi() { console.log(this.msg); } }
};

// export default MyComponent;

/* ==========================================================
   最终总结：Vue 开发中你真正每天都在用的 JS 知识全家桶
   ========================================================== */

console.log(`
🎯 学完这两份 Demo，你已经掌握了 Vue 所需的核心 JS：

1. 变量声明：const / let
2. 箭头函数 + 模板字符串
3. 解构赋值（props、ref 必备）
4. 展开运算符（状态更新必备）
5. 数组方法：map / filter / reduce / find
6. 异步：async / await + Promise
7. 事件处理：@click、@input 等底层
8. 条件与循环（v-if / v-for 的 JS 版）
9. 模块化 import/export（项目结构基础）

这些就是你在写 Vue 组件时，99% 时间都在打交道的 JS 语法。

剩下的（比如 class、原型、this 绑定、闭包等）虽然有用，但不是每天必写，遇到再深入就行。

现在你可以放心去学 Vue 了！当你看到：
@click="handleClick"
v-for="item in filteredList"
const { count, increment } = store()

你都会立刻明白它背后在干什么。
`);