import React, { Component } from 'react'
import 'bulma/css/bulma.css'
import TimelineItem from './components/timeline-item.js'
import * as firebase from "firebase";

// Initialize Firebase
var config = {
  apiKey: "AIzaSyAic_B1hGwKBeJ_MNp-AHwHAzh_FJll7fQ",
  authDomain: "batprojeto.firebaseapp.com",
  databaseURL: "https://batprojeto.firebaseio.com",
  projectId: "batprojeto",
  storageBucket: "batprojeto.appspot.com",
  messagingSenderId: "666801053286"
}
firebase.initializeApp(config)


class App extends Component {
  constructor (props) {
    super(props)
    this.state = {
      records: []
    }
    var recordsRef = firebase.database().ref('records/')
    recordsRef.on('child_added', (data) => {
      recordsRef.once('value').then((snapshot) => {
        this.setState({records: snapshot.val()})
      })
    })

  }

  componentWillMount () {
    firebase.database().ref('records/').once('value').then((snapshot) => {
      this.setState({records: snapshot.val()})
    })
  }


  render() {
    let parseDate = (date) => {
      let dateString = date.toString()
      console.log(dateString.split('T'))
      let day = dateString.split('T')[0].split('-').reverse().join('/')
      let hour = dateString.split('T')[1].split('.')[0]
      return { day, hour }
    }
    let records = Object.keys(this.state.records).map(key => this.state.records[key]).reverse()
    console.log(records)
    return (
      <div>
        <section class="hero is-dark">
          <div class="hero-body">
            <div class="container">
              <h1 class="title">
                BatProjeto
              </h1>
              <h2 class="subtitle">
                FrontEnd
              </h2>
            </div>
          </div>
        </section>
        <div className="bd-snippet-preview">
          <div className="container is-fluid">
            <div className="timeline">
              {
                records.map(
                  (record, key) => {
                    if ( key === 0 ) {
                      return (
                        <div key={key}>
                          <header className="timeline-header">
                            <span className="tag is-primary">{parseDate(record.date).day}</span>
                          </header>
                          <TimelineItem key={key} date={parseDate(record.date).hour} checkpoint={record.id}/>
                        </div>
                      )
                    } else if (parseDate(records[key].date).day === parseDate(records[key-1].date).day) {
                      return <TimelineItem key={key} date={parseDate(record.date).hour} checkpoint={record.id}/>
                    } else {
                      return (
                        <div key={key}>
                          <header className="timeline-header">
                            <span className="tag is-primary">{parseDate(record.date).day}</span>
                          </header>
                          <TimelineItem key={key} date={parseDate(record.date).hour} checkpoint={record.id}/>
                        </div>
                      )
                    }
                  }
                )
              }
            </div>
            <div class="timeline-header">
              <span class="tag is-medium is-info">The end.</span>
            </div>
          </div>
        </div>
      </div>
    )
  }
}

export default App;
