package com.ewan.tradingsystem.api.controllers;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import com.ewan.tradingsystem.api.dtos.OrderBookResponse;
import com.ewan.tradingsystem.api.services.OrderService;

@RestController
@RequestMapping("/api")
public class MarketController {

    private final OrderService service;

    public MarketController(OrderService service) {
        this.service = service;
    }

    @GetMapping("/orderbook")
    public OrderBookResponse getBook() {
        return service.getOrderBook();
    }

    @GetMapping("/trades")
    public OrderBookResponse getTrades() {
        return service.getTrades();
    }
}
