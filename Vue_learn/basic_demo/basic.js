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