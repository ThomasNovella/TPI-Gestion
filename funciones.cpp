#include "funciones.h"
#include <cctype>
#include <iostream>
#include <string>
#include "structs.h"
#include <cstdlib> //rand() y srand()
#include <ctime>  // time()


bool cargarMarcas(Marca marcas[], int tam){

    int codigo;
    int minimo = 1;
    int maximo = 10;
    string nombre;

    for(int i = 0; i < tam; i++){

        cout << "Ingrese codigo de marca: ";
        cin >> codigo;

        while(codigo < minimo || codigo > maximo){

            cout << "Codigo invalido";
            cout << endl;
            cout << "Ingrese codigo: ";
            cin >> codigo;
            cout << endl;
        }
        marcas[i].codigo_marca = codigo;

        cin.ignore();

        cout << "Ingrese nombre: ";
        getline(cin,nombre);

        while(nombre.length() == 0){

            cout << "Nombre vacio";
            cout << endl;
            cout << "Ingrese nombre: ";
            getline(cin,nombre);
            cout << endl;
        }

        marcas[i].nombre_marca = nombre;

        cout << endl;
    }
  return true;
}

void listarMarcas(Marca marcas[], int tam){

    for(int i = 0; i < tam; i++){

        cout << "Codigo: " << marcas[i].codigo_marca << endl;
        cout << "Nombre: " << marcas[i].nombre_marca << endl;
        cout << endl;
    }
}

bool validarCodigoConsecutivo(int arr_codigos[], int tam_arr_codigo, int cod_p){
//con_p sirve para el codigo que estoy probando ahora mismo, entonces si es igual al siguente del codigo ya cargado es consecutivo (+1)
    for(int i = 0; i < tam_arr_codigo; i++){

        if(arr_codigos[i] + 1 == cod_p) return true;
    }

    return false;
}

bool cargarProductos(Producto productos[], int tam_p, Marca marcas[], int tam_m){

    int codigo_producto = 0;
    string nombre;
    float precio_venta = 0;
    float precio_compra = 0;
    int stock = 0;
    int codigo_marca = 0;
    int minimo = 100;
    int maximo = 999;
    int cont_comprobar_codigo = 0;
    bool codigo_consecutivo = false;
    const int tam_arr_codigos = tam_p;
    int arr_codigos[tam_arr_codigos]{0};

    for(int i = 0; i < tam_p; i++){

        cout << "Ingrese codigo de producto: ";
        cin >> codigo_producto;

        if(codigo_producto < minimo || codigo_producto > maximo) {

            cout << "El codigo ingresado no es de 3 digitos" << endl << endl;
            system("pause");
            system("cls");
            return false;
        }

        arr_codigos[i] = codigo_producto;

        codigo_consecutivo = false;

        if(i > 0){

            codigo_consecutivo = validarCodigoConsecutivo(arr_codigos, tam_arr_codigos, codigo_producto);
        }

        if(codigo_consecutivo == true){

            cout << "Codigo consecutivo" << endl << endl;
            system("pause");
            system("cls");
            return false;
        }

        cout << "Ingrese nombre: ";
        cin.ignore();
        getline(cin,nombre);

        cout << "Ingrese precio de venta: ";
        cin >> precio_venta;

        cout << "Ingrese precio de compra: ";
        cin >> precio_compra;

        cout << "Ingrese stock disponible: ";
        cin >> stock;

        cout << "Codigo de marca: ";
        cin >> codigo_marca;

        cont_comprobar_codigo = 0;

        //Bug si repito codigo_marca
        for(int j = 0; j < tam_m ; j++){

            if(codigo_marca == marcas[j].codigo_marca) {

                cont_comprobar_codigo++;
                break;
            }
        }

        if(cont_comprobar_codigo == 0){

            cout << endl;
            cout << "Codigo de marca no encontrado en el lote de marcas" << endl;
            cout << endl;
            system("pause");
            system("cls");
            return false;
        }


        productos[i].codigo_producto = codigo_producto;
        productos[i].nombre_producto = nombre;
        productos[i].precio_venta = precio_venta;
        productos[i].precio_compra = precio_compra;
        productos[i].stock = stock;
        productos[i].codigo_marca = codigo_marca;

        cout << endl;
    }

    return true;
}

void listarProductos(Producto productos[], int tam){

    for(int i = 0; i < tam; i++){

        cout << "Codigo de producto: " << productos[i].codigo_producto << endl;
        cout << "Nombre de producto: " << productos[i].nombre_producto << endl;
        cout << "Precio de venta: " << productos[i].precio_venta << endl;
        cout << "Precio de compra: " << productos[i].precio_compra << endl;
        cout << "Stock disponible: " << productos[i].stock << endl;
        cout << "Codigo de marca: " << productos[i].codigo_marca << endl;

        cout << endl;
    }
}

