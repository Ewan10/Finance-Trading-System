package com.ewan.tradingsystem.api.controllers;

import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import com.ewan.tradingsystem.api.dtos.OrderDto;
import com.ewan.tradingsystem.api.dtos.StatusResponse;
import com.ewan.tradingsystem.api.services.OrderService;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.PutMapping;


@RestController
@RequestMapping("api/orders")
public class OrderController {

    private final OrderService orderService;

    public OrderController(OrderService orderService) {
        this.orderService = orderService;
    }

    @PostMapping
    public StatusResponse submit(@RequestBody OrderDto orderDto)
    {
        return orderService.submit(orderDto);
    }

    @DeleteMapping("/{id}")
    public StatusResponse cancel(@PathVariable long id) {
        return orderService.cancel(id);
    }
    
    @PutMapping("/{id}")
    public StatusResponse modifyOrder(@PathVariable long id, @RequestBody OrderDto orderDto) {
        return orderService.modify(id, orderDto);
    }
}