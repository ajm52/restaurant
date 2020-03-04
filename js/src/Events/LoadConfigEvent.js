//Configuration load event. As of now, should only occur once at start of simulation.

const LoadConfigEventType = {
  configLoad: "CONFIG-LOAD"
};

const LoadConfigEventCreator = {
  configData: jsonData => ({
    type: LoadConfigEventType.configLoad,
    jsonData
  })
};

export { LoadConfigEventCreator, LoadConfigEventType };
