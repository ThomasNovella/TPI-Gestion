#include <iostream>
#include "structs.h"
#include "funciones.h"


int main()
{
    //MENU
    bool salir = false;
    int opcion, opcionReporte;
    //Son 10 marcas
    bool marcas_cargadas = false;
    const int tam_marcas = 10;
    Marca arr_marcas[tam_marcas]{};
    //Son 20 productos
    bool productos_cargados = false;
    const int tam_productos = 20;
    Producto arr_productos[tam_productos]{};
    //Son 5 formas de pago
    const int tam_formas_pago = 5;
    bool formas_pago_cargadas = false;
    FormaPago arr_formas_pago[tam_formas_pago]{};
    //Ventas
    RecaudacionProducto arr_recaudacion[tam_productos]{};
    // LOTE DE VENTAS - ACUMULADORES PARA REPORTES
    bool lote_ventas_cargado = false;

    // NUEVOS ARRAYS PARA REPORTES
    // Reporte 2: Porcentaje por forma de pago
    int ventas_por_forma_pago[tam_formas_pago]{}; // Un contador para cada forma de pago

    int arr_cantidad_vendida_por_producto[tam_productos]{};
    // Reporte 3: Ventas por marca y forma de pago (la alternativa a la matriz)
    // Explicación: Crearemos una estructura para esto en structs.h
    const int tam_reporte3 = tam_marcas * tam_formas_pago; // Máximo 50 combinaciones (10 marcas * 5 f.pago)
    VentaMarcaFormaPago arr_ventas_marca_fp[tam_reporte3]{};
    int cant_combinaciones_reales = 0; // Para saber cuántas combinaciones usamos realmente
    int total_ventas_realizadas = 0;
    // Reporte 5: Top 10 Clientes
    const int tam_clientes = 50;
    CompraCliente arr_compras_cliente[tam_clientes]{}; // Un contador para cada cliente
    for(int i=0; i < tam_clientes; i++){
        arr_compras_cliente[i].codigo_cliente = i + 1;
    }

    while(salir == false){

        cout << "1. Cargar Marcas" << endl;
        cout << "2. Cargar Productos" <<  endl;
        cout << "3. Cargar Formas de Pago" << endl;
        cout << "4. Cargar Lote de Ventas" << endl;
//        cout << "5. List ar Marcas" << endl;
//        cout << "6. Listar Productos" << endl;
//        cout << "7. Listar formas de pago" << endl;
//        cout << "8. Recaudacion por producto" << endl;
        cout << "5. Reportes" << endl;

        cout << "0. Salir del menu" << endl << endl;

        cout << "Ingrese opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                system("cls");

                if(cargarMarcas(arr_marcas, tam_marcas) == true){
                    cout << "Marcas cargadas exitosamente";
                    cout << endl << endl;
                    marcas_cargadas = true;
                    system("pause");
                    system("cls");
                }
                break;
            case 2:
                system("cls");
                if(marcas_cargadas == true){
                    productos_cargados = cargarProductos(arr_productos, tam_productos, arr_marcas, tam_marcas);
                    if(productos_cargados == true){
                        cout << "Productos cargados exitosamente";
                        inicializarRecaudaciones(arr_recaudacion, arr_productos, tam_productos);
                        cout << endl;
                        system("pause");
                        system("cls");
                        cout << endl;
                    }
                }
                else{
                    cout << "Debe cargar primero las marcas" << endl << endl;
                    system("pause");
                    system("cls");
                }
                break;
            case 3:
                system("cls");
                if(marcas_cargadas == true && productos_cargados == true){

                    cout << "ingrese un codigo 'EF', 'MP', 'TR', 'TC' o 'CT'" << endl << endl;
                    formas_pago_cargadas = cargarFormasPago(arr_formas_pago, tam_formas_pago);
                    system("cls");

                    if(formas_pago_cargadas == true){
                        cout << "Formas de pago cargadas exitosamente";
                        cout << endl << endl;
                        system("pause");
                        system("cls");
                    }
                }
                else{

                    cout << "Debe cargar primero las marcas y/o productos";
                    cout << endl << endl;
                    system("pause");
                    system("cls");
                }
                break;
            case 4:
                //Validar que todo este cargado anteriormente
                if(marcas_cargadas == true && productos_cargados == true && formas_pago_cargadas == true){
                    system("cls");
                    lote_ventas_cargado = cargarLoteVentas(
                        arr_productos, tam_productos,
                        arr_formas_pago, tam_formas_pago,
                        arr_recaudacion, tam_productos,
                        ventas_por_forma_pago,
                        arr_cantidad_vendida_por_producto, // Parámetro para Reporte de Productos sin Ventas
                        arr_ventas_marca_fp, cant_combinaciones_reales, // Parámetros para Reporte 3
                        arr_compras_cliente, tam_clientes, // Parámetros para Reporte 5
                        total_ventas_realizadas // Parámetro para el total
                    );
                    if(lote_ventas_cargado == true){

                        cout << "Lote cargado exitosamente";
                        cout << endl;
                        system("pause");
                        system("cls");
                    }
                }
                else{

                    cout << "Debe cargar lote 1, 2 y 3 para cargar Lote de ventas";
                    cout << endl << endl;
                    system("pause");
                    system("cls");
                }
                break;
                case 5: // Menú de Reportes
                    if (!marcas_cargadas || !productos_cargados || !formas_pago_cargadas) {
                    cout << "Debe cargar Marcas, Productos y Formas de Pago antes de ver reportes." << endl;
                    system("pause");
                    system("cls");
                    break;
                    }

                    opcionReporte = listarReportes();
                    while (opcionReporte != 0) {
                        switch (opcionReporte) {
                            case 1:
                                system("cls");
                                listarMarcas(arr_marcas, tam_marcas);
                                cout << endl;
                                break;
                            case 2:
                                system("cls");
                                listarProductos(arr_productos, tam_productos);
                                cout << endl;

                                break;
                            case 3:
                                system("cls");
                                listarFormasPago(arr_formas_pago, tam_formas_pago);
                                cout << endl;
                                system("pause");
                                system("cls");
                                break;
                            case 4:
                                system("cls");
                                if (!lote_ventas_cargado) {
                                    cout << "Debe cargar el Lote de Ventas primero." << endl;
                                } else {
                                listarRecaudacionPorProducto(arr_recaudacion, tam_productos);
                                }
                                system("pause");
                                system("cls");
                                break;


                                case 5:
                                system("cls");
                                if (!lote_ventas_cargado) {
                                    cout << "Debe cargar el Lote de Ventas primero." << endl;
                                } else {
                                    listarPorcentajePorFormaPago(arr_formas_pago, tam_formas_pago, ventas_por_forma_pago, total_ventas_realizadas);
                                }
                                system("pause");
                                system("cls");
                                break;
                                case 6:
                                    system("cls");
                                    if (!lote_ventas_cargado) {
                                        cout << "Debe cargar el Lote de Ventas primero." << endl;
                                    } else {
                                        listarProductosSinVentas(arr_productos, tam_productos, arr_cantidad_vendida_por_producto);
                                    }
                                    system("pause");
                                    system("cls");
                                    break;
                                case 7:
                                    system("cls");
                                    if (!lote_ventas_cargado) {
                                        cout << "Debe cargar el Lote de Ventas primero." << endl;
                                    } else {
                                        listarVentasPorMarcaYFP(arr_ventas_marca_fp, cant_combinaciones_reales, arr_marcas, tam_marcas, arr_formas_pago, tam_formas_pago);
                                    }
                                    system("pause");
                                    system("cls");
                                    break;
                                case 8:
                                    system("cls");
                                    if (!lote_ventas_cargado) {
                                        cout << "Debe cargar el Lote de Ventas primero." << endl;
                                    } else {
                                        listarTopClientesYSorteo(arr_compras_cliente, tam_clientes);
                                    }
                                    system("pause");
                                    system("cls");
                                    break;
                            }

                            cout << endl << endl;
                            opcionReporte = listarReportes();
                        }
                        system("cls"); // Limpia la pantalla al salir del menú de reportes
                        break;

            case 0:
                salir = true;
            break;
        }
    }
    return 0;
}
