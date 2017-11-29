import React, { Component } from 'react'
import firebase from 'firebase'

var config = {
  apiKey: "AIzaSyAic_B1hGwKBeJ_MNp-AHwHAzh_FJll7fQ",
  authDomain: "batprojeto.firebaseapp.com",
  databaseURL: "https://batprojeto.firebaseio.com",
  projectId: "batprojeto",
  storageBucket: "batprojeto.appspot.com",
  messagingSenderId: "666801053286"
}
firebase.initializeApp(config)

export default class App extends Component {
  constructor (props) {
    super(props)
    this.state = {
      records: []
    }
  }

  componentWillMount () {
    this.firebaseRef = firebase.database().ref('records')
    this.firebaseRef.on('child_added', (dataSnapshot) => {
      this.setState({
        records: this.records
      })
    })
  }

  render () {
    console.log(this.state.records)
    return (
      <ul>
        {this.state.records.map((item) => <li>item.date</li>)}
      </ul>
    )
  }
}