bool validarCodigoFormaPago(string codigo){

    if(codigo == "EF" || codigo == "MP" || codigo == "TR" || codigo == "TC" || codigo == "CT") {
            return true;
            } else{

    cout << "Codigo invalido";
    cout << endl << endl;
    system("pause");
    system("cls");
    return false;
    }
}

bool validarCodigoFormaPagoRepetido(FormaPago formas_pago[], int tam, string codigo_forma_pago){

    for(int i = 0; i < tam; i++){

        if(formas_pago[i].codigo_forma_pago == codigo_forma_pago){

            cout << "Codigo repetido. Intente nuevamente";
            cout << endl << endl;
            system("pause");
            system("cls");
            return true;
        }
    }

    return false;
}

bool cargarFormasPago(FormaPago formas_pago[], int tam){

     bool codigo_valido = false;
     bool codigo_repetido = false;
     string codigo_forma_pago;
     string nombre_forma_pago;
     int porcentaje_descuento = 0;

     for(int i = 0; i < tam; i++){

        cin.ignore();
        cout << "Ingrese codigo forma de pago: ";
        getline(cin,codigo_forma_pago);

        codigo_forma_pago = transformarMayusculaFormasDePago(codigo_forma_pago);

        codigo_valido = false;
        codigo_repetido = false;

        if(i == 0){

            codigo_valido = validarCodigoFormaPago(codigo_forma_pago);

            if(codigo_valido == false){

                return false;
            }
            else{

                formas_pago[i].codigo_forma_pago = codigo_forma_pago;
            }
        }
        if(i > 0){

            codigo_valido = validarCodigoFormaPago(codigo_forma_pago);

            if(codigo_valido == true){

                codigo_repetido = validarCodigoFormaPagoRepetido(formas_pago, tam, codigo_forma_pago);

                if(codigo_repetido == true){

                    return false;
                }
                else{

                    formas_pago[i].codigo_forma_pago = codigo_forma_pago;
                }
            }
            else{

                return false;
            }
        }

        cout << "Ingrese nombre forma de pago: ";
        getline(cin, nombre_forma_pago);

        cout << "Ingrese porcentaje descuento: ";
        cin >> porcentaje_descuento;

        formas_pago[i].nombre_forma_pago = nombre_forma_pago;
        formas_pago[i].porcentaje_descuento = porcentaje_descuento;

        cout << endl;
    }
    return true;
}

string transformarMayusculaFormasDePago(string& codigo){

      for(int i = 0; i < codigo.length(); i++){

            codigo[i] = toupper(codigo[i]);
      }

      return codigo;
}

void listarFormasPago(FormaPago formas_pago[], int tam){

    for(int i = 0; i < tam; i++){

        cout << formas_pago[i].codigo_forma_pago << endl;
        cout << formas_pago[i].nombre_forma_pago << endl;
        cout << formas_pago[i].porcentaje_descuento << endl;

        cout << endl;
    }
}

bool buscarCodigoProducto(Producto productos[], int tam_productos, int codigo_producto){

     for(int i = 0; i < tam_productos; i++){

        if(productos[i].codigo_producto == codigo_producto)return true;

     }
return false;
}

void procesarProductosSinVentas(Producto productos[], int tam_productos, int codigo_producto_actual, int cantidad_vendida, int arr_cant_vendida[]) {
    // Acumulo en la posicion correspondiente en donde se encuentra el codigo de producto
    for(int i = 0; i < tam_productos; i++){
        if(productos[i].codigo_producto == codigo_producto_actual){
            arr_cant_vendida[i] += cantidad_vendida;
            break; //
        }
    }
}

void listarProductosSinVentas(Producto productos[], int tam_productos, int arr_cant_vendida[]){
     system("cls");
     cout << "--- REPORTE: PRODUCTOS SIN VENTAS REGISTRADAS ---" << endl;
     cout << "---------------------------------------------------" << endl << endl;
     bool hubo_sin_ventas = false;

     for(int i = 0; i < tam_productos; i++){
        if(arr_cant_vendida[i] == 0){
            cout << "Codigo de producto: " << productos[i].codigo_producto << endl;
            cout << "Nombre del producto: " << productos[i].nombre_producto << endl;
            cout << endl;
            hubo_sin_ventas = true;
        }
     }

     if (hubo_sin_ventas == false){
        cout << "Todos los productos registraron ventas." << endl;
     }
}

