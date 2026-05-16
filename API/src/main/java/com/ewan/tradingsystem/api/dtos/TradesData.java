package com.ewan.tradingsystem.api.dtos;
import java.util.List;

import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
public class TradesData {
    private List<TradeDto> trades;
}
