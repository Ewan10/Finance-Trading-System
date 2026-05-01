package com.ewan.tradingsystem.api.dtos;

import java.util.List;

public class OrderBookResponse {
    public String status;
    public Data data;

    public static class Data {
        public List<Level> bids;
        public List<Level> asks;
    }

    public static class Level {
        public long price;
        public long quantity;
    }
}