int buscarIndiceFormaPago(FormaPago formas_pago[], int tam, string codigo){
    for(int i=0; i<tam; i++){
        if(formas_pago[i].codigo_forma_pago == codigo){
            return i; // Devuelve la posición donde lo encontró
        }
    }
    return -1; // Devuelve -1 si no lo encuentra (no debería pasar por las validaciones)
}

bool cargarLoteVentas(
    Producto productos[], int tam_productos,
    FormaPago formas_pago[], int tam_formas_pago,
    RecaudacionProducto rec[], int tam_recaudacion,
    int ventas_por_fp[],
    int arr_cant_vendida[],
    VentaMarcaFormaPago arr_ventas_marca_fp[], int &cant_combinaciones,
    CompraCliente arr_compras_cliente[], int tam_clientes,
    int &total_ventas
){

     bool codigo_producto_encontrado = false;
     bool codigo_forma_pago_valido = false;
     int numero_compra = -1;
     int codigo_producto = 0;
     string forma_pago;
     int cantidad_vendida = 0;
     int codigo_cliente = 0;
     int dia_venta = 0;
     total_ventas = 0;

     cout << "Ingrese numero de compra: ";
     cin >> numero_compra;

     while(numero_compra != 0){

         cout << "Ingrese codigo de producto: ";
         cin >> codigo_producto;

         //Verifico si el codigo de producto ingresado esta en el array de productos

         codigo_producto_encontrado = buscarCodigoProducto(productos, tam_productos, codigo_producto);

         if(codigo_producto_encontrado == false){

            cout << "Codigo de producto no encontrado";
            cout << endl << endl;
            system("pause");
            system("cls");

            return false;
         }

         cout << "Ingrese forma de pago: ";
         cin >> forma_pago;

         forma_pago = transformarMayusculaFormasDePago(forma_pago);

         //Ver si no tengo nada cargado
         codigo_forma_pago_valido = validarCodigoFormaPago(forma_pago);

         if(codigo_forma_pago_valido == false){

            cout << "Forma de pago no valida";
            cout << endl << endl;
            system("pause");
            system("cls");

            return false;
         }

         cout << "Ingrese cantidad vendida: ";
         cin >> cantidad_vendida;

         cout << "Ingrese codigo de cliente: ";
         cin >> codigo_cliente;

         if(codigo_cliente < 1 || codigo_cliente > 50){

            cout << "Codigo de cliente no valido";
            cout << endl << endl;
            system("pause");
            system("cls");
            return false;
         }

         cout << "Ingrese dia venta: ";
         cin >> dia_venta;

         if(dia_venta < 1 || dia_venta > 30){

            cout << "Dia venta invalido";
            cout << endl << endl;
            system("pause");
            system("cls");
            return false;
         }
         total_ventas++;

         //4. Productos sin ventas
         //recaudaciones
         //porcentaje forma de pago
         procesarProductosSinVentas(productos, tam_productos, codigo_producto, cantidad_vendida, arr_cant_vendida);
         actualizarRecaudacion(rec, productos, tam_recaudacion, codigo_producto, cantidad_vendida);
         int indice_fp = buscarIndiceFormaPago(formas_pago, tam_formas_pago, forma_pago);
            if (indice_fp != -1) {
            ventas_por_fp[indice_fp]++; // Incrementa el contador para esa forma de pago
            }
            //reporte de ventas por Marca y Forma de pago
         int marca_actual = buscarCodigoMarcaPorProducto(codigo_producto, productos, tam_productos);
         bool combinacion_encontrada = false;
         // Buscamos si la combinación (marca, forma de pago) ya existe
        for (int i = 0; i < cant_combinaciones; i++) {
            if (arr_ventas_marca_fp[i].codigo_marca == marca_actual && arr_ventas_marca_fp[i].codigo_forma_pago == forma_pago) {
                arr_ventas_marca_fp[i].cantidad_vendida += cantidad_vendida;
                combinacion_encontrada = true;
                break;
            }
        }
        // Si no existía, la creamos
        if (!combinacion_encontrada) {
            arr_ventas_marca_fp[cant_combinaciones].codigo_marca = marca_actual;
            arr_ventas_marca_fp[cant_combinaciones].codigo_forma_pago = forma_pago;
            arr_ventas_marca_fp[cant_combinaciones].cantidad_vendida = cantidad_vendida;
            cant_combinaciones++; // Incrementamos el contador de combinaciones reales
        }

        //reporte 5
        arr_compras_cliente[codigo_cliente - 1].cantidad_compras++;

         cout << endl;

         cout << "Ingrese numero de compra: ";
         cin >> numero_compra;

    }

    //4. Listar
    //system("cls");
    //listarProductosSinVentas(productos, tam_productos, arr_cantidad_vendida_por_producto, tam_arr_cant_vendida);

    return true;
}

