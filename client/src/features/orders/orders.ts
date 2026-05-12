import { Component } from '@angular/core';
import { OrderEntry } from './order-entry/order-entry';
import { OrdersTable } from './orders-table/orders-table';

@Component({
  selector: 'app-orders',
  standalone: true,
  imports: [
    OrderEntry,
    OrdersTable,
  ],
  templateUrl: './orders.html',
  styleUrl: './orders.css',
})
export class Orders {

}
