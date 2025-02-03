# Forward Declarations

Las "forward declarations" o declaraciones anticipadas son una forma de informar al compilador sobre la existencia de una entidad (como una clase, estructura o función) sin proporcionar todos los detalles de su definición. Esto es útil para evitar dependencias circulares y para reducir los tiempos de compilación al no incluir directamente archivos completos donde no se necesita la definición completa.

Por ejemplo, en C++ puedes declarar una clase así:
class MiClase; // Forward declaration

Luego, en otro lugar del programa, puedes utilizar punteros o referencias a "MiClase" sin necesitar su definición completa en ese momento. Más adelante, debes incluir la definición completa (por ejemplo, incluyendo el header correspondiente) para poder acceder a sus miembros o métodos.
