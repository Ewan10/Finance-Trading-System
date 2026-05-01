package com.ewan.tradingsystem.api.client;

import org.springframework.stereotype.Component;
import org.springframework.web.client.RestTemplate;
import static org.springframework.http.HttpMethod.PUT;

import org.springframework.http.HttpEntity;

import static org.springframework.http.HttpMethod.DELETE;

import com.ewan.tradingsystem.api.dtos.OrderBookResponse;
import com.ewan.tradingsystem.api.dtos.OrderDto;
import com.ewan.tradingsystem.api.dtos.StatusResponse;

@Component
public class EngineClient {

    private final RestTemplate restTemplate;
    private static final String URL = "http://localhost:8081";

    public EngineClient(RestTemplate restTemplate) {
        this.restTemplate = restTemplate;
    }

    public StatusResponse submitOrder(OrderDto orderDto) {
        return restTemplate.postForObject(
                URL + "/orders", orderDto, StatusResponse.class);
    }

    public StatusResponse cancelOrder(long id) {
        return restTemplate.exchange(
                URL + "/orders/" + id,
                DELETE,
                null,
                StatusResponse.class).getBody();
    }

    public StatusResponse modifyOrder(long id, OrderDto orderDto) {
        return restTemplate.exchange(
                URL + "/orders/" + id,
                PUT,
                new HttpEntity<>(orderDto),
                StatusResponse.class).getBody();
    }

    public OrderBookResponse getOrderBook() {
        return restTemplate.getForObject(
                URL + "/orderbook",
                OrderBookResponse.class);
    }

    public OrderBookResponse getTrades() {
        return restTemplate.getForObject(
                URL + "/trades",
                OrderBookResponse.class);
    }
}