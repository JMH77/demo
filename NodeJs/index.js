const express = require('express');
const cors = require('cors');

const app = express();

const ALLOWED_ORIGINS = ['http://localhost:5173', 'http://127.0.0.1:5173'];

app.use(cors({
  origin: (origin, callback) => {
    if (!origin || ALLOWED_ORIGINS.includes(origin)) {
      callback(null, true);
    } else {
      callback(new Error('Origin not allowed by CORS'));
    }
  }
}));
app.use(express.json());

let nextUserId = 1;
let nextMessageId = 1;
let users = [];
let messages = [];

function initData() {
  users = [
    { id: nextUserId++, name: '张三', age: 25, createdAt: new Date().toISOString() },
    { id: nextUserId++, name: '李四', age: 30, createdAt: new Date().toISOString() },
    { id: nextUserId++, name: '王五', age: 28, createdAt: new Date().toISOString() }
  ];
  messages = [
    { id: nextMessageId++, content: 'Node.js demo message', timestamp: new Date().toISOString() }
  ];
}

function buildResponse(success, message, data = null) {
  return {
    success,
    message,
    timestamp: new Date().toISOString(),
    data
  };
}

app.get('/', (req, res) => {
  res.json({
    status: 'running',
    message: 'Node.js backend demo is online',
    timestamp: new Date().toISOString()
  });
});

app.get('/api/test', (req, res) => {
  res.json(buildResponse(true, 'GET request simulated from Vue', {
    server: 'Node.js',
    method: 'GET',
    name: 'JMH哆哆'
  }));
});

app.post('/api/data', (req, res) => {
  const payload = req.body;
  console.log('📥 Received POST data:', payload);
  res.json(buildResponse(true, 'Payload processed successfully', { receivedData: payload }));
});

app.get('/api/user', (req, res) => {
  const { id, name } = req.query;
  console.log(`📥 Query parameters: id=${id}, name=${name}`);
  res.json(buildResponse(true, 'Query params received', {
    id,
    name,
    queryResult: `Queried user: ${name || 'unknown'} (ID: ${id || 'N/A'})`
  }));
});

app.post('/api/message', (req, res) => {
  const { message } = req.body;
  if (!message || !message.trim()) {
    return res.status(400).json(buildResponse(false, 'Message is required'));
  }

  const newMessage = {
    id: nextMessageId++,
    content: message.trim(),
    timestamp: new Date().toISOString()
  };
  messages.unshift(newMessage);

  res.json(buildResponse(true, 'Message saved successfully', {
    savedMessage: newMessage,
    totalMessages: messages.length
  }));
});

app.get('/api/messages', (req, res) => {
  res.json(buildResponse(true, 'Messages retrieved', {
    data: messages,
    count: messages.length
  }));
});

app.get('/api/users', (req, res) => {
  res.json(buildResponse(true, 'Users retrieved', {
    data: users,
    count: users.length
  }));
});

app.post('/api/users', (req, res) => {
  const { name, age } = req.body;
  if (!name || !name.trim()) {
    return res.status(400).json(buildResponse(false, 'User name is required'));
  }

  const newUser = {
    id: nextUserId++,
    name: name.trim(),
    age: Number.isInteger(age) ? age : 0,
    createdAt: new Date().toISOString()
  };
  users.push(newUser);

  res.status(201).json(buildResponse(true, 'User created', newUser));
});

app.use((req, res) => {
  res.status(404).json(buildResponse(false, 'Endpoint not found', { path: req.path }));
});

const PORT = 5000;
initData();

app.listen(PORT, () => {
  console.log('='.repeat(60));
  console.log('🚀 Node.js backend demo running');
  console.log('📡 Listening on http://localhost:' + PORT);
  console.log('🧰 Endpoints: /api/test, /api/data, /api/user, /api/message, /api/messages, /api/users');
  console.log('='.repeat(60));
});
