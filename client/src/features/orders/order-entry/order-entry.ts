import { Component, inject } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { Order } from '../../../shared/models/order.model';
import { OrdersService } from '../../../core/services/orders.service';

@Component({
  selector: 'app-order-entry',
  standalone: true,
  imports: [
    FormsModule
  ],
  templateUrl: './order-entry.html',
  styleUrl: './order-entry.css',
})
export class OrderEntry {
  order = {
    clientId: 0,
    price: 0,
    quantity: 0,
    side: '',
  };
  private orderService = inject(OrdersService);

  submitOrder() {
    const payload = {
      ...this.order,
      price: Math.round(this.order.price * 100)
    };
    this.orderService.submitOrder(payload).subscribe({
      next: (response) => {
        this.orderService.addOrder(response);
        console.log('Order submitted successfully:', response);
      },
      error: (error) => {
        console.error('Error submitting order:', error);
      }
    });
  }

}
