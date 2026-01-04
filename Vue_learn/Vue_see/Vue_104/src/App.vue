<template>
  <!-- 根组件的模板 -->
  <div id="app">
    <h1>Vue 3 入门示例 - App 主组件</h1>

    <!-- props 传值：把 message 从父组件传给子组件 -->
    <!-- 这里我们没有在子组件定义 props，所以只是演示语法 -->
    <!-- 如果子组件需要接收，可以在子组件中使用 defineProps -->
    <Components1 />

    <!-- 多个子组件实例 -->
    <!-- <arco_test /> -->
    <!-- <test_v_model /> -->
    <TestButton />

    <!-- 事件监听：子组件可以通过 $emit 发射事件，这里先留着演示 -->
    <!-- <Components1 @some-event="handleEvent" /> -->

    <!-- 父组件自己的响应式数据展示 -->
    <p>父组件的消息：{{ appMessage }}</p>

    <!-- 父组件的输入框 -->
    <input v-model="appMessage" placeholder="修改父组件的消息" />
  </div>
</template>

<script setup>
import { ref, onMounted } from 'vue'
// 导入我们刚才创建的子组件
import Components1 from './components/components1.vue'
import test_v_model from './components/v_model_test.vue'
import TestButton from './components/test_button.vue'
import arco_test from './components/arco_test.vue'

// ------------------- 父组件的响应式数据 -------------------
const appMessage = ref('Hello from App.vue! 这是一条来自父组件的消息')

// ------------------- 生命周期钩子 -------------------
onMounted(() => {
  console.log('App 组件挂载完成！')
})

// 如果子组件发射事件，可以在这里定义处理函数
// function handleEvent(payload) {
//   console.log('收到子组件事件：', payload)
// }
</script>

<style>
/* App.vue 的全局样式（不加 scoped 会影响全局） */
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  text-align: center;
  margin-top: 40px;
  color: #2c3e50;
}

h1 {
  color: #42b983;
}
</style>