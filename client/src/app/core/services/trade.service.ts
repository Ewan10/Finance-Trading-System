import { HttpClient } from '@angular/common/http';
import { inject, Injectable, signal } from '@angular/core';
import { environment } from '@env/environment.development';
import { Trade } from '@shared/models/trade.model';
import { TradesResponse } from '@shared/models/tradesResponse.model';

@Injectable({
  providedIn: 'root',
})
export class TradeService {
  private http = inject(HttpClient);
  private apiUrl = environment.apiUrl;
  private _trades = signal<Trade[]>([]);
  trades = this._trades.asReadonly();
  setTrades = (trades: Trade[]) => this._trades.set(trades);

  getTrades() {
    return this.http.get<TradesResponse>(`${this.apiUrl}/trades`);
  }
}