void inicializarRecaudaciones(RecaudacionProducto rec[], Producto prod[], int tam) {
    for (int i = 0; i < tam; i++) {
        rec[i].codigo_producto = prod[i].codigo_producto;
        rec[i].nombre_producto = prod[i].nombre_producto;
        rec[i].stock_remanente = prod[i].stock;
    }
}

void actualizarRecaudacion(RecaudacionProducto rec[], Producto prod[], int tam, int codigo, int cantidad) {
    for (int i = 0; i < tam; i++) {
        if (rec[i].codigo_producto == codigo) {
            rec[i].cantidad_vendida += cantidad;
            rec[i].total_recaudado += cantidad * prod[i].precio_venta;
            rec[i].stock_remanente -= cantidad;
            break;
        }
    }
}

void listarRecaudacionPorProducto(RecaudacionProducto rec[], int tam) {
    // Ordenamiento por burbuja
    for (int i = 0; i < tam - 1; i++) {
        for (int j = 0; j < tam - i - 1; j++) {
            if (rec[j].cantidad_vendida < rec[j + 1].cantidad_vendida) {
                RecaudacionProducto aux = rec[j];
                rec[j] = rec[j + 1];
                rec[j + 1] = aux;
            }
        }
    }

    cout << "Codigo | Nombre  | Recaudado | Vendido | Stock" << endl;
    cout << "-----------------------------------------------------" << endl;
    for (int i = 0; i < tam; i++){
        cout << rec[i].codigo_producto << "\t "
             << rec[i].nombre_producto << "\t    "
             << rec[i].total_recaudado << "\t\t"
             << rec[i].cantidad_vendida << "\t\t"
             << rec[i].stock_remanente << endl;
    }
}


int listarReportes() {
    int r;
    cout << "--- MENU DE REPORTES ---" << endl;
    cout << "1. Listar Marcas" << endl;
    cout << "2. Listar Productos" << endl;
    cout << "3. Listar Formas de pago" << endl;
    cout << "------------------------" << endl;
    cout << "4. Recaudacion por producto (Ordenado por cantidad vendida)" << endl;
    cout << "5. Porcentaje de ventas por forma de pago" << endl;
    cout << "6. Productos sin ventas" << endl;
    cout << "7. Ventas por Marca y Forma de Pago" << endl;
    cout << "8. Top 10 Clientes y Sorteo" << endl;
    cout << "------------------------" << endl;
    cout << "0. Volver al menu principal"  << endl << endl;
    cout << "Ingrese opcion: ";
    cin >> r;
    cout << endl;
    return r;
}

void listarPorcentajePorFormaPago(FormaPago formas_pago[], int tam_fp, int ventas_por_fp[], int total_ventas) {
    system("cls");
    cout << "--- REPORTE: PORCENTAJE DE VENTAS POR FORMA DE PAGO ---" << endl;
    cout << "--------------------------------------------------------" << endl;

    if (total_ventas == 0) {
        cout << "No se registraron ventas para calcular porcentajes." << endl;
        return; // Salimos de la función si no hay ventas
    }

    for (int i = 0; i < tam_fp; i++) {
        float porcentaje = (float)ventas_por_fp[i] * 100 / total_ventas;
        cout << "Forma de Pago: " << formas_pago[i].nombre_forma_pago << endl;
        cout << "Porcentaje: " << porcentaje << "%" << endl;
        cout << "--------------------------------------------------------" << endl;
    }
}

int buscarCodigoMarcaPorProducto(int cod_prod, Producto productos[], int tam){
     for (int i = 0; i < tam; i++) {
            if (productos[i].codigo_producto == cod_prod) {
                 return productos[i].codigo_marca;
            }
     }
     return -1;
}//nueva

