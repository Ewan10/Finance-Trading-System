import { Component, inject } from '@angular/core';
import { OrderEntry } from './order-entry/order-entry';
import { OrdersTable } from './orders-table/orders-table';
import { TableColumn } from '@shared/models/table-column.model';
import { Table } from '@shared/components/table/table';
import { OrdersService } from '@core/services/orders.service';

@Component({
  selector: 'app-orders',
  standalone: true,
  imports: [
    OrderEntry,

    Table
  ],
  templateUrl: './orders.html',
  styleUrl: './orders.css',
})
export class Orders {
  ordersService = inject(OrdersService);
  orders = this.ordersService.orders;
  
    orderColumns: TableColumn[] = [
    { key: 'orderId', label: 'Id' },
    { key: 'side', label: 'Side' },
    { key: 'quantity', label: 'Quantity', },
    { key: 'price', label: 'Price', pipe: 'number', format: '1.2-2' },
    { key: 'status', label: 'Status' },
    { key: 'timestamp', label: 'Time', type: 'time' },
  ];
  
}
