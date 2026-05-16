import { DatePipe, DecimalPipe } from '@angular/common';
import { Component, input } from '@angular/core';
import { TableColumn } from '@shared/models/table-column.model';
import { PricePipe } from '@shared/pipes/price-pipe';

@Component({
  selector: 'app-table',
  imports: [
    DatePipe,
    DecimalPipe,
    PricePipe
  ],
  templateUrl: './table.html',
  styleUrl: './table.css',
})
export class Table {
  columns = input.required<TableColumn[]>();
  data = input.required<any[]>();
  trackByKey = input<string>('id');
  caption = input<string>();
  noEntriesMsg = input<string>();




}