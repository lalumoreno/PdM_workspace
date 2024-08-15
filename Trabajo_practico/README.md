Curso de Especialización de Sistemas Embebidos (CESE)  
Trabajo práctico para Programación de Microcontroladores y Protocolos de Comunicación   
  
Autor: Laura Andrea Moreno Rodríguez  
Contacto: moreno.rodriguez.laura@gmail.com  
Fecha: Agosto 2024  
  
El sistema consiste en un sensor digital que mide la luz ambiental y por medio de una señal PWM se regula proporcionalmente la intensidad entregada a una lámpara (LED). Adicionalmente se proporciona una interfaz de usuario sencilla donde se puede ver el nivel de luminosidad y de intensidad en tiempo real, así como modificar el nivel de sensibilidad que se desea manejar en el sistema.  

Módulos implementados en el sistema son:   
API: Es el módulo principal del sistema desde donde se maneja la lógica del dimmer automático por medio de una máquina de estados finita y se hace uso de los demás módulos.   
BH1750: Contiene todas las funciones necesarias para comunicarse con el sensor de luminocidad digital BH1750 mediante el protocolo I2C. Desde este módulo se enciende el sensor, se establece la frecuencia de medición y se leen los datos retornados.   
LAMP: Contiene todas las funciones necesarias para modificar el nivel de intensidad entregado a la lámpara o LED mediante la generación de una señal PWM. Desde este módulo se inicializa la señal y se varía el pulso de acuerdo al nivel de luz retornado por el sensor  
UI: Contiene todas las funciones necesarias para entregar una interfaz de usuario en el PC por medio de comunicación UART. Desde este módulo se configura la interfaz para mostrar mensajes en pantalla a petición del sistema y para abrir el menú de configuración al recibir el input del usuario.  

