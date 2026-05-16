package com.ewan.tradingsystem.api.dtos;
import lombok.Getter;
import lombok.Setter;
import lombok.NoArgsConstructor;

@Getter
@Setter
@NoArgsConstructor
public class TradeDto {
    private long tradeId;
    private long buyOrderId;
    private long sellOrderId;
    private long price;
    private long quantity;
    private long timestamp;
}