void listarVentasPorMarcaYFP(VentaMarcaFormaPago arr_ventas_marca_fp[], int cant_combinaciones, Marca marcas[], int tam_marcas, FormaPago formas_pago[], int tam_fp) {
    system("cls");
    cout << "--- REPORTE: VENTAS POR MARCA Y FORMA DE PAGO ---" << endl;
    cout << "---------------------------------------------------" << endl;

      // Recorremos cada marca para mostrar sus ventas
      for (int i = 0; i < tam_marcas; i++) {
          cout << endl << "MARCA: " << marcas[i].nombre_marca << endl;
          cout << "........................" << endl;
          bool tuvo_ventas_esta_marca = false;

          // Buscamos en nuestro array de acumuladores qué ventas corresponden a esta marca
          for (int j = 0; j < cant_combinaciones; j++) {
              if (arr_ventas_marca_fp[j].codigo_marca == marcas[i].codigo_marca) {
                  // Buscamos el nombre de la forma de pago para mostrarlo
                  string nombre_fp = "";
                  for (int k = 0; k < tam_fp; k++) {
                      if (formas_pago[k].codigo_forma_pago == arr_ventas_marca_fp[j].codigo_forma_pago) {
                          nombre_fp = formas_pago[k].nombre_forma_pago;
                          break;
                      }
                  }
                  cout << "  > Forma de Pago: " << nombre_fp << endl;
                  cout << "    Cantidad Vendida: " << arr_ventas_marca_fp[j].cantidad_vendida << " unidades" << endl;
                  tuvo_ventas_esta_marca = true;
              }
          }

          if (!tuvo_ventas_esta_marca) {
              cout << "  (Sin ventas registradas para esta marca)" << endl;
          }
      }
  }

  //reporte 5 top clientes y sorteo

  void listarTopClientesYSorteo(CompraCliente arr_compras_cliente[], int tam_clientes) {
    system("cls");
    cout << "--- REPORTE: TOP 10 CLIENTES Y SORTEO DE CUPONES ---" << endl;
    cout << "------------------------------------------------------" << endl;
    // --- Parte 1: Ordenar el array de clientes de mayor a menor ---
      for (int i = 0; i < tam_clientes - 1; i++) {
          for (int j = 0; j < tam_clientes - i - 1; j++) {
              if (arr_compras_cliente[j].cantidad_compras < arr_compras_cliente[j + 1].cantidad_compras) {
                  CompraCliente aux = arr_compras_cliente[j];
                  arr_compras_cliente[j] = arr_compras_cliente[j + 1];
                  arr_compras_cliente[j + 1] = aux;
              }
          }
      }

      // --- Parte 2: Mostrar el Top 10 ---
      cout << endl << "TOP 10 CLIENTES MAS FRECUENTES" << endl;
      cout << "Posicion | Cod. Cliente | Nro. de Compras" << endl;
      cout << "----------------------------------------" << endl;
      for (int i = 0; i < 10; i++) {
          // Solo mostramos si el cliente tuvo al menos una compra
          if (arr_compras_cliente[i].cantidad_compras > 0) {
              cout << "   " << i + 1 << "\t | \t" << arr_compras_cliente[i].codigo_cliente << "\t | \t" << arr_compras_cliente[i].cantidad_compras << endl;
          }
      }
      cout << "----------------------------------------" << endl << endl;

      // --- Parte 3: Sorteo de 3 ganadores ---
      cout << "SORTEO DE 3 CUPONES DE DESCUENTO" << endl;
      cout << "----------------------------------------" << endl;

      // Verificamos si hay al menos 3 clientes en el top 10 para sortear
      int clientes_elegibles = 0;
      for(int i=0; i<10; i++){
          if(arr_compras_cliente[i].cantidad_compras > 0) clientes_elegibles++;
      }

      if (clientes_elegibles < 3) {
          cout << "No hay suficientes clientes elegibles para realizar el sorteo." << endl;
      } else {
          srand(time(NULL)); // Inicializamos la semilla del generador de números aleatorios

          int indices_ganadores[3]{-1, -1, -1}; // Guardamos los índices (0-9) de los ganadores
          int nro_ganador = 0;

          while (nro_ganador < 3) {
              int indice_aleatorio = rand() % clientes_elegibles; // Un número aleatorio entre 0 y (elegibles-1)
              bool repetido = false;
              // Verificamos que no hayamos sacado ya a este ganador
              for (int i = 0; i < nro_ganador; i++) {
                  if (indices_ganadores[i] == indice_aleatorio) {
                      repetido = true;
                      break;
                  }
              }

              if (!repetido) {
                  indices_ganadores[nro_ganador] = indice_aleatorio;
                  nro_ganador++;
              }
          }

          cout << "Los 3 clientes ganadores son!" << endl << endl;
          for (int i = 0; i < 3; i++) {
              int indice_ganador_en_array = indices_ganadores[i];
              cout << "GANADOR " << i + 1 << ": Cliente Nro. " << arr_compras_cliente[indice_ganador_en_array].codigo_cliente;
              cout << " (" << arr_compras_cliente[indice_ganador_en_array].cantidad_compras << " compras)" << endl;
          }
      }
  }
