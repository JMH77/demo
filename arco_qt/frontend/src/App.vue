<template>
  <!-- 使用 Login 组件 -->
  <Login />
</template>

<script setup>
// 导入 Login 组件
import Login from './components/Login.vue'
</script>

<style>
/* 移除浏览器默认样式 */
body {
  margin: 0;
  padding: 0;
}

#app {
  width: 100%;
  height: 100%;
}
</style>