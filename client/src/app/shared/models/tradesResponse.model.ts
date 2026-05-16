import { Trade } from "./trade.model";

export interface TradesResponse {
  data: {
    trades: Trade[];
  };
}