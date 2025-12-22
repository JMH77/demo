<template>
  <div class="login-container">
    <!-- 标题 -->
    <div class="login-header">
      <h1>船舶工单管理系统</h1>
    </div>

    <!-- 登录表单 -->
    <div class="login-form-wrapper">
      <a-form
        :model="currentFormData"
        :rules="isRegisterMode ? registerRules : rules"
        ref="formRef"
        auto-label-width
        @submit="isRegisterMode ? handleRegister : handleLogin"
      >
        <!-- 用户名输入框 -->
        <a-form-item field="username" label="用户名">
          <a-input
            v-model="username"
            placeholder="请输入用户名"
            size="large"
          >
            <template #prefix>
              <icon-user />
            </template>
          </a-input>
        </a-form-item>

        <!-- 密码输入框 -->
        <a-form-item field="password" label="密码">
          <a-input
            v-model="password"
            type="password"
            placeholder="请输入密码"
            size="large"
          >
            <template #prefix>
              <icon-lock />
            </template>
          </a-input>
        </a-form-item>

        <!-- 注册模式下的额外字段 -->
        <template v-if="isRegisterMode">
          <!-- 邮箱输入框 -->
          <a-form-item field="email" label="邮箱">
            <a-input
              v-model="registerData.email"
              placeholder="请输入邮箱"
              size="large"
            >
            <template #prefix>
              <icon-user />
            </template>
            </a-input>
          </a-form-item>

          <!-- 姓名输入框 -->
          <a-form-item field="name" label="姓名">
            <a-input
              v-model="registerData.name"
              placeholder="请输入姓名"
              size="large"
            >
              <template #prefix>
                <icon-user />
              </template>
            </a-input>
          </a-form-item>

          <!-- 人员类型下拉框 -->
          <a-form-item field="userType" label="人员类型">
            <a-select
              v-model="registerData.userType"
              placeholder="请选择人员类型"
              size="large"
            >
              <a-option value="分配人员">分配人员</a-option>
              <a-option value="执行人员">执行人员</a-option>
              <a-option value="验收人员">验收人员</a-option>
            </a-select>
          </a-form-item>
        </template>

        <!-- 登录和注册按钮 -->
        <div class="form-buttons">
          <a-button
            type="primary"
            size="large"
            html-type="submit"
            :loading="isLoading"
          >
            {{ isRegisterMode ? '注册' : '登录' }}
          </a-button>
          <a-button
            size="large"
            @click="handleRegisterClick"
          >
            {{ isRegisterMode ? '返回登录' : '注册' }}
          </a-button>
        </div>
      </a-form>
    </div>
  </div>
</template>

<script setup>
import { ref, computed } from 'vue'
import { Message } from '@arco-design/web-vue'
import {
  IconUser,
  IconLock,
} from '@arco-design/web-vue/es/icon'

// ==================== 响应式数据 ====================
// 登录表单数据
const formData = ref({
  username: '',
  password: '',
})

// 注册表单数据
const registerData = ref({
  username: '',
  password: '',
  email: '',
  name: '',
  userType: '',
})

// 是否为注册模式
const isRegisterMode = ref(false)

// 加载状态
const isLoading = ref(false)

// 表单引用
const formRef = ref(null)

// 当前表单数据（计算属性，用于表单 model）
const currentFormData = computed(() => {
  return isRegisterMode.value ? registerData.value : formData.value
})

// 用户名计算属性（支持双向绑定）
const username = computed({
  get: () => isRegisterMode.value ? registerData.value.username : formData.value.username,
  set: (val) => {
    if (isRegisterMode.value) {
      registerData.value.username = val
    } else {
      formData.value.username = val
    }
  }
})

// 密码计算属性（支持双向绑定）
const password = computed({
  get: () => isRegisterMode.value ? registerData.value.password : formData.value.password,
  set: (val) => {
    if (isRegisterMode.value) {
      registerData.value.password = val
    } else {
      formData.value.password = val
    }
  }
})

// ==================== 表单验证规则 ====================
const rules = {
  username: [
    {
      required: true,
      message: '用户名不能为空',
    },
    {
      minLength: 3,
      message: '用户名长度不能少于3个字符',
    },
  ],
  password: [
    {
      required: true,
      message: '密码不能为空',
    },
    {
      minLength: 6,
      message: '密码长度不能少于6个字符',
    },
  ],
}

// 注册表单验证规则
const registerRules = {
  username: [
    {
      required: true,
      message: '用户名不能为空',
    },
    {
      minLength: 3,
      message: '用户名长度不能少于3个字符',
    },
  ],
  password: [
    {
      required: true,
      message: '密码不能为空',
    },
    {
      minLength: 6,
      message: '密码长度不能少于6个字符',
    },
  ],
  email: [
    {
      required: true,
      message: '邮箱不能为空',
    },
    {
      type: 'email',
      message: '请输入有效的邮箱地址',
    },
  ],
  name: [
    {
      required: true,
      message: '姓名不能为空',
    },
    {
      minLength: 2,
      message: '姓名长度不能少于2个字符',
    },
  ],
  userType: [
    {
      required: true,
      message: '请选择人员类型',
    },
  ],
}

