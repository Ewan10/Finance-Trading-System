export interface Trade {
    tradeId: number;
    buyOrderId: number;
    sellOrderId: number;
    price: number;
    quantity: number;
    timestamp: string;
}
