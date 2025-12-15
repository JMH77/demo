import { createApp } from 'vue'
import './style.css'
import App from './App.vue'

// 1. 引入Arco Design Vue组件库和全局样式
import ArcoVue from '@arco-design/web-vue';
import '@arco-design/web-vue/dist/arco.css'; 

const app = createApp(App);
// 2. 全局注册Arco组件（这样所有Vue文件都能直接用Arco的组件）
app.use(ArcoVue);
app.mount('#app');