const MessageEventCreator = {
  newMsg: (msgType, content) => ({
    type: msgType,
    content: content
  })
};

export default MessageEventCreator;
