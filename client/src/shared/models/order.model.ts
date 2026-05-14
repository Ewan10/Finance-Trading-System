export interface Order {
    orderId: number;

    clientId: number;
    
    price: number;
    
    quantity: number;

    side: 'BUY' | 'SELL';
    
    status: string;

    timestamp: string;
}
