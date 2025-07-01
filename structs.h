#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>
using namespace std;

struct Marca {
    int codigo_marca;
    string nombre_marca;
};

struct Producto {
    int codigo_producto;
    string nombre_producto;
    float precio_venta;
    float precio_compra;
    int stock;
    int codigo_marca;
};

struct FormaPago {
    string codigo_forma_pago;
    string nombre_forma_pago;
    int porcentaje_descuento;
};

struct RecaudacionProducto {
    int codigo_producto;
    string nombre_producto;
    float total_recaudado = 0;
    int cantidad_vendida = 0;
    int stock_remanente = 0;
};

// Estructura para el Reporte 3 (alternativa a la matriz)
struct VentaMarcaFormaPago {
    int codigo_marca;
    string codigo_forma_pago;
    int cantidad_vendida = 0;
};

// Estructura para el Reporte 5
struct CompraCliente {
    int codigo_cliente = 0;
    int cantidad_compras = 0;
};

#endif // STRUCTS_H
