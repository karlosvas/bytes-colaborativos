**Este proyecto está subido en [Repositorio](https://github.com/karlosvas/ProyectoViernes-grupo-05)**

**Integrantes**:

- @karlosvas
- @Lsterpino
- @AlternateDelta
- @Rs-845

## Documentacion

**Se ha creado la configuración de SpringBoot 🟢**

### Entidades

**Se ha creado la entidad EstadoTareas 🟢**

La entidad `EstadoTarea` representa los diferentes estados que puede tener una tarea en el sistema.

- **id**: Identificador único de tipo `Long`. Es generado automáticamente.
- **nombre**: Nombre del estado de la tarea. Es un campo obligatorio y único, con un máximo de 50 caracteres, es el tipo `State`.
- **descripcion**: Descripción del estado de la tarea. Es un campo opcional, con un máximo de 255 caracteres.

**Cambio en el modelo `EstadoTarea` añadiendo el enum State 🟢**

Utiliza un enum `State` para la gestión de estados. Esto mejora la claridad y la seguridad del código al definir explícitamente los posibles estados de una tarea.

- **Estados disponibles**:
  - `SUCCESS`: La operación se completó con éxito.
  - `PENDING`: La operación está pendiente de ser procesada.
  - `IN_PROGRESS`: La operación está en curso.
  - `ON_HOLD`: La operación está en espera o pausada temporalmente.
  - `ERROR`: Ocurrió un error durante la operación.
  - `CANCELLED`: La operación fue cancelada.
  - `FAILED`: La operación falló y no se pudo completar.

**Se ha creado la entidad Tarea 🟢**

La entidad `Tarea` representa las tareas que se gestionan en el sistema.

- **id**: Identificador único de tipo `int`. Es generado automáticamente.
- **nombre**: Nombre de la tarea. Es un campo obligatorio.
- **descripcion**: Descripción de la tarea. Es un campo opcional.
- **fechaFinalizacion**: Fecha esperada de terminación de la tarea en formato `dd/MM/yyyy`. Es un campo obligatorio.
- **idEstadoTarea**: Identificador del estado de la tarea. Es un campo obligatorio que referencia a la entidad `EstadoTarea`.

### Validaciones

EstadoTareas:

- `nombre` no puede estar vacío y no puede exceder los 50 caracteres.
- `descripcion` no puede exceder los 255 caracteres.

Tarea:

- `nombre` no puede estar vacío.
- `fechaFinalizacion` debe estar en el formato `dd/MM/yyyy`.
- `idEstadoTarea` debe ser un identificador válido de un estado de tarea existente.

**Se ha creado la base de datos 🟢**  
**Se ha creado las tablas de la base de datos tareas y estado_tareas 🟢**
**Añadido la configuración de application.propierties con la ayuda de dotenv 🟢**

### Estructura de la Base de Datos PostgreSQL

- Tabla: Tareas

| Campo                 | Tipo      | Descripción                                          |
| --------------------- | --------- | ---------------------------------------------------- |
| id_tareas (PK)        | int       | Identificador único de la tarea                      |
| nombre                | String    | Nombre de la tarea                                   |
| descripcion           | String    | Descripción de la tarea                              |
| fecha_finalizacion    | LocalDate | Fecha esperada de terminación (dd/MM/yyyy)           |
| id_estado_tareas (FK) | int       | Identificador del estado de la tarea (clave foránea) |

- Tabla: EstadoTareas

| Campo                 | Tipo   | Descripción                             |
| --------------------- | ------ | --------------------------------------- |
| id_estado_tareas (PK) | int    | Identificador único del estado de tarea |
| nombre                | String | Nombre del estado de la tarea           |
| descripción           | String | Descripción del estado de la tarea      |

### Repositorios

**Creado el repository de EstadoTarea 🟢**  
El repositorio `EstadoTareaRepository` es una interfaz que extiende `JpaRepository` y proporciona métodos CRUD para interactuar con la base de datos. Está vinculado a la entidad `EstadoTarea`, para Consultar todos los estados o buscar estados específicos.

**Creado el repository de `TareaRepository` 🟢**  
El repositorio `TareaRepository` es una interfaz que extiende `JpaRepository` y proporciona métodos CRUD para interactuar con la base de datos. Está vinculado a la entidad `Tarea`, permitiendo realizar operaciones como:

- **Guardar, actualizar y eliminar tareas**: Permite persistir nuevas tareas, actualizar tareas existentes y eliminar tareas de la base de datos.
- **Consultar tareas**: Permite recuperar todas las tareas o tareas específicas según criterios.

### Servicios

**Servicio `TareaService` con las funciones CRUD 🟢**
El servicio permite gestionar las tareas a través de métodos que interactúan con el repositorio `TareaRepository`.

- **Métodos implementados**:
  - `createTarea`: Crea una nueva tarea de tipo `Tarea`.
  - `updateTarea`: Actualiza una tarea existente.
  - `deleteTarea`: Elimina una tarea existente.
  - `getAllTareas`: Obtiene todas las tareas.
  - `getTareaById`: Obtiene una tarea por su identificador.

**Servicio `EstadoTareaService` con las funciones CRUD 🟢**  
El servicio permite gestionar los estados de las tareas a través de métodos que interactúan con el repositorio `EstadoTareaRepository`.

- **Métodos implementados**:
  - `createEstadoTarea`: Crea un nuevo estado de tarea de tipo `State`.
  - `updateEstadoTarea`: Actualiza un estado de tarea existente.
  - `deleteEstadoTarea`: Elimina un estado de tarea existente.
  - `getAllEstadosTarea`: Obtiene todos los estados de tarea.

### Controladores

**Controlador TareaController para manejar las peticiones HTTP 🟢**  
El controlador `TareaController` implementa los endpoints para gestionar las tareas a través de peticiones HTTP.

- **Endpoints implementados**:
  - `POST /api/tareas`: Crea una nueva tarea.
  - `GET /api/tareas`: Obtiene todas las tareas.
  - `PUT /api/tareas/{id}`: Actualiza una tarea existente.
  - `DELETE /api/tareas/{id}`: Elimina una tarea existente.

**Controlador EstadoTareaController para manejar las peticiones HTTP 🟢**  
El controlador `EstadoTareaController` implementa los endpoints para gestionar los estados de las tareas a través de peticiones HTTP.

- **Endpoints implementados**:
  - `POST /api/estados`: Crea un nuevo estado de tarea.
  - `GET /api/estados`: Obtiene todos los estados de tarea.
  - `PUT /api/estados/{id}`: Actualiza un estado de tarea existente.
  - `DELETE /api/estados/{id}`: Elimina un estado de tarea existente.

### Excepciones

**Excepción personalizada `TareaNotFoundException` 🟢**

Se ha creado la excepción personalizada `TareaNotFoundException` para manejar los casos en los que una tarea no se encuentra en la base de datos.

- `TareaNotFoundException`: Constructor que recibe el mensaje de error y lo envía al constructor de la superclase, `RuntimeException`, su segundo parametro opcional es la causa de la excepción de tipo `Throwable`.

**Excepción personalizada `EstadoTareaNotFoundException` 🟢**

Se ha creado la excepción personalizada `EstadoTareaNotFoundException` para manejar los casos en los que un estado de tarea no se encuentra en la base de datos.

- `EstadoTareaNotFoundException`: Constructor que recibe el mensaje de error y lo envía al constructor de la superclase, `RuntimeException`, su segundo parametro opcional es la causa de la excepción de tipo `Throwable`.

### DTOs

**DTO `TareaDTO` para transferir datos de las tareas 🟢**

Se ha creado el DTO `TareaDTO` para transferir datos de las tareas entre el controlador y el servicio. Este DTO se utiliza para evitar exponer directamente las entidades y proporcionar una capa de abstracción entre los datos de la base de datos y los datos enviados a través de las peticiones HTTP.
Utiliza implements Serializable para que pueda ser serializado y deserializado. Esto permite que los objetos DTO se conviertan en bytes para ser enviados a través de la red y luego se reconstruyan en el lado del servidor.

- **Campos del DTO**:

  - `id`: Identificador único de la tarea.
  - `nombre`: Nombre de la tarea.
  - `descripcion`: Descripción de la tarea.
  - `fechaFinalizacion`: Fecha esperada de terminación de la tarea.
  - `idEstadoTarea`: Identificador del estado de la tarea.

**DTO `EstadoTareaDTO` para transferir datos de los estados de las tareas 🟢**

Se ha creado el DTO `EstadoTareaDTO` para transferir datos de los estados de las tareas entre el controlador y el servicio. Este DTO se utiliza para evitar exponer directamente las entidades y proporcionar una capa de abstracción entre los datos de la base de datos y los datos enviados a través de las peticiones HTTP.
Utiliza implements Serializable para que pueda ser serializado y deserializado. Esto permite que los objetos DTO se conviertan en bytes para ser enviados a través de la red y luego se reconstruyan en el lado del servidor.

- **Campos del DTO**:

  - `id_estado_tarea`: Identificador único del estado de la tarea.
  - `nombre`: Nombre del estado de la tarea.
  - `descripcion`: Descripción del estado de la tarea.

### Otros

**Se ha creado la configuración de dotenv necesaria 🟢**

Se ha añadido la dependencia de `dotenv` para cargar las variables de entorno desde un archivo `.env`. Esto permite configurar las propiedades de la aplicación de forma segura y mantener la información sensible fuera del código fuente.
Para que la aplicación cargue las variables de entorno desde un archivo `.env`, se ha creado un archivo `.env.demo` con las variables de configuración necesarias.

> **Nota**: El archivo `.env` no se debe subir al repositorio para mantener la información sensible segura. Se ha añadido al archivo `.gitignore` para evitar que se suba al repositorio.

**Se creó el javadoc 🟢**

Se ha creado la documentación del proyecto en formato Javadoc para facilitar la comprensión del código y la generación de documentación técnica.

> **Nota**: La documentación Javadoc se genera en la carpeta `target/site/apidocs/` del proyecto al ejecutar el comando:

```batch
mvn javadoc:javadoc
```
