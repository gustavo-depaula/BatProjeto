import React, { Component } from 'react'

class TimelineItem extends Component {
	render () {
    return (
      <div className="timeline-item">
        <div className="timeline-marker"></div>
        <div className="timeline-content">
          <p className="heading">{this.props.date}</p>
          <p>Checkpoint {this.props.checkpoint}</p>
        </div>
      </div>
    )
  }
}

export default TimelineItem