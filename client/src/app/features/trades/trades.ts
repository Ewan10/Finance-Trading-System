import { Component, inject, OnInit } from '@angular/core';
import { TradeService } from '@core/services/trade.service';
import { Table } from '@shared/components/table/table';
import { TableColumn } from '@shared/models/table-column.model';

@Component({
  selector: 'app-trades',
  imports: [
    Table
  ],
  templateUrl: './trades.html',
  styleUrl: './trades.css',
})
export class Trades implements OnInit {
  private tradeService = inject(TradeService);
  
  ngOnInit(): void {
    this.tradeService.getTrades().subscribe({
      next: (response) => {
         this.tradeService.setTrades(response.data.trades);
         console.log('Trades fetched successfully:', response.data.trades);
      }
    });
  }
  
  trades = this.tradeService.trades;

  tradesColumns: TableColumn[] = [
    { key: 'tradeId', label: 'Trade Id' },
    { key: 'buyOrderId', label: 'Buy Id' },
    { key: 'sellOrderId', label: 'Sell Id' },
    { key: 'quantity', label: 'Quantity', },
    { key: 'price', label: 'Price', pipe: 'number', format: '1.2-2' },
    { key: 'timestamp', label: 'Time', type: 'time' },
  ];
}
