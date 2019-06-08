#include <wiringPi.h>

// PIN de LED: el PIN 0 de wiringPi es BCM_GPIO 17.
// hemos tenido que usar la numeración de BCM al inicializar con wiringPiSetupSys
// cuando elige un número PIN diferente, use la numeración de BCM, también
// en Páginas de propiedades, seleccione Eventos de compilación > Evento remoto posterior a la compilación y actualice el comando. 
// que utiliza la exportación de gpio para la configuración de wiringPiSetupSys
#define	LED	17

int main(void)
{
	wiringPiSetupSys();

	pinMode(LED, OUTPUT);

	while (true)
	{
		digitalWrite(LED, HIGH);  // Activado
		delay(500); // ms
		digitalWrite(LED, LOW);	  // Desactivado
		delay(500);
	}
	return 0;
}