import './assets/main.css'

import { createApp } from 'vue'
import App from './App.vue'

// 关键：引入 ArcoVue
import ArcoVue from '@arco-design/web-vue'
// 关键：引入样式（没有这个所有组件都没样子！）
import '@arco-design/web-vue/dist/arco.css'

const app = createApp(App)
app.use(ArcoVue)        // ← 就是加这一句！
app.mount('#app')
