<template>
  <div>
    <input type="checkbox" id="agree" v-model="agree" />
    <!-- <label for="agree">我同意协议</label> -->
     <label for="agree" v-if="agree == true">我bu同意协议</label>
     <label for="agree" v-else>我同意协议</label>
    <p>是否同意：{{ agree }}（true/false）</p>

    <!-- 多选 checkbox -->
    <input type="checkbox" value="苹果" v-model="fruits" />
    <input type="checkbox" value="香蕉" v-model="fruits" />
    <input type="checkbox" value="橙子" v-model="fruits" />
    <p>选择的水果：{{ fruits }}</p>  <!-- 数组 -->

    <!-- 你也可以加个按钮测试代码修改状态 -->
    <button @click="agree = true">代码强制同意</button>
    <button @click="agree = false">代码强制不同意</button>
  </div>
</template>

<script setup>
import { ref } from 'vue'

const agree = ref(false)  // 默认不同意
const fruits = ref([])    // 存储选中的水果，初始为空数组
</script>