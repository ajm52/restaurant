import React from "react";
import { connect } from "react-redux";
import PropTypes from "prop-types";
import { MessageActionCreator } from "../../Actions/MessageAction";

/**
 * This class is responsible for receiving
 * messages from the backend logic of the
 * simulation.
 */

class MessageReceiver extends React.Component {
  constructor(props) {
    super(props);

    this.state = {
      sock: null,
      port: props.port,
      name: "reception",
      queue: null, //where messages are pushed
      queueInUse: false //ad hoc safety mechanism for queue access
    };
  }

  componentDidMount() {
    this.connect();
  }

  /**
   * Connect function. Handles all that comm-related jazz.
   */
  connect = () => {
    var sock = new WebSocket(`ws://localhost:${this.state.port}/ws`);

    //think about caching "this"
    //might need a connectInterval

    sock.onopen = () => {
      console.log("connected!");

      this.setState({ sock: sock });

      //reset cached timeout
      //clearTimeout on the current connection
    };

    /**
     * Message handler. Simply dump into the message queue.
     */
    sock.onmessage = evt => {
      console.log("message received:", evt);
    };

    sock.onclose = evt => {
      console.log("connection closed.");

      //perhaps include reattempts with timeout
    };

    sock.onerror = err => {
      console.error("Error:", err.message, ". Closing connection . . .");

      sock.close();
    };
  };

  //perhaps include a check function to try and reconnect following disconnection

  render() {
    return <div id={this.state.name}></div>;
  }
}

MessageReceiver.propTypes = {
  //fill these in when all the props are established
};

const mapStateToProps = state => ({
  queue: state && state.service && state.service.queue,
  queueInUse: state && state.service && state.service.queueInUse
});

const mapDispatchToProps = {
  newMsg: MessageActionCreator.newMsg
};

/**
 * may want to connect this to the application state.
 */
export default MessageReceiver;
