import { Component, inject } from '@angular/core';
import { Order } from '../../../shared/models/order.model';
import { DatePipe, DecimalPipe } from '@angular/common';
import { OrdersService } from '../../../core/services/orders.service';
import { PricePipe } from '../../../shared/pipes/price-pipe';

@Component({
  selector: 'app-orders-table',
  standalone: true,
  imports: [
    DatePipe,
    PricePipe,
    DecimalPipe
  ],
  templateUrl: './orders-table.html',
  styleUrl: './orders-table.css',
})
export class OrdersTable {
  ordersService = inject(OrdersService);
  orders = this.ordersService.orders;

}
