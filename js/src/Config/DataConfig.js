import React from "react";
import PropTypes from "prop-types";
import { connect } from "react-redux";
import { LoadConfigEventCreator } from "../Events/LoadConfigEvent";

/**
 * invisible component that pushes config data to application state upon mounting.
 * @author ajm
 * @created 3/4/20
 * @modified 3/4/20
 */

const configData = require("./config.json");

class DataConfig extends React.Component {
  render() {
    return <div />;
  }
  componentDidMount() {
    this.props.jsonData(configData);
  }
}

const mapDispatchToProps = {
  jsonData: LoadConfigEventCreator.configLoad
};

DataConfig.propTypes = {
  jsonData: PropTypes.func
};

export default connect(null, mapDispatchToProps)(DataConfig);
