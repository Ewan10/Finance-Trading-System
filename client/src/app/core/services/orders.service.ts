import { HttpClient } from '@angular/common/http';
import { inject, Injectable, signal } from '@angular/core';
import { Order } from '../../shared/models/order.model';
import { environment } from '../../../environments/environment.development';

@Injectable({
  providedIn: 'root',
})
export class OrdersService {
  private http = inject(HttpClient);
  private apiUrl = environment.apiUrl;
  private _orders = signal<Order[]>([]);
  orders = this._orders.asReadonly();
  
  addOrder = (order: Order) => this._orders.update(list => [order, ...list]);

  submitOrder(order: any) {
    return this.http.post<Order>(`${this.apiUrl}api/orders`, order);
  }

}
