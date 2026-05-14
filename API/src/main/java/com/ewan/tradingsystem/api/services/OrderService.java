package com.ewan.tradingsystem.api.services;

import org.springframework.stereotype.Service;
import com.ewan.tradingsystem.api.client.EngineClient;
import com.ewan.tradingsystem.api.dtos.OrderBookResponse;
import com.ewan.tradingsystem.api.dtos.OrderDto;
import com.ewan.tradingsystem.api.dtos.OrderResponse;
import com.ewan.tradingsystem.api.dtos.StatusResponse;

@Service
public class OrderService {
    private final EngineClient engineClient;

    public OrderService(EngineClient engineClient) {
        this.engineClient = engineClient;
    }

    public OrderResponse submit(OrderDto orderDto) {
        return engineClient.submitOrder(orderDto);
    }

    public StatusResponse cancel(long id) {
        return engineClient.cancelOrder(id);
    }

    public StatusResponse modify(long id, OrderDto orderDto) {
        return engineClient.modifyOrder(id, orderDto);
    }

    public OrderBookResponse getOrderBook() {
        return engineClient.getOrderBook();
    }

    public OrderBookResponse getTrades() {
        return engineClient.getTrades();
    }
}