import { Routes } from '@angular/router';
import { MainLayout } from './features/main-layout/main-layout';
import { Orders } from './features/orders/orders';
import { Trades } from '@features/trades/trades';

export const routes: Routes = [
     {
    path: '',
    component: MainLayout,
    children: [
      {
        path: 'orders',
        component: Orders
      },
      {
        path: 'trades',
        component: Trades
      }
    ]
  }

];
