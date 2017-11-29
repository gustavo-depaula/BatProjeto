const http = require('http')
const url = require('url')
const firebase = require('firebase')
const express = require('express')

// firebase config
const firebase_config = {
  apiKey: "AIzaSyAic_B1hGwKBeJ_MNp-AHwHAzh_FJll7fQ",
  authDomain: "batprojeto.firebaseapp.com",
  databaseURL: "https://batprojeto.firebaseio.com",
  projectId: "batprojeto",
  storageBucket: "",
  messagingSenderId: "666801053286"
}
firebase.initializeApp(firebase_config)
const database = firebase.database()

// express config
const app = express()
const server_port = 3000

// express functions
function passed_checkpoint (checkpoint_id, date) {
  console.log(`checkpoint ${checkpoint_id}, às ${date}`)
  let new_record_key = database.ref().child('records').push().key
  let update = {}
  update['/records/' + new_record_key] = Object.assign({}, {id: checkpoint_id}, {date: date})
  database.ref().update(update) 
}

// express routes
app.get('/checkpoint/:checkpointId', (req, res) => {
  passed_checkpoint(req.params.checkpointId, new Date())
  res.send(new Date())
})

// express start
app.listen(server_port, () => console.log(`O servidor está rodando na porta ${server_port}`))