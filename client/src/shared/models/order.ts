export interface Order {
    orderId: number;

    clientId: number;

    side: 'BUY' | 'SELL';

    quantity: number;

    price: number;

    status: string;

    timestamp: string;
}