// ==================== 事件处理 ====================
// 登录处理
const handleLogin = async () => {
//  todos: 进行用户注册
    Message.info('登录功能待实现')
}

// 注册按钮点击处理
const handleRegisterClick = () => {
  isRegisterMode.value = !isRegisterMode.value
  // 切换模式时重置表单
  if (formRef.value) {
    formRef.value.resetFields()
  }
  if (isRegisterMode.value) {
    // 重置注册表单数据
    registerData.value = {
      username: '',
      password: '',
      email: '',
      name: '',
      userType: '',
    }
  } else {
    // 重置登录表单数据
    formData.value = {
      username: '',
      password: '',
    }
  }
}

// 注册处理
const handleRegister = async () => {
  const valid = await formRef.value.validate()
  if (!valid) {
    return
  }
  // todos: 进行用户注册
  Message.info('注册功能待实现')
}
</script>

<style scoped>
/* 登录容器：使用 flexbox 实现中间布局 */
.login-container {
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  width: 100%;
  height: 100vh;
  background-image: url('@/assets/background.jpg');
  background-size: cover;
  background-position: center;
  background-attachment: fixed;
  background-repeat: no-repeat;
  margin: 0;
  padding: 0;
  position: relative;
  overflow: hidden;
}

/* 使用伪元素添加半透明遮罩，控制背景透明度 */
.login-container::before {
  content: '';
  position: absolute;
  top: 0;
  left: 0;
  right: 0;
  bottom: 0;
  background-color: rgba(0, 0, 0, 0.2);
  pointer-events: none;
}

/* 登录标题 */
.login-header {
  margin-bottom: 30px;
  text-align: center;
  color: white;
  position: relative;
  z-index: 1;
  margin-top: -100px;
  user-select: none;
}

.login-header h1 {
  font-size: 48px;
  margin: 0;
  font-weight: bold;
  letter-spacing: 2px;
  text-shadow: 0 2px 10px rgba(0, 100, 200, 0.5), 0 0 20px rgba(100, 200, 255, 0.3);
}


/* 登录表单包装器 */
.login-form-wrapper {
  width: 100%;
  max-width: 380px;
  padding: 50px;
  background: transparent;
  border-radius: 12px;
  position: relative;
  z-index: 1;
  user-select: none;
}

/* 表单内容 */
.form-content {
  width: 100%;
}

/* 表单按钮组 */
.form-buttons {
  display: flex;
  gap: 66px;
  margin-top: 30px;
  justify-content: center;
}

/* Arco 组件的间距调整 */
:deep(.arco-form-item) {
  margin-bottom: 20px;
}

:deep(.arco-form-item:last-child) {
  margin-bottom: 0;
}

/* 表单标签样式 */
:deep(.arco-form-item-label-col) {
  color: white !important;
}

:deep(.arco-form-item-label-col label) {
  color: white !important;
  font-weight: bold !important;
}

:deep(.arco-form-item-label-content label) {
  color: white !important;
  font-weight: bold !important;
}

/* 输入框透明背景效果 */
:deep(.arco-input) {
  background-color: rgba(255, 255, 255, 0.95);
  border: 1px solid rgba(255, 255, 255, 0.8);
  color: #333;
}

:deep(.arco-input::placeholder) {
  color: rgba(0, 0, 0, 0.4);
}

:deep(.arco-input:hover) {
  border-color: rgba(255, 255, 255, 0.95);
}

:deep(.arco-input:focus) {
  background-color: rgba(255, 255, 255, 1);
  border-color: #5b7fff;
}

:deep(.arco-input-prefix) {
  color: rgba(0, 0, 0, 0.4);
}

/* 下拉框样式，与输入框保持一致 */
:deep(.arco-select) {
  background-color: rgba(255, 255, 255, 0.95);
  border: 1px solid rgba(255, 255, 255, 0.8);
  color: #333;
}

:deep(.arco-select:hover) {
  border-color: rgba(255, 255, 255, 0.95);
}

:deep(.arco-select-focused) {
  background-color: rgba(255, 255, 255, 1);
  border-color: #5b7fff;
}

:deep(.arco-select-view-value) {
  color: #333;
}

:deep(.arco-select-view-placeholder) {
  color: rgba(0, 0, 0, 0.4);
}

:deep(.arco-select-view-single) {
  color: #333;
}

/* 按钮焦点样式移除 */
:deep(.arco-btn) {
  outline: none;
}

:deep(.arco-btn:focus) {
  outline: none;
}
</style>