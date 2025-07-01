#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "structs.h" // Asumido necesario

bool cargarMarcas(Marca marcas[], int tam);
void listarMarcas(Marca marcas[], int tam);

bool cargarProductos(Producto productos[], int tam, Marca marcas[], int tam_m);
bool validarCodigoConsecutivo(int arr_codigos, int tam_arr_codigo, int cod);
void listarProductos(Producto productos[], int tam);

bool cargarFormasPago(FormaPago formas_pago[], int tam);
bool validarCodigoFormaPago(string codigo);
bool validarCodigoFormaPagoRepetido(FormaPago formas_pago[], int tam, string codigo_forma_pago);
void listarFormasPago(FormaPago formas_pago[], int tam);

bool cargarLoteVentas(
    Producto productos[], int tam_productos,
    FormaPago formas_pago[], int tam_formas_pago,
    RecaudacionProducto rec[], int tam_recaudacion,
    int ventas_por_fp[],
    int arr_cant_vendida[],
    VentaMarcaFormaPago arr_ventas_marca_fp[], int &cant_combinaciones,
    CompraCliente arr_compras_cliente[], int tam_clientes,
    int &total_ventas
);

int buscarIndiceFormaPago(FormaPago formas_pago[], int tam, string codigo);
bool buscarCodigoProducto(Producto productos[], int tam_productos, int codigo_producto);

void procesarProductosSinVentas(Producto productos[], int tam_productos, int codigo_producto_actual, int cantidad_vendida, int arr_cant_vendida[]);
void listarProductosSinVentas(Producto productos[], int tam_productos, int arr_cant_vendida[]);
string transformarMayusculaFormasDePago(string& codigo);

void inicializarRecaudaciones(RecaudacionProducto rec[], Producto prod[], int tam);
void actualizarRecaudacion(RecaudacionProducto rec[], Producto prod[], int tam, int codigo, int cantidad);
void listarRecaudacionPorProducto(RecaudacionProducto rec[], int tam);


int listarReportes();
void listarPorcentajePorFormaPago(FormaPago formas_pago[], int tam_fp, int ventas_por_fp[], int total_ventas);
int buscarCodigoMarcaPorProducto(int cod_prod, Producto productos[], int tam);
void listarVentasPorMarcaYFP(VentaMarcaFormaPago arr_ventas_marca_fp[], int cant_combinaciones, Marca marcas[], int tam_marcas, FormaPago formas_pago[], int tam_fp);


//reporte 5
void listarTopClientesYSorteo(CompraCliente arr_compras_cliente[], int tam_clientes);

#endif // FUNCIONES_H
