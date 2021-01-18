# Práctica 2 - Cobertura de vértices con pesos
 * Autor: Fernando Peña Bes (NIA: 756012)
 * Autor: Jose Daniel Subías Sarrato (NIA: 759533)

## Cómo ejecutar

En `lab000` no tenemos permisos para instalar directamente módulos de Python.
Lo más sencillo es utilizar un entorno virtual e instalarlos ahí.

### Preparar el entorno virtual

En Python hay diferentes alternativas para trabajar con entornos virtuales.
Nosotros hemos elegido `venv` que es la manera recomentada de crear entornos
virtuales desde Python 3.6.

Estos son los pasos para usar `venv`: 

1. Ir al directorio raíz del proyecto y crear el entorno mediante el siguiente comando:

    python3 -m venv practica2_env

> En `lab000` puede tardar un minuto la creación del entorno.

2. A continuación, activarlo:

    source practica2_env/bin/activate

3. Por último, instalar los paquetes requeridos en el entorno:

    pip3 install -r requirements.txt

Para desactivar el entorno se puede usar `deactivate`.

### Ejecutar el programa

	python3 vertex_cover.py <fichero_entrada>

### Ejecutar las pruebas automáticas
	
	./ejecutar2.sh
