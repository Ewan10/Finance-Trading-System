package com.ewan.tradingsystem.api.dtos;

import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
public class TradesResponse {
    private String status;
    private TradesData data;
}
