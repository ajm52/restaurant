import React from "react";

/**
 * This class is responsible for updating
 * application state information according
 * to incoming messages. The updated info
 * is reflected accordingly in the UI.
 */

class MessageHandler extends React.Component {
  constructor(props) {
    super(props);

    this.state = {
      name: "handler"
    };
  }

  render() {
    return <div id={this.state.name}></div>;
  }
}

export default MessageHandler;
