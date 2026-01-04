<template>
  <!-- 这是组件的模板部分，用来定义 HTML 结构 -->
  <div class="components1">
    <!-- 显示组件的标题 -->
    <h2>{{ title }}</h2>

    <!-- v-bind 简写 : 绑定属性，比如动态设置 class -->
    <p :class="{ highlight: isHighlight }">这是一个子组件的段落</p>

    <!-- v-on 简写 @ 绑定事件，点击按钮时调用 addCount 方法 -->
    <button @click="addCount">点击次数：{{ count }}</button>

    <!-- v-if / v-else 条件渲染 -->
    <div v-if="count >= 5">
      哇！你已经点击了 {{ count }} 次，好厉害！
    </div>
    <div v-else>
      继续点击吧，还差一点就到 5 次了～
    </div>

    <!-- v-for 列表渲染，从 items 数组中循环生成 li -->
    <ul>
      <li v-for="(item, index) in items" :key="index">
        {{ index + 1 }}. {{ item }}
      </li>
    </ul>

    <!-- 双向绑定 v-model，用于输入框 -->
    <input v-model="inputText" placeholder="在这里输入内容" />
    <p>你输入的内容是：{{ inputText }}</p>
  </div>
</template>

<script setup>
// Vue 3 的 <script setup> 语法糖，无需显式 export default
import { ref, computed, onMounted } from 'vue'

// ------------------- 响应式数据（ref） -------------------
// ref 用于包装基本类型的值，使其变得响应式
const count = ref(0)          // 点击次数，初始值为 0
const inputText = ref('')     // 输入框的内容，初始为空字符串
const isHighlight = ref(true) // 是否高亮段落

// ------------------- 计算属性（computed） -------------------
const title = computed(() => {
  // 计算属性会根据依赖自动更新
  return `子组件 - 当前计数：${count.value}`
})

// ------------------- 普通数组（ref） -------------------
const items = ref(['苹果', '香蕉', '橙子'])

// ------------------- 方法 -------------------
function addCount() {
  count.value++               // 修改响应式数据需要 .value
  // 当计数达到 10 次时，取消高亮
  if (count.value >= 10) {
    isHighlight.value = false
  }
}

// ------------------- 生命周期钩子 -------------------
// onMounted 在组件挂载到 DOM 后执行
onMounted(() => {
  console.log('Components1 组件已经挂载完成！')
})
</script>

<style scoped>
/* scoped 表示样式只作用于当前组件，不会污染全局 */
.components1 {
  padding: 20px;
  border: 2px solid #42b983;
  border-radius: 8px;
  background-color: #f9f9f9;
  margin-top: 20px;
}

h2 {
  color: #42b983;
}

.highlight {
  /* 当 isHighlight 为 true 时应用此样式 */
  background-color: yellow;
  font-weight: bold;
}

button {
  padding: 8px 16px;
  background-color: #42b983;
  color: white;
  border: none;
  border-radius: 4px;
  cursor: pointer;
}

button:hover {
  background-color: #369b73;
}
</style>