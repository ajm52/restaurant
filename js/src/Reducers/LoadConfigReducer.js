import { LoadConfigEventType } from "../Events/LoadConfigEvent";

//Load configuration reducer for sim configuration actions.
export default function LoadConfigReducer(state = {}, event) {
  switch (event.type) {
    case LoadConfigEventType.configLoad:
      return {
        ...state,
        ...event.jsonData
      };
    default:
      return state;
  }
}
