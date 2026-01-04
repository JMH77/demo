<template>
  <div class="test-container">
    <h2>前后端通信测试</h2>
    
    <!-- 测试按钮区域 -->
    <div class="button-group">
      <button @click="testGet" :disabled="loading">📥 GET 请求</button>
      <button @click="testPost" :disabled="loading">📤 POST 请求</button>
      <button @click="testWithParams" :disabled="loading">🔍 带参数请求</button>
    </div>

    <!-- 加载状态 -->
    <div v-if="loading" class="loading">
      ⏳ 请求中...
    </div>

    <!-- 响应结果展示 -->
    <div v-if="response" class="response-box">
      <h3>📨 服务器响应:</h3>
      <pre>{{ response }}</pre>
    </div>

    <!-- 错误信息 -->
    <div v-if="error" class="error-box">
      <h3>❌ 错误信息:</h3>
      <pre>{{ error }}</pre>
    </div>

    <!-- 输入框测试 -->
    <div class="input-section">
      <h3>💬 发送自定义消息</h3>
      <input 
        v-model="message" 
        placeholder="输入要发送的消息"
        @keyup.enter="sendMessage"
      />
      <button @click="sendMessage" :disabled="loading">发送</button>
    </div>
  </div>
</template>

<script setup>
import { ref } from 'vue'
import axios from 'axios'

// 后端服务器地址 (根据你的Flask服务端口调整)
const API_BASE_URL = 'http://localhost:5000'

// 响应式数据
const loading = ref(false)
const response = ref(null)
const error = ref(null)
const message = ref('')

// 清空之前的响应
function clearResponse() {
  response.value = null
  error.value = null
}

// 测试 GET 请求
async function testGet() {
  clearResponse()
  loading.value = true
  
  try {
    const res = await axios.get(`${API_BASE_URL}/api/test`)
    response.value = res.data
    console.log('GET 请求成功:', res.data)
  } catch (err) {
    error.value = err.message
    console.error('GET 请求失败:', err)
  } finally {
    loading.value = false
  }
}

// 测试 POST 请求
async function testPost() {
  clearResponse()
  loading.value = true
  
  try {
    const data = {
      name: '测试用户',
      action: 'test_post',
      timestamp: new Date().toISOString()
    }
    const res = await axios.post(`${API_BASE_URL}/api/data`, data)
    response.value = res.data
    console.log('POST 请求成功:', res.data)
  } catch (err) {
    error.value = err.message
    console.error('POST 请求失败:', err)
  } finally {
    loading.value = false
  }
}

// 测试带参数的 GET 请求
async function testWithParams() {
  clearResponse()
  loading.value = true
  
  try {
    const res = await axios.get(`${API_BASE_URL}/api/user`, {
      params: {
        id: 123,
        name: '张三'
      }
    })
    response.value = res.data
    console.log('带参数请求成功:', res.data)
  } catch (err) {
    error.value = err.message
    console.error('带参数请求失败:', err)
  } finally {
    loading.value = false
  }
}

// 发送自定义消息
async function sendMessage() {
  if (!message.value.trim()) {
    error.value = '消息不能为空'
    return
  }
  
  clearResponse()
  loading.value = true
  
  try {
    const res = await axios.post(`${API_BASE_URL}/api/message`, {
      message: message.value
    })
    response.value = res.data
    message.value = '' // 清空输入框
    console.log('消息发送成功:', res.data)
  } catch (err) {
    error.value = err.message
    console.error('消息发送失败:', err)
  } finally {
    loading.value = false
  }
}
</script>

<style scoped>
.test-container {
  max-width: 800px;
  margin: 20px auto;
  padding: 20px;
  border: 2px solid #42b983;
  border-radius: 10px;
  background: #f9f9f9;
}

h2 {
  color: #42b983;
  text-align: center;
}

.button-group {
  display: flex;
  gap: 10px;
  justify-content: center;
  margin: 20px 0;
  flex-wrap: wrap;
}

button {
  padding: 12px 24px;
  font-size: 16px;
  cursor: pointer;
  background: #42b983;
  color: white;
  border: none;
  border-radius: 5px;
  transition: all 0.3s;
}

button:hover:not(:disabled) {
  background: #35a372;
  transform: translateY(-2px);
  box-shadow: 0 4px 8px rgba(0,0,0,0.2);
}

button:disabled {
  background: #ccc;
  cursor: not-allowed;
}

.loading {
  text-align: center;
  font-size: 18px;
  color: #42b983;
  margin: 20px 0;
  animation: pulse 1.5s infinite;
}

@keyframes pulse {
  0%, 100% { opacity: 1; }
  50% { opacity: 0.5; }
}

.response-box,
.error-box {
  margin: 20px 0;
  padding: 15px;
  border-radius: 8px;
  text-align: left;
}

.response-box {
  background: #e8f5e9;
  border: 1px solid #4caf50;
}

.error-box {
  background: #ffebee;
  border: 1px solid #f44336;
}

.response-box h3 {
  color: #2e7d32;
  margin-top: 0;
}

.error-box h3 {
  color: #c62828;
  margin-top: 0;
}

pre {
  background: white;
  padding: 10px;
  border-radius: 5px;
  overflow-x: auto;
  white-space: pre-wrap;
  word-wrap: break-word;
}

.input-section {
  margin-top: 30px;
  padding-top: 20px;
  border-top: 2px dashed #42b983;
}

.input-section h3 {
  color: #42b983;
}

.input-section input {
  width: 60%;
  padding: 10px;
  font-size: 16px;
  border: 2px solid #42b983;
  border-radius: 5px;
  margin-right: 10px;
}

.input-section input:focus {
  outline: none;
  border-color: #35a372;
  box-shadow: 0 0 5px rgba(66, 185, 131, 0.5);
}
</style>
