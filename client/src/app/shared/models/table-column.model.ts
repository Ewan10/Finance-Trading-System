export interface TableColumn {
    key: string;
    label: string;

    type?: 'text' | 'time' | 'number';
    pipe?: 'number' | 'date';
    format?: string;
}
