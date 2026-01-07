# Node.js Backend Demo

This is a lightweight Node.js counterpoint to the `Flask_learn/backend_demo.py` example. It uses `express` + `cors` to expose the same set of routes so you can quickly compare how the backend is built in each stack.

## Getting started

1. Open a terminal inside this folder: `cd NodeJs`
2. Install dependencies: `npm install`
3. Run the demo server: `npm start`

The server listens on port `5000`, so it can sit beside the Flask demo or be wired to the same front-end.

## Highlights

- `GET /` – health check with a timestamp.
- `GET /api/test` – mimic a Vue fetch call.
- `POST /api/data` – echoes back the JSON payload.
- `GET /api/user` – returns query parameters.
- `POST /api/users` – adds an in-memory user.
- `GET /api/users` – lists users.
- `POST /api/message` – stores a message in memory.
- `GET /api/messages` – returns saved messages.

Because this sample keeps data in-memory, restarting the server resets the lists; the `initData()` helper seeds a few records for easier testing.
