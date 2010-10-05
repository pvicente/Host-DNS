Autor: Pedro Vicente Fernandez

Estructura del proyecto
==============================

El proyecto consta del siguiente arbol de archivos:

|-- Makefile
|-- src
|   |-- DNSDatabase.cpp
|   |-- DNSQuery.cpp
|   |-- DNSRegister.cpp
|   |-- DNSRequest.cpp
|   |-- DNSResponse.cpp
|   |-- DNSServer.cpp
|   |-- FlatFile.cpp
|   |-- HashTable.cpp
|   |-- include
|   |   |-- DNSDatabase.hpp
|   |   |-- DNSDefine.hpp
|   |   |-- DNSError.hpp
|   |   |-- DNSHeader.hpp
|   |   |-- DNSQuery.hpp
|   |   |-- DNSRegister.hpp
|   |   |-- DNSRequest.hpp
|   |   |-- DNSResponse.hpp
|   |   |-- DNSServer.hpp
|   |   |-- FlatFile.hpp
|   |   |-- HashTable.hpp
|   |   |-- LogSystem.hpp
|   |   |-- NonCopyable.hpp
|   |   |-- String.hpp
|   |   |-- StringList.hpp
|   |   |-- Tokenizer.hpp
|   |   `-- Utils.hpp
|   |-- LogSystem.cpp
|   |-- main.cpp
|   |-- Makefile
|   |-- String.cpp
|   |-- StringList.cpp
|   |-- Tokenizer.cpp
|   `-- Utils.cpp
`-- tests
    |-- Main.hpp
    |-- Makefile
    |-- TSDNSDatabase.cpp
    |-- TSDNSServer.cpp
    |-- TSFlatFile.cpp
    |-- TSHash.cpp
    |-- TSString.cpp
    |-- TSStringList.cpp
    |-- TSTokenizer.cpp
    `-- TSUtils.cpp


Para construir el programa solo hay que ejecutar make en el directorio base.
El binario dns sera creado en el directorio base.

El directorio tests contiene un conjunto de tests unitarios de cada clase desarrollada en el proyecto.
Para construirlos es necesario tener la libreria libcppunit-dev.

Parametros:
=============================================

El binario dns acepta los siguiente parametros

Usage:
        -p      UDP port number
        -h      Hosts file path

Los valores por defecto son:

Puerto: 53
File: /etc/hosts

Utiliza el sistema de log syslog para todos los mensajes de error de la aplicacion.
Puede ser consultado en /var/log/syslog.

Si el error es grave ademas los mostrara en la salida de error.

El programa no iniciara el servicio si no puede hacer bind sobre ninguna de las interfaces del sistema configuradas.
Necesita de permisos de root si el puerto es < 1024

El servicio escuchara en cada interfaz del sistema que este up y configurada.

Un error en la carga del archivo de datos no provoca que el programa aborte la ejecucion.

Estructura del programa
=============================
Debido a los requerimientos no se han utilizado las STL libraries y tampoco c++ templates.
Se han creado 2 namespaces que contienen la funcionalidad del programa:

- namespace utils: contiene utilities para el programa
	include/HashTable.hpp (HasTable de Strings Nodes)
	include/LogSystem.hpp (Log del sistema)
	include/NonCopyable.hpp (interface of noncopyable objects)
	include/String.hpp (implementacion string con interfaz stl y copia profunda)
	include/StringList.hpp (implementacion de listas de string con interfaz stl)
	include/Tokenizer.hpp (Tokenizer de cadenas reentrante)
	include/Utils.hpp (funciones utiles en el programa)

- namespace dns: contiene las clases propias de dns
	DNSDatabase.hpp (Contiene todos los registros dns cargados en un hashtable)
	DNSDefine.hpp (Contiene las definiciones staticas y typos enumerados)
	DNSError.hpp (Contiene los codigos de error)
	DNSHeader.hpp (Acceso y modificacion a los elementos de una cabecera dns)
	DNSQuery.hpp (Contiene los datos (name, class, type) y funcionalidad para parsear querys dns
	DNSRegister.hpp (Contiene un registro de la base de datos, con las ips asociadas a un host)
	DNSRequest.hpp (Contiene los metodos para el parseo de una request dns)
	DNSResponse.hpp (Contiene los metodos para generar una respuesta a partir de una query dns)
	DNSServer.hpp (Es la instancia que da el servicio dns)

En cuanto a los limites de la implementacion se ha optado por dar un servicio basico de DNS y ante cualquier peticion no soportada
se devulve codigo de respuesta not implemented.

Las limitaciones de la implementacion actuales son las siguientes:

- Solo hay soporte para IPV4 y direcciones ip IPV4. Registros A del dns. El archivo de hosts es interpretado como nombres asociados a IPs y
no existen alias de nombres por lo tanto no existiran respuestas a CNAME.

- Solo se soportan requests tipo A (ANY) y clase IN (ANY). A otro tipo de request el servidor respondera con un codigo not implemented.

- Solo se soporta una query en cada mensaje DNS, si aparecen multiples queries se devolvera una respuesta not implemented.

- Si existen errores en el formato de la request se devolvera un codigo de respuesta indicando el fallo de formato de la request.

- No se soporta protocolo TCP y tampoco recursion. Si el servidor no tiene el nombre devolvera un codigo de respuesta no encontrado.

- Es monoproceso y no multihilo: se ha estimado poco necesario implementar multihilo para el servicio pero en caso necesario
estimamos que no seria traumatico incluirlo.

- No se realizan recargas del fichero. Este es leido en el arranque.


Documentacion
========================

Todos los archivos de cabecera contienen documentacion de los metodos en formato doxygen


Soporte Multiplataforma
============================
Ha sido compilado en linux (ubuntu 32bits y centos 64 bits) con g++ 4.1 y g++ 4.4.

No ha sido compilado en Solaris o HP-UX platform.


Estructura de Datos
=======================

Ha sido desarrollado un hash table, debido a que su desarrollo es simple y rapido, algo que es evaluable.
Es un hash con dispersion abierta (listas de strings) de nodos cuya clave es un string con comparacion case insensitive.

Se han testeado diversos algoritmos de hashing sobre strings

RS Hash Function
JS Hash Function
PJW Hash Function
ELF Hash Function
BKDR Hash Function
SDBM Hash Function
DJB Hash Function
DEK Hash Function
AP Hash Function

y se ha optado por el lgoritmo de hash de strings de boost ya que los resultados han sido muy parecidos a
AP, DEK, SDBM y su complejidad es menor. 

seed ^= tolower(str[i]) + 0x9e3779b9 + (seed<<6) + (seed>>2);

El factor de carga es 0.8, para hacer rehasing de los elementos.

El orden de busqueda en el termino medio es O(1) si no hay colisiones.

Trabajo Futuro
==============================
Soporte de mas funcionalidad: CNAMES, Recursion, TCP protocol, IPV6.

Incorporar multihilo. Servidor concurrente con preforked threads y pthread_conditions.

Comparar rendimiento del hash_table con arboles de busqueda balanceados (Red Black Tree o AVL O(log n) mas eficientes en almacenamiento con 
bloom_filters(no tienen falsos positivos) con hashing O1 en primera busqueda, para filtrar datos que no deben ser buscados.

Comparar rendimiento de hash_table con patricia tries cuyo orden de complejidad es O(1) y son mas eficientes en almacenamiento.